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
    promotedBuffer.setSize(2, samplesPerBlock);
}

void TestSignalGeneratorAudioProcessor::releaseResources()
{
    promotedBuffer.setSize(0, 0);
}

void TestSignalGeneratorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    const auto numSamples = buffer.getNumSamples();
    
    if (isActive)
    {
        const auto numChannels = buffer.getNumChannels();

        oscillator.getNextAudioBlock(promotedBuffer, numSamples);
        gain.applyGain(promotedBuffer.getWritePointer(0), numSamples);
        castBuffer(buffer, promotedBuffer, 1, numSamples);

        if (numChannels > 1)
            buffer.copyFrom(1, 0, buffer, 0, 0, numSamples);
    }
    else
    {
        gain.skip(numSamples);
        buffer.clear();
    }
}

void TestSignalGeneratorAudioProcessor::processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    if (isActive)
    {
        const auto numSamples = buffer.getNumSamples();
        const auto numChannels = buffer.getNumChannels();

        oscillator.getNextAudioBlock(buffer, numSamples);
        gain.applyGain(buffer.getWritePointer(0), numSamples);

        if (numChannels > 1)
            buffer.copyFrom(1, 0, buffer, 0, 0, numSamples);
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
        gain.setTargetValue(Decibels::decibelsToGain(static_cast<double>(level)));
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
