#pragma once

#include <JuceHeader.h>
#include "PluginParameters.h"
#include "OSC.h"

//==============================================================================
/**
*/
class TestSignalGeneratorAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    TestSignalGeneratorAudioProcessor();
    ~TestSignalGeneratorAudioProcessor() override {};

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {};

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; };

    //==============================================================================
    const juce::String getName() const override { return JucePlugin_Name; };

    bool acceptsMidi() const override { return false; };
    bool producesMidi() const override { return false; };
    bool isMidiEffect() const override { return false; };
    double getTailLengthSeconds() const override { return 0.0; };

    //==============================================================================
    int getNumPrograms() override { return 1; };
    int getCurrentProgram() override { return 0; };
    void setCurrentProgram(int index) override {};
    const juce::String getProgramName(int index) override { return {}; };
    void changeProgramName(int index, const juce::String& newName) override {};

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override
    {
        auto state = parameters.copyState();
        std::unique_ptr<XmlElement> xml(state.createXml());
        copyXmlToBinary(*xml, destData);
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName(parameters.state.getType()))
                parameters.replaceState(ValueTree::fromXml(*xmlState));
    }

private:
    void parameterChanged(const String& paramID, float newValue) override;

    AudioProcessorValueTreeState parameters;
    UndoManager undoManager;

    NaiveOscillator oscillator;
    SmoothedValue<float, ValueSmoothingTypes::Linear> gain;

    bool isActive = DEFAULT_ACTV;
    float level = DEFAULT_LVL;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestSignalGeneratorAudioProcessor)
};
