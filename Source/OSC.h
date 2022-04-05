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

	void getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples)
	{
		auto* bufferData = buffer.getWritePointer(0);

		for (int smp = 0; smp < numSamples; ++smp)
				bufferData[smp] = getNextAudioSample();
	}

	float getNextAudioSample()
	{
		float sampleValue;
		const auto b = balance.getNextValue();

		switch (waveform)
		{
		case 0: // Sinusoide
			sampleValue = sin(MathConstants<float>::twoPi * normalizedPhaseValueOne);
			break;
		case NOISE_ID: // Noise
			sampleValue = filteredNoise();
			break;
		case 2: // 2 Sines
			sampleValue = sin(MathConstants<float>::twoPi * normalizedPhaseValueOne) * sqrt(1.0 - b) +
				          sin(MathConstants<float>::twoPi * normalizedPhaseValueTwo) * sqrt(b);
			break;
		case 3: // Noise + sine
			sampleValue = sin(MathConstants<float>::twoPi * normalizedPhaseValueOne) * sqrt(1.0f - b) +
				          filteredNoise() * sqrt(b);
			break;
		case 4: // Impulse train
			sampleValue = (float)(normalizedPhaseValueOne < ((trainThresh > 0.0f) ? trainThresh : oldPhaseOneValue));
			break;
		case 5: // Log sweep
			sampleValue = sin(MathConstants<float>::twoPi * phaseToCumulativePhase(normalizedPhaseValueOne,
				                                                       frequencyTwo.getCurrentValue(),
				                                                       frequencyThree.getCurrentValue()));
			break;
		case 6: // Ramp
			sampleValue = (normalizedPhaseValueOne * 2.0f) - 1.0f;
			break;
		case 7: // Ramp * Sine
			sampleValue = phaseToLevel(normalizedPhaseValueOne) * sin(MathConstants<float>::twoPi * normalizedPhaseValueTwo);
			break;
		case 8: // Ramp * Noise
			sampleValue = phaseToLevel(normalizedPhaseValueOne) * filteredNoise();
			break;
		case 9: // Sine Burst
			sampleValue = phaseToBurst(normalizedPhaseValueOne) * sin(MathConstants<float>::twoPi * normalizedPhaseValueTwo);
			break;
		case 10: // Noise Burst
			sampleValue = phaseToBurst(normalizedPhaseValueOne) * filteredNoise();
			break;
		default:
			sampleValue = 0.0f;
		}

		updatePhase();

		return sampleValue;
	}

	void refreshAllParams()
	{
		parameterChanged(NAME_ACTV, actv);
		parameterChanged(NAME_WF, waveform);
		parameterChanged(NAME_F1, f1);
		parameterChanged(NAME_F2, f2);
		parameterChanged(NAME_F3, f3);
		parameterChanged(NAME_BAL, bal);
		parameterChanged(NAME_DUR, trainThresh);
		parameterChanged(NAME_Q, q);
		parameterChanged(NAME_TYP, typ);
		parameterChanged(NAME_LOG, rampIndB);
		parameterChanged(NAME_DR, dr);
	}

private:
	void resetPhase()
	{
		normalizedPhaseValueOne = 0.0f;
		normalizedPhaseValueTwo = 0.0f;
		oldPhaseOneValue = 0.0f;
	}

	void updatePhase()
	{
		oldPhaseOneValue = normalizedPhaseValueOne;

		{
			const float phaseIncrement = frequencyOne.getNextValue() / sampleRate;
			normalizedPhaseValueOne += phaseIncrement;
			normalizedPhaseValueOne -= static_cast<int>(normalizedPhaseValueOne);
		}

		{
			const float phaseIncrement = frequencyTwo.getNextValue() / sampleRate;
			normalizedPhaseValueTwo += phaseIncrement;
			normalizedPhaseValueTwo -= static_cast<int>(normalizedPhaseValueTwo);
		}

		{
			frequencyThree.getNextValue();
		}
	}

	float phaseToCumulativePhase(float x, float l, float h)
	{
		const auto stl = log2(l);
		const auto sth = log2(h);
		const auto st = (x * (sth - stl)) + stl;
		const auto hz = pow(2.0f, st) / sampleRate;

		cump += hz;
		cump -= static_cast<int>(cump);

		return cump;
	}

	float phaseToLevel(float x)
	{
		x = rampIndB < 2 ? x : 1.0f - x;
		return (rampIndB % 2) ? Decibels::decibelsToGain(x * 96.0f - 96.0f) : x;
	}

	float phaseToBurst(float x)
	{
		return ((x < lThresh) || (x > uThresh)) ? lowLevel : 1.0;
	}

	void setFilter()
	{
		const auto f = jmin((waveform == NOISE_ID) ? f1 : f2, (float)(sampleRate * 0.5));
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

	float filteredNoise()
	{
		const auto f = (waveform == NOISE_ID) ? f1 : f2;
		const auto x = 2.0f * (rand.nextFloat() - 0.5f);
		const auto ft = (typ == 0 && f < 20000.0f) || (typ == 1) || (typ == 2 && f > 0.05f);
		return ft ? noiseFilter.processSingleSampleRaw(x) : x;
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
			f1 = jmin(newValue, (float)(sampleRate * 0.5));
			frequencyOne.setTargetValue(f1);
			setFilter();
		}

		if (paramID == NAME_F2)
		{
			f2 = jmin(newValue, (float)(sampleRate * 0.5));
			frequencyTwo.setTargetValue(newValue);
			setFilter();
		}

		if (paramID == NAME_F3)
		{
			f3 = jmin(newValue, (float)(sampleRate * 0.5));
			frequencyThree.setTargetValue(newValue);
		}

		if (paramID == NAME_BAL)
		{
			bal = newValue;
			balance.setTargetValue((newValue + 1.0) * 0.5);
		}

		if (paramID == NAME_DUR)
			trainThresh = newValue;

		if (paramID == NAME_Q)
		{
			q = newValue;
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
			dr = newValue;
			lowLevel = Decibels::decibelsToGain(dr);
		}
	}

	double sampleRate = 1.0;
	
	bool actv = DEFAULT_ACTV;
	int waveform = DEFAULT_WF;
	float f1 = DEFAULT_F1;
	float f2 = DEFAULT_F2;
	float f3 = DEFAULT_F3;
	double bal = 0.5 * (DEFAULT_BAL + 1.0);
	float trainThresh = DEFAULT_DUR;
	float q = DEFAULT_Q;
	int typ = DEFAULT_TYP;
	int rampIndB = DEFAULT_LOG;
	float dr = DEFAULT_DR;
	
	float lowLevel = Decibels::decibelsToGain(DEFAULT_DR);
	
	float normalizedPhaseValueOne = 0.0f;
	float normalizedPhaseValueTwo = 0.0f;
	float oldPhaseOneValue = 0.0f;
	float cump = 0.0f;
	float lThresh = 0.25f;
	float uThresh = 0.75f;
	IIRFilter noiseFilter;
	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequencyOne;
	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequencyTwo;
	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequencyThree;
	SmoothedValue<double, ValueSmoothingTypes::Linear> balance;
	Random rand;
};