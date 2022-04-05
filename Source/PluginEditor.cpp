/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (TestSignalGeneratorAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    undoButton.reset (new juce::TextButton ("Undo"));
    addAndMakeVisible (undoButton.get());
    undoButton->addListener (this);

    undoButton->setBounds (328, 56, 56, 24);

    redoButton.reset (new juce::TextButton ("Redo"));
    addAndMakeVisible (redoButton.get());
    redoButton->addListener (this);

    redoButton->setBounds (392, 56, 56, 24);

    loadButton.reset (new juce::TextButton ("Load"));
    addAndMakeVisible (loadButton.get());
    loadButton->addListener (this);

    loadButton->setBounds (328, 16, 56, 24);

    saveButton.reset (new juce::TextButton ("Save"));
    addAndMakeVisible (saveButton.get());
    saveButton->addListener (this);

    saveButton->setBounds (392, 16, 56, 24);

    sourceBox.reset (new juce::ComboBox ("Source"));
    addAndMakeVisible (sourceBox.get());
    sourceBox->setEditableText (false);
    sourceBox->setJustificationType (juce::Justification::centredLeft);
    sourceBox->setTextWhenNothingSelected (juce::String());
    sourceBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sourceBox->addListener (this);

    sourceBox->setBounds (128, 56, 144, 24);

    srcLabel.reset (new juce::Label ("Source label",
                                     TRANS("Signal type:")));
    addAndMakeVisible (srcLabel.get());
    srcLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    srcLabel->setJustificationType (juce::Justification::centredLeft);
    srcLabel->setEditable (false, false, false);
    srcLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    srcLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    srcLabel->setBounds (18, 56, 96, 24);

    f1Slider.reset (new juce::Slider ("F1"));
    addAndMakeVisible (f1Slider.get());
    f1Slider->setRange (0, 10, 0);
    f1Slider->setSliderStyle (juce::Slider::LinearHorizontal);
    f1Slider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    f1Slider->addListener (this);

    f1Slider->setBounds (128, 96, 320, 24);

    par1Label.reset (new juce::Label ("Freq 1",
                                      TRANS("Rate/Freq. 1:")));
    addAndMakeVisible (par1Label.get());
    par1Label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    par1Label->setJustificationType (juce::Justification::centredLeft);
    par1Label->setEditable (false, false, false);
    par1Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    par1Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    par1Label->setBounds (18, 96, 96, 24);

    par2Label.reset (new juce::Label ("Parameter 2",
                                      TRANS("Rate/Freq. 2:\n")));
    addAndMakeVisible (par2Label.get());
    par2Label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    par2Label->setJustificationType (juce::Justification::centredLeft);
    par2Label->setEditable (false, false, false);
    par2Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    par2Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    par2Label->setBounds (18, 136, 96, 24);

    par3Label.reset (new juce::Label ("Parameter 3",
                                      TRANS("Ramp scale:\n")));
    addAndMakeVisible (par3Label.get());
    par3Label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    par3Label->setJustificationType (juce::Justification::centredLeft);
    par3Label->setEditable (false, false, false);
    par3Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    par3Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    par3Label->setBounds (18, 176, 96, 24);

    f2Slider.reset (new juce::Slider ("F2"));
    addAndMakeVisible (f2Slider.get());
    f2Slider->setRange (0, 10, 0);
    f2Slider->setSliderStyle (juce::Slider::LinearHorizontal);
    f2Slider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    f2Slider->setBounds (128, 136, 320, 24);

    f3Slider.reset (new juce::Slider ("F3"));
    addAndMakeVisible (f3Slider.get());
    f3Slider->setRange (0, 10, 0);
    f3Slider->setSliderStyle (juce::Slider::LinearHorizontal);
    f3Slider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    f3Slider->setBounds (128, 176, 320, 24);

    outLabel.reset (new juce::Label ("Out gain",
                                     TRANS("Out gain:\n")));
    addAndMakeVisible (outLabel.get());
    outLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    outLabel->setJustificationType (juce::Justification::centredLeft);
    outLabel->setEditable (false, false, false);
    outLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    outLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    outLabel->setBounds (18, 221, 96, 32);

    gainSlider.reset (new juce::Slider ("Out gain"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setRange (0, 10, 0);
    gainSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    gainSlider->setBounds (128, 221, 320, 32);

    onToggle.reset (new juce::ToggleButton ("Active"));
    addAndMakeVisible (onToggle.get());
    onToggle->setButtonText (juce::String());
    onToggle->setToggleState (true, juce::dontSendNotification);

    onToggle->setBounds (288, 56, 23, 24);

    qSlider.reset (new juce::Slider ("Q"));
    addAndMakeVisible (qSlider.get());
    qSlider->setRange (0, 10, 0);
    qSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    qSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    qSlider->setBounds (128, 136, 320, 24);

    balSlider.reset (new juce::Slider ("BAL"));
    addAndMakeVisible (balSlider.get());
    balSlider->setRange (0, 10, 0);
    balSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    balSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    balSlider->setBounds (128, 176, 320, 24);

    durSlider.reset (new juce::Slider ("DUR"));
    addAndMakeVisible (durSlider.get());
    durSlider->setRange (0, 10, 0);
    durSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    durSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    durSlider->setBounds (128, 176, 320, 24);

    typSlider.reset (new juce::Slider ("TYP"));
    addAndMakeVisible (typSlider.get());
    typSlider->setRange (0, 10, 0);
    typSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    typSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    typSlider->setBounds (128, 176, 320, 24);

    logSlider.reset (new juce::Slider ("LOG"));
    addAndMakeVisible (logSlider.get());
    logSlider->setRange (0, 10, 0);
    logSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    logSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    logSlider->setBounds (128, 176, 320, 24);

    drSlider.reset (new juce::Slider ("DR"));
    addAndMakeVisible (drSlider.get());
    drSlider->setRange (0, 10, 0);
    drSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    drSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

    drSlider->setBounds (128, 176, 320, 24);

    infoLabel.reset (new juce::Label ("Info box",
                                      TRANS("F1 period: 0.3942 sec (12343 samples); sample rate: 44100.")));
    addAndMakeVisible (infoLabel.get());
    infoLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    infoLabel->setJustificationType (juce::Justification::centredLeft);
    infoLabel->setEditable (false, false, false);
    infoLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    infoLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    infoLabel->setBounds (16, 264, 440, 24);


    //[UserPreSize]
    
    sourceBox->addItemList(oscChoices, 1);
     
    // ATTACHMENTS
    {
        gainAttachment.reset(new SliderAttachment(valueTreeState,   NAME_LVL,  *gainSlider));
        activeAttachment.reset(new ButtonAttachment(valueTreeState, NAME_ACTV, *onToggle));
        typeAttachment.reset(new ComboBoxAttachment(valueTreeState, NAME_WF,   *sourceBox));

        f1Attachment.reset(new SliderAttachment(valueTreeState,  NAME_F1,  *f1Slider ));
        f2Attachment.reset(new SliderAttachment(valueTreeState,  NAME_F2,  *f2Slider ));
        f3Attachment.reset(new SliderAttachment(valueTreeState,  NAME_F3,  *f3Slider ));
        qAttachment.reset(new SliderAttachment(valueTreeState,   NAME_Q,   *qSlider  ));
        balAttachment.reset(new SliderAttachment(valueTreeState, NAME_BAL, *balSlider));
        durAttachment.reset(new SliderAttachment(valueTreeState, NAME_DUR, *durSlider));
        typAttachment.reset(new SliderAttachment(valueTreeState, NAME_TYP, *typSlider));
        logAttachment.reset(new SliderAttachment(valueTreeState, NAME_LOG, *logSlider));
        drAttachment.reset(new SliderAttachment(valueTreeState,  NAME_DR,  *drSlider ));
    }


    //[/UserPreSize]

    setSize (470, 320);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    gainAttachment.reset();
    activeAttachment.reset();
    typeAttachment.reset();
    f1Attachment.reset();
    f2Attachment.reset();
    f3Attachment.reset();
    qAttachment.reset();
    balAttachment.reset();
    durAttachment.reset();
    typAttachment.reset();
    logAttachment.reset();
    drAttachment.reset();
    //[/Destructor_pre]

    undoButton = nullptr;
    redoButton = nullptr;
    loadButton = nullptr;
    saveButton = nullptr;
    sourceBox = nullptr;
    srcLabel = nullptr;
    f1Slider = nullptr;
    par1Label = nullptr;
    par2Label = nullptr;
    par3Label = nullptr;
    f2Slider = nullptr;
    f3Slider = nullptr;
    outLabel = nullptr;
    gainSlider = nullptr;
    onToggle = nullptr;
    qSlider = nullptr;
    balSlider = nullptr;
    durSlider = nullptr;
    typSlider = nullptr;
    logSlider = nullptr;
    drSlider = nullptr;
    infoLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 18, y = 10, width = 292, height = 30;
        juce::String text (TRANS("Test Signal Generator"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 20.00f, juce::Font::bold));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 296, width = 430, height = 16;
        juce::String text (TRANS("Coded by G.P. at Laboratorio di Informatica Musicale :: V 1.0"));
        juce::Colour fillColour = juce::Colour (0xff617077);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    auto defaultLoc = File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory);
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == undoButton.get())
    {
        //[UserButtonCode_undoButton] -- add your button handler code here..
        valueTreeState.undoManager->undo();
        //[/UserButtonCode_undoButton]
    }
    else if (buttonThatWasClicked == redoButton.get())
    {
        //[UserButtonCode_redoButton] -- add your button handler code here..
        valueTreeState.undoManager->redo();
        //[/UserButtonCode_redoButton]
    }
    else if (buttonThatWasClicked == loadButton.get())
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        juce::FileChooser chooser("Select preset to load...", defaultLoc, "*.xml");

        if (chooser.browseForFileToOpen())
        {
            auto fileToLoad = chooser.getResult();
            MemoryBlock sourceData;
            fileToLoad.loadFileAsData(sourceData);
            processor.setStateInformation(sourceData.getData(), sourceData.getSize());
        }
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == saveButton.get())
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        juce::FileChooser chooser("Select save position...", defaultLoc, "*.xml");

        if (chooser.browseForFileToSave(true))
        {
            auto file = chooser.getResult();

            if (file.existsAsFile())
                file.deleteFile();

            juce::FileOutputStream outputStream(file);

            if (outputStream.openedOk())
            {
                MemoryBlock destData;
                processor.getStateInformation(destData);
                outputStream.write(destData.getData(), destData.getSize());
            }
        }
        //[/UserButtonCode_saveButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == sourceBox.get())
    {
        //[UserComboBoxCode_sourceBox] -- add your combo box handling code here..

        hideContextualSliders();

        switch (sourceBox->getSelectedItemIndex())
        {
        case 0: // Sinusoide
            setContextualLabels("Frequency:","","");
            break;
        case NOISE_ID: // Noise
            setContextualLabels("Frequency:", "Quality:", "Filter:");
            qSlider->setVisible(true);
            typSlider->setVisible(true);
            break;
        case 2: // 2 Sines
        case 3: // Noise + sine
            setContextualLabels("Frequency 1:", "Frequency 2:", "Balance:");
            f2Slider->setVisible(true);
            balSlider->setVisible(true);
            break;
        case 4: // Impulse train
            setContextualLabels("Frequency:", "", "Width:");
            durSlider->setVisible(true);
            break;
        case 5: // Log sweep
            setContextualLabels("Rate:", "From freq:", "To freq:");
            f2Slider->setVisible(true);
            f3Slider->setVisible(true);
            break;
        case 6: // Ramp
            setContextualLabels("Rate:", "", "");
            break;
        case 7: // Ramp * Sine
        case 8: // Ramp * Noise
            setContextualLabels("Rate:", "Frequency:", "Ramp scale:");
            f2Slider->setVisible(true);
            logSlider->setVisible(true);
            break;
        case 9: // Sine Burst
        case 10: // Noise Burst
            setContextualLabels("Rate:", "Frequency:", "Dynamic range:");
            f2Slider->setVisible(true);
            drSlider->setVisible(true);
            break;
        default:
            break;
        }
        //[/UserComboBoxCode_sourceBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == f1Slider.get())
    {
        //[UserSliderCode_f1Slider] -- add your slider handling code here..
        auto sr = processor.getSampleRate();
        auto t = 1.0 / f1Slider->getValue();
        auto s = t * sr;
        auto decimals = (t < 1) ? 4 : ((t < 10) ? 3 : 2);
        String info = String("F1 period: ") + String(t, decimals) <<  " sec (" << String(s, 1) << " samples); Sample rate: " << String(roundToInt(sr)) << ".";
        infoLabel->setText(info, NotificationType::sendNotification);
        //[/UserSliderCode_f1Slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PluginEditor::hideContextualSliders()
{
    f2Slider->setVisible(false);
    f3Slider->setVisible(false);
    qSlider->setVisible(false);
    balSlider->setVisible(false);
    durSlider->setVisible(false);
    typSlider->setVisible(false);
    logSlider->setVisible(false);
    drSlider->setVisible(false);
}

void PluginEditor::setContextualLabels(String l1, String l2, String l3)
{
    par1Label->setText(l1, NotificationType::sendNotification);
    par2Label->setText(l2, NotificationType::sendNotification);
    par3Label->setText(l3, NotificationType::sendNotification);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="TestSignalGeneratorAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p), processor(p), valueTreeState(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="470" initialHeight="320">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="18 10 292 30" fill="solid: ffffffff" hasStroke="0" text="Test Signal Generator"
          fontname="Default monospaced font" fontsize="20.0" kerning="0.0"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 296 430 16" fill="solid: ff617077" hasStroke="0" text="Coded by G.P. at Laboratorio di Informatica Musicale :: V 1.0"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
  </BACKGROUND>
  <TEXTBUTTON name="Undo" id="972fdcacaeb6cba1" memberName="undoButton" virtualName=""
              explicitFocusOrder="0" pos="328 56 56 24" buttonText="Undo" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Redo" id="e764a8bee8d8e92a" memberName="redoButton" virtualName=""
              explicitFocusOrder="0" pos="392 56 56 24" buttonText="Redo" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load" id="7f1231bf9104366b" memberName="loadButton" virtualName=""
              explicitFocusOrder="0" pos="328 16 56 24" buttonText="Load" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Save" id="16d654ee459b8269" memberName="saveButton" virtualName=""
              explicitFocusOrder="0" pos="392 16 56 24" buttonText="Save" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="Source" id="60a9aef1725bf9d0" memberName="sourceBox" virtualName=""
            explicitFocusOrder="0" pos="128 56 144 24" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="Source label" id="a9a23e46a87dcd0c" memberName="srcLabel"
         virtualName="" explicitFocusOrder="0" pos="18 56 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Signal type:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="F1" id="1289608264f87443" memberName="f1Slider" virtualName=""
          explicitFocusOrder="0" pos="128 96 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Freq 1" id="34818acade7a032c" memberName="par1Label" virtualName=""
         explicitFocusOrder="0" pos="18 96 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rate/Freq. 1:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Parameter 2" id="569be5139311784d" memberName="par2Label"
         virtualName="" explicitFocusOrder="0" pos="18 136 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rate/Freq. 2:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Parameter 3" id="2fa249da6814e9a3" memberName="par3Label"
         virtualName="" explicitFocusOrder="0" pos="18 176 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ramp scale:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="F2" id="41fd6adb14a8c96c" memberName="f2Slider" virtualName=""
          explicitFocusOrder="0" pos="128 136 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="F3" id="c953bb65cde4ed70" memberName="f3Slider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <LABEL name="Out gain" id="adbbdadd9a4bf9ed" memberName="outLabel" virtualName=""
         explicitFocusOrder="0" pos="18 221 96 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Out gain:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="1" italic="0" justification="33"
         typefaceStyle="Bold"/>
  <SLIDER name="Out gain" id="2504e7bde7658720" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="128 221 320 32" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TOGGLEBUTTON name="Active" id="77d0fb2a1555278a" memberName="onToggle" virtualName=""
                explicitFocusOrder="0" pos="288 56 23 24" buttonText="" connectedEdges="0"
                needsCallback="0" radioGroupId="0" state="1"/>
  <SLIDER name="Q" id="5dde4ff6eea3a5f3" memberName="qSlider" virtualName=""
          explicitFocusOrder="0" pos="128 136 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="BAL" id="51b44fbb80eafd6" memberName="balSlider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="DUR" id="10b02c480dfe82e6" memberName="durSlider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="TYP" id="b33e397d20625c43" memberName="typSlider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="LOG" id="c071b1a7b0bf0c13" memberName="logSlider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="DR" id="60b18cd4ab91b983" memberName="drSlider" virtualName=""
          explicitFocusOrder="0" pos="128 176 320 24" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <LABEL name="Info box" id="8a48cdb446639ef7" memberName="infoLabel"
         virtualName="" explicitFocusOrder="0" pos="16 264 440 24" edTextCol="ff000000"
         edBkgCol="0" labelText="F1 period: 0.3942 sec (12343 samples); sample rate: 44100."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

