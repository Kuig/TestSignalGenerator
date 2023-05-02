/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (TestSignalGeneratorAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    void hideContextualSliders();
    void setContextualLabels(String l1, String l2, String l3);


    TestSignalGeneratorAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<ButtonAttachment> activeAttachment;
    std::unique_ptr<ComboBoxAttachment> typeAttachment;

    std::unique_ptr<SliderAttachment> f1Attachment;
    std::unique_ptr<SliderAttachment> f2Attachment;
    std::unique_ptr<SliderAttachment> f3Attachment;
    std::unique_ptr<SliderAttachment> qAttachment;
    std::unique_ptr<SliderAttachment> balAttachment;
    std::unique_ptr<SliderAttachment> durAttachment;
    std::unique_ptr<SliderAttachment> typAttachment;
    std::unique_ptr<SliderAttachment> logAttachment;
    std::unique_ptr<SliderAttachment> drAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextButton> undoButton;
    std::unique_ptr<juce::TextButton> redoButton;
    std::unique_ptr<juce::TextButton> loadButton;
    std::unique_ptr<juce::TextButton> saveButton;
    std::unique_ptr<juce::ComboBox> sourceBox;
    std::unique_ptr<juce::Label> srcLabel;
    std::unique_ptr<juce::Slider> f1Slider;
    std::unique_ptr<juce::Label> par1Label;
    std::unique_ptr<juce::Label> par2Label;
    std::unique_ptr<juce::Label> par3Label;
    std::unique_ptr<juce::Slider> f2Slider;
    std::unique_ptr<juce::Slider> f3Slider;
    std::unique_ptr<juce::Label> outLabel;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::ToggleButton> onToggle;
    std::unique_ptr<juce::Slider> qSlider;
    std::unique_ptr<juce::Slider> balSlider;
    std::unique_ptr<juce::Slider> durSlider;
    std::unique_ptr<juce::Slider> typSlider;
    std::unique_ptr<juce::Slider> logSlider;
    std::unique_ptr<juce::Slider> drSlider;
    std::unique_ptr<juce::Label> infoLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

