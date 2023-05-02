#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"

class NaiveOscillator : public AudioProcessorValueTreeState::Listener
{
public:
	NaiveOscillator()
	{
		frequencyOne.setCurrentAndTargetValue(DEFAULT_F1);
		frequencyTwo.setCurrentAndTargetValue(DEFAULT_F2);
		frequencyThree.setCurrentAndTargetValue(DEFAULT_F3);
		balance.setCurrentAndTargetValue((DEFAULT_BAL + 1.0) * 0.5);
	}

	~NaiveOscillator() {};

	void pepareToPlay(double sr)
	{
		sampleRate = sr;
		frequencyOne.reset(sr, RATE_SMTH);
		frequencyTwo.reset(sr, RATE_SMTH);
		frequencyThree.reset(sr, RATE_SMTH);
		balance.reset(sr, AMP_SMTH);
		noiseFilter.reset();

		refreshAllParams();
	}

	void getNextAudioBlock(AudioBuffer<double>& buffer, const int numSamples)
	{
		auto bufferData = buffer.getWritePointer(0);

		for (int smp = 0; smp < numSamples; ++smp)
				bufferData[smp] = getNextAudioSample();
	}

	double getNextAudioSample()
	{
		double sampleValue;
		const auto b = balance.getNextValue();

		switch (waveform)
		{
		case 0: // Sinusoide
			sampleValue = sin(MathConstants<double>::twoPi * normalizedPhaseValueOne);
			break;
		case NOISE_ID: // Noise
			sampleValue = filteredNoise();
			break;
		case 2: // 2 Sines
			sampleValue = sin(MathConstants<double>::twoPi * normalizedPhaseValueOne) * sqrt(1.0 - b) +
				          sin(MathConstants<double>::twoPi * normalizedPhaseValueTwo) * sqrt(b);
			break;
		case 3: // Noise + sine
			sampleValue = sin(MathConstants<double>::twoPi * normalizedPhaseValueOne) * sqrt(1.0 - b) +
				          filteredNoise() * sqrt(b);
			break;
		case 4: // Impulse train
			sampleValue = (float)(normalizedPhaseValueOne < ((trainThresh > 0.0) ? trainThresh : oldPhaseOneValue));
			break;
		case 5: // Log sweep
			sampleValue = sin(MathConstants<double>::twoPi * phaseToCumulativePhase(normalizedPhaseValueOne,
				                                                       frequencyTwo.getCurrentValue(),
				                                                       frequencyThree.getCurrentValue()));
			break;
		case 6: // Ramp
			sampleValue = (normalizedPhaseValueOne * 2.0) - 1.0;
			break;
		case 7: // Ramp * Sine
			sampleValue = phaseToLevel(normalizedPhaseValueOne) * sin(MathConstants<double>::twoPi * normalizedPhaseValueTwo);
			break;
		case 8: // Ramp * Noise
			sampleValue = phaseToLevel(normalizedPhaseValueOne) * filteredNoise();
			break;
		case 9: // Sine Burst
			sampleValue = phaseToBurst(normalizedPhaseValueOne) * sin(MathConstants<double>::twoPi * normalizedPhaseValueTwo);
			break;
		case 10: // Noise Burst
			sampleValue = phaseToBurst(normalizedPhaseValueOne) * filteredNoise();
			break;
		default:
			sampleValue = 0.0;
		}

		updatePhase();

		return sampleValue;
	}

	void refreshAllParams()
	{
		parameterChanged(NAME_ACTV, (float)actv);
		parameterChanged(NAME_WF,   (float)waveform);
		parameterChanged(NAME_F1,   (float)f1);
		parameterChanged(NAME_F2,   (float)f2);
		parameterChanged(NAME_F3,   (float)f3);
		parameterChanged(NAME_BAL,  (float)bal);
		parameterChanged(NAME_DUR,  (float)trainThresh);
		parameterChanged(NAME_Q,    (float)q);
		parameterChanged(NAME_TYP,  (float)typ);
		parameterChanged(NAME_LOG,  (float)rampIndB);
		parameterChanged(NAME_DR,   (float)dr);
	}

private:
	void resetPhase()
	{
		normalizedPhaseValueOne = 0.0;
		normalizedPhaseValueTwo = 0.0;
		oldPhaseOneValue = 0.0;
	}

	void updatePhase()
	{
		oldPhaseOneValue = normalizedPhaseValueOne;

		{
			const double phaseIncrement = frequencyOne.getNextValue() / sampleRate;
			normalizedPhaseValueOne += phaseIncrement;
			normalizedPhaseValueOne -= static_cast<int>(normalizedPhaseValueOne);
		}

		{
			const double phaseIncrement = frequencyTwo.getNextValue() / sampleRate;
			normalizedPhaseValueTwo += phaseIncrement;
			normalizedPhaseValueTwo -= static_cast<int>(normalizedPhaseValueTwo);
		}

		{
			frequencyThree.getNextValue();
		}
	}

	double phaseToCumulativePhase(double x, double l, double h)
	{
		const auto stl = log2(l);
		const auto sth = log2(h);
		const auto st = (x * (sth - stl)) + stl;
		const auto hz = pow(2.0, st) / sampleRate;

		cump += hz;
		cump -= static_cast<int>(cump);

		return cump;
	}

	double phaseToLevel(double x)
	{
		x = rampIndB < 2 ? x : 1.0 - x;
		return (rampIndB % 2) ? Decibels::decibelsToGain(x * 96.0 - 96.0) : x;
	}

	double phaseToBurst(double x)
	{
		return ((x < lThresh) || (x > uThresh)) ? lowLevel : 1.0;
	}

	void setFilter()
	{
		const auto f = jmin((waveform == NOISE_ID) ? f1 : f2, sampleRate * 0.5);
		IIRCoefficients coeff;

		switch (typ)
		{
		case 0: // LP
			coeff = IIRCoefficients::makeLowPass(sampleRate, f, q);
			break;
		case 1: // BP
			coeff = IIRCoefficients::makeBandPass(sampleRate, f, q);
			break;
		case 2: // HP
			coeff = IIRCoefficients::makeHighPass(sampleRate, f, q);
			break;
		default:
			coeff = IIRCoefficients::makeLowPass(sampleRate, f, q);
			break;
		}

		noiseFilter.setCoefficients(coeff);
	}

	double filteredNoise()
	{
		const auto f = (waveform == NOISE_ID) ? f1 : f2;
		const auto x = 2.0 * (rand.nextDouble() - 0.5);
		const auto ft = (typ == 0 && f < 20000.0) || (typ == 1) || (typ == 2 && f > 0.05);
		// Still old filter class... not worried since it just processes noise.
		return ft ? (double)noiseFilter.processSingleSampleRaw((float)x) : (float)x;
	}

	void parameterChanged(const String& paramID, float newValue) override
	{
		if (paramID == NAME_ACTV)
		{
			actv = newValue > 0.5f;
			if (actv) resetPhase();
		}

		if (paramID == NAME_WF)
		{
			waveform = roundToInt(newValue);
			resetPhase();
		}

		if (paramID == NAME_F1)
		{
			f1 = jmin(static_cast<double>(newValue), sampleRate * 0.5);
			frequencyOne.setTargetValue(f1);
			setFilter();
		}

		if (paramID == NAME_F2)
		{
			f2 = jmin(static_cast<double>(newValue), sampleRate * 0.5);
			frequencyTwo.setTargetValue(f2);
			setFilter();
		}

		if (paramID == NAME_F3)
		{
			f3 = jmin(static_cast<double>(newValue), sampleRate * 0.5);
			frequencyThree.setTargetValue(f3);
		}

		if (paramID == NAME_BAL)
		{
			bal = static_cast<double>(newValue);
			balance.setTargetValue((bal + 1.0) * 0.5);
		}

		if (paramID == NAME_DUR)
			trainThresh = static_cast<double>(newValue);

		if (paramID == NAME_Q)
		{
			q = static_cast<double>(newValue);
			setFilter();
		}

		if (paramID == NAME_TYP)
		{
			typ = roundToInt(newValue);
			setFilter();
		}

		if (paramID == NAME_LOG)
			rampIndB = roundToInt(newValue);

		if (paramID == NAME_DR)
		{
			dr = static_cast<double>(newValue);
			lowLevel = Decibels::decibelsToGain(dr);
		}
	}

	double sampleRate = 1.0;
	
	bool actv = DEFAULT_ACTV;
	int waveform = DEFAULT_WF;
	double f1 = DEFAULT_F1;
	double f2 = DEFAULT_F2;
	double f3 = DEFAULT_F3;
	double bal = 0.5 * (DEFAULT_BAL + 1.0);
	double trainThresh = DEFAULT_DUR;
	double q = DEFAULT_Q;
	int typ = DEFAULT_TYP;
	int rampIndB = DEFAULT_LOG;
	double dr = DEFAULT_DR;
	
	double lowLevel = Decibels::decibelsToGain(DEFAULT_DR);
	
	double normalizedPhaseValueOne = 0.0;
	double normalizedPhaseValueTwo = 0.0;
	double oldPhaseOneValue = 0.0;
	double cump = 0.0;
	double lThresh = 0.25;
	double uThresh = 0.75;
	IIRFilter noiseFilter;
	SmoothedValue<double, ValueSmoothingTypes::Multiplicative> frequencyOne;
	SmoothedValue<double, ValueSmoothingTypes::Multiplicative> frequencyTwo;
	SmoothedValue<double, ValueSmoothingTypes::Multiplicative> frequencyThree;
	SmoothedValue<double, ValueSmoothingTypes::Linear> balance;
	Random rand;
};