/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainUIComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainUIComponent::MainUIComponent (EARMP_ChannelstripAudioProcessor& p)
    : audioProcessor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..

    pre_knobs.setknobimage(knobA_png, knobA_pngSize);
    EqSw.setknobimage(switch_toggle_left_right_png, switch_toggle_left_right_pngSize);


    //[/Constructor_pre]

    Main_slider.reset (new juce::Slider ("MainControl"));
    addAndMakeVisible (Main_slider.get());
    Main_slider->setRange (-60, 10, 1);
    Main_slider->setSliderStyle (juce::Slider::LinearVertical);
    Main_slider->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    Main_slider->addListener (this);

    Main_slider->setBounds (40, 360, 72, 195);

    HF_knob.reset (new juce::Slider ("EQ"));
    addAndMakeVisible (HF_knob.get());
    HF_knob->setRange (20, 500, 20);
    HF_knob->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    HF_knob->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    HF_knob->addListener (this);

    HF_knob->setBounds (0, 168, 72, 72);

    LF_Knob.reset (new juce::Slider ("EQ"));
    addAndMakeVisible (LF_Knob.get());
    LF_Knob->setRange (2500, 18000, 500);
    LF_Knob->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    LF_Knob->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    LF_Knob->addListener (this);

    LF_Knob->setBounds (72, 248, 72, 72);

    PeakFreq_knob.reset (new juce::Slider ("EQ"));
    addAndMakeVisible (PeakFreq_knob.get());
    PeakFreq_knob->setRange (75.0, 1000.0, 1.0);
    PeakFreq_knob->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    PeakFreq_knob->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    PeakFreq_knob->addListener (this);
    PeakFreq_knob->setBounds (0, 248, 72, 72);

    PeakGain_knob.reset (new juce::Slider ("EQ"));
    addAndMakeVisible (PeakGain_knob.get());
    PeakGain_knob->setRange (-12.0, 12.0, 0.1);
    PeakGain_knob->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    PeakGain_knob->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    PeakGain_knob->addListener (this);
    PeakGain_knob->setBounds (72, 168, 72, 72);

    juce__slider.reset (new juce::Slider ("EQbutton"));
    addAndMakeVisible (juce__slider.get());
    juce__slider->setRange (0, 1, 1);
    juce__slider->setSliderStyle (juce::Slider::RotaryHorizontalDrag);
    juce__slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    juce__slider->addListener (this);

    juce__slider->setBounds (8, 48, 50, 50);

    juce__imageButton.reset (new juce::ImageButton ("new button"));
    addAndMakeVisible (juce__imageButton.get());
    juce__imageButton->addListener (this);

    juce__imageButton->setImages (false, true, true,
                                  juce::ImageCache::getFromMemory (BinaryData::OFF_png, BinaryData::OFF_pngSize), 1.000f, juce::Colour (0x00000000),
                                  juce::Image(), 1.000f, juce::Colour (0x00000000),
                                  juce::ImageCache::getFromMemory (BinaryData::ON_png, BinaryData::ON_pngSize), 1.000f, juce::Colour (0x00000000));
    juce__imageButton->setBounds (80, 64, 47, 24);

    Load_button.reset (new juce::TextButton ("Load MP3"));
    addAndMakeVisible (Load_button.get());
    Load_button->setButtonText ("Load");
    Load_button->addListener (this);
    Load_button->setBounds (16, 104, 52, 24);

    Play_button.reset (new juce::TextButton ("Play"));
    addAndMakeVisible (Play_button.get());
    Play_button->setButtonText ("Play");
    Play_button->addListener (this);
    Play_button->setBounds (72, 104, 52, 24);

    Stop_button.reset (new juce::TextButton ("Stop"));
    addAndMakeVisible (Stop_button.get());
    Stop_button->setButtonText ("Stop");
    Stop_button->addListener (this);
    Stop_button->setBounds (16, 132, 52, 24);

    Position_slider.reset (new juce::Slider ("Position"));
    addAndMakeVisible (Position_slider.get());
    Position_slider->setRange (0.0, 1.0, 0.01);
    Position_slider->setSliderStyle (juce::Slider::LinearHorizontal);
    Position_slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    Position_slider->addListener (this);
    Position_slider->setBounds (72, 132, 52, 24);

    File_label.reset (new juce::Label ("FileName", "No file"));
    addAndMakeVisible (File_label.get());
    File_label->setJustificationType (juce::Justification::centredLeft);
    File_label->setColour (juce::Label::textColourId, juce::Colours::white);
    File_label->setBounds (16, 320, 118, 24);


    //[UserPreSize]
    //getNumChildComponents: get the number of knobs or button components

    juce__imageButton->setClickingTogglesState(true);  //stay on or off

    for (int i = 0; i < getNumChildComponents(); i++)
    {
        auto* childcomponents = getChildComponent(i);
        DBG(childcomponents->getName());

        if (auto* knobs = dynamic_cast<Slider*>(childcomponents))  //search components as juce:Slider
        {
            String x = "EQ";
            if (! x.compare(knobs->getName()))  //search the components as EQ group
            {
                DBG(knobs->getName());
                knobs->setLookAndFeel(&pre_knobs);  //set the knob style
            }
        }

        if (auto* button = dynamic_cast<Slider*>(childcomponents))  //search components as juce:Slider
        {
            String x = "EQbutton";
            if (!x.compare(button->getName()))  //search the components as EQ group
            {
                DBG(button->getName());
                button->setLookAndFeel(&EqSw);  //set the knob style
            }
        }
    }
    //[/UserPreSize]

    setSize (150, 600);


    //[Constructor] You can add your own custom stuff here..
    KnobsAttachment[0].reset (new SliderAttachment (p.parameters, "HighPassFc", *HF_knob));
    KnobsAttachment[1].reset (new SliderAttachment (p.parameters, "LowPassFc", *LF_Knob));
    KnobsAttachment[2].reset (new SliderAttachment (p.parameters, "PeakFreq", *PeakFreq_knob));
    KnobsAttachment[3].reset (new SliderAttachment (p.parameters, "PeakGain", *PeakGain_knob));
    buttonsAttachment[0].reset(new ButtonAttachment(p.parameters,"Eq_switch", *juce__imageButton));
    
    //step 4 for paremeter table tree S/R
    KnobsAttachment[4].reset (new SliderAttachment(p.parameters,"Level_control",*Main_slider));
    // p.set_parameters();
    startTimerHz (20);
    //[/Constructor]
}

MainUIComponent::~MainUIComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    KnobsAttachment[0]=nullptr;
    KnobsAttachment[1]=nullptr;
    KnobsAttachment[2]=nullptr;
    buttonsAttachment[0]=nullptr;
    buttonsAttachment[1]=nullptr;
    //[/Destructor_pre]

    Main_slider = nullptr;
    HF_knob = nullptr;
    LF_Knob = nullptr;
    PeakFreq_knob = nullptr;
    PeakGain_knob = nullptr;
    juce__slider = nullptr;
    juce__imageButton = nullptr;
    Load_button = nullptr;
    Play_button = nullptr;
    Stop_button = nullptr;
    Position_slider = nullptr;
    File_label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainUIComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainUIComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainUIComponent::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == Main_slider.get())
    {
        //[UserSliderCode_Main_slider] -- add your slider handling code here..
#if myBugMessage
        DBG("Main Volume: " << Main_slider->getValue());
#endif
        double x = audioProcessor.dBscale(Main_slider->getValue());
        audioProcessor.masterVol=x;
        //[/UserSliderCode_Main_slider]
    }
    else if (sliderThatWasMoved == HF_knob.get())
    {
        //[UserSliderCode_HF_knob] -- add your slider handling code here..
        audioProcessor.control_HighPassfilter(HF_knob->getValue());
        //[/UserSliderCode_HF_knob]
    }
    else if (sliderThatWasMoved == LF_Knob.get())
    {
        //[UserSliderCode_LF_Knob] -- add your slider handling code here..
        audioProcessor.control_LowPassfilter(LF_Knob->getValue());
        //[/UserSliderCode_LF_Knob]
    }
    else if (sliderThatWasMoved == PeakFreq_knob.get())
    {
        audioProcessor.control_PeakEq(PeakFreq_knob->getValue(), PeakGain_knob->getValue());
    }
    else if (sliderThatWasMoved == PeakGain_knob.get())
    {
        audioProcessor.control_PeakEq(PeakFreq_knob->getValue(), PeakGain_knob->getValue());
    }
    else if (sliderThatWasMoved == juce__slider.get())
    {
        //[UserSliderCode_juce__slider] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider]
    }
    else if (sliderThatWasMoved == Position_slider.get())
    {
        if (audioProcessor.isAudioFileLoaded() && Position_slider->isMouseButtonDown())
            audioProcessor.setAudioPosition (Position_slider->getValue());
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainUIComponent::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == juce__imageButton.get())
    {
        //[UserButtonCode_juce__imageButton] -- add your button handler code here..
        audioProcessor.EqSwitch = juce__imageButton->getToggleState();
        //[/UserButtonCode_juce__imageButton]
    }
    else if (buttonThatWasClicked == Load_button.get())
    {
        auto safeThis = juce::Component::SafePointer<MainUIComponent> (this);
        audioFileChooser = std::make_unique<juce::FileChooser> ("Load an audio file",
                                                                juce::File(),
                                                                "*.mp3;*.wav;*.aiff;*.flac");

        audioFileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                                       [safeThis] (const juce::FileChooser& chooser)
                                       {
                                           if (safeThis == nullptr)
                                               return;

                                           auto file = chooser.getResult();

                                           if (file.existsAsFile() && safeThis->audioProcessor.loadAudioFile (file))
                                           {
                                               auto length = juce::jmax (0.01, safeThis->audioProcessor.getAudioLength());
                                               safeThis->Position_slider->setRange (0.0, length, 0.01);
                                               safeThis->Position_slider->setValue (0.0, juce::dontSendNotification);
                                               safeThis->File_label->setText (safeThis->audioProcessor.getLoadedAudioFileName(),
                                                                              juce::dontSendNotification);
                                           }
                                       });
    }
    else if (buttonThatWasClicked == Play_button.get())
    {
        audioProcessor.playLoadedAudio();
    }
    else if (buttonThatWasClicked == Stop_button.get())
    {
        audioProcessor.stopLoadedAudio();
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainUIComponent::timerCallback()
{
    if (audioProcessor.isAudioFileLoaded() && Position_slider != nullptr && ! Position_slider->isMouseButtonDown())
    {
        auto length = juce::jmax (0.01, audioProcessor.getAudioLength());
        Position_slider->setRange (0.0, length, 0.01);
        Position_slider->setValue (audioProcessor.getAudioPosition(), juce::dontSendNotification);
    }
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainUIComponent" componentName=""
                 parentClasses="public juce::Component" constructorParams="EARMP_ChannelstripAudioProcessor&amp; p"
                 variableInitialisers="audioProcessor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="150"
                 initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="MainControl" id="188c58569e09d44b" memberName="Main_slider"
          virtualName="" explicitFocusOrder="0" pos="40 360 72 195" min="-60.0"
          max="10.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="EQ" id="39bc27052fac8a8b" memberName="HF_knob" virtualName=""
          explicitFocusOrder="0" pos="0 152 72 72" min="20.0" max="500.0"
          int="20.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="EQ" id="fdc22485d3289e1f" memberName="LF_Knob" virtualName=""
          explicitFocusOrder="0" pos="72 224 72 72" min="2500.0" max="18000.0"
          int="500.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="EQbutton" id="cdc50d7d483217b9" memberName="juce__slider"
          virtualName="" explicitFocusOrder="0" pos="8 48 50 50" min="0.0"
          max="1.0" int="1.0" style="RotaryHorizontalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <IMAGEBUTTON name="new button" id="41769c74b2517960" memberName="juce__imageButton"
               virtualName="" explicitFocusOrder="0" pos="80 64 47 24" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::OFF_png" opacityNormal="1.0" colourNormal="0"
               resourceOver="" opacityOver="1.0" colourOver="0" resourceDown="BinaryData::ON_png"
               opacityDown="1.0" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

