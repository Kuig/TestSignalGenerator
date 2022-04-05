#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestSignalGeneratorAudioProcessor::TestSignalGeneratorAudioProcessor() :
    parameters(*this, &undoManager, Identifier("Parameters"), createParameterLayout())
{

    parameters.addParameterListener(NAME_LVL, this);
    parameters.addParameterListener(NAME_ACTV, this);

    parameters.addParameterListener(NAME_ACTV, &oscillator);
    parameters.addParameterListener(NAME_WF, &oscillator);
    parameters.addParameterListener(NAME_F1, &oscillator);
    parameters.addParameterListener(NAME_F2, &oscillator);
    parameters.addParameterListener(NAME_F3, &oscillator);
    parameters.addParameterListener(NAME_BAL, &oscillator);
    parameters.addParameterListener(NAME_DUR, &oscillator);
    parameters.addParameterListener(NAME_Q, &oscillator);
    parameters.addParameterListener(NAME_TYP, &oscillator);
    parameters.addParameterListener(NAME_LOG, &oscillator);
    parameters.addParameterListener(NAME_DR, &oscillator);

}

//==============================================================================
void TestSignalGeneratorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    oscillator.pepareToPlay(sampleRate);
    gain.reset(sampleRate, AMP_SMTH);
    gain.setTargetValue(Decibels::decibelsToGain(level));
}

void TestSignalGeneratorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //juce::ScopedNoDenormals noDenormals;

    if (isActive)
    {
        const auto numSamples = buffer.getNumSamples();
        oscillator.getNextAudioBlock(buffer, numSamples);

        if (buffer.getNumChannels() > 1)
            buffer.copyFrom(1, 0, buffer, 0, 0, numSamples);

        gain.applyGain(buffer, numSamples);
    }
    else
        buffer.clear();
}

//==============================================================================

void TestSignalGeneratorAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == NAME_LVL)
    {
        level = newValue;
        gain.setTargetValue(Decibels::decibelsToGain(level));
    }

    if (paramID == NAME_ACTV)
    {
        isActive = newValue > 0.5f;
        oscillator.refreshAllParams();
    }

}

juce::AudioProcessorEditor* TestSignalGeneratorAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestSignalGeneratorAudioProcessor();
}
