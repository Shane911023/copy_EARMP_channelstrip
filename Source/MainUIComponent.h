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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"  //step[3]: ¤Þ¥ÎPluginProcessor¡A¬°¤F¥H«á¾Þ§@audio process
#include "myLookAndFeel.h"
using namespace BinaryData;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainUIComponent  : public juce::Component,
                         public juce::Slider::Listener,
                         public juce::Button::Listener,
                         private juce::Timer
{
public:
    //==============================================================================
    MainUIComponent (EARMP_ChannelstripAudioProcessor& p);
    ~MainUIComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    EARMP_ChannelstripAudioProcessor& audioProcessor;  //step[4]: «Å§i¤Þ¤JEARMP_ChannelstripAudioProcessor¡A»PAUDIO¥\¯àÃìµ²
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void timerCallback() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    std::unique_ptr<SliderAttachment> KnobsAttachment[3];
    std::unique_ptr<ButtonAttachment> buttonsAttachment[2];

    int d=1;

    myLookAndFeelV3 pre_knobs, EqSw;
    std::unique_ptr<juce::FileChooser> audioFileChooser;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> Main_slider;
    std::unique_ptr<juce::Slider> HF_knob;
    std::unique_ptr<juce::Slider> LF_Knob;
    std::unique_ptr<juce::Slider> juce__slider;
    std::unique_ptr<juce::ImageButton> juce__imageButton;
    std::unique_ptr<juce::TextButton> Load_button;
    std::unique_ptr<juce::TextButton> Play_button;
    std::unique_ptr<juce::TextButton> Stop_button;
    std::unique_ptr<juce::Slider> Position_slider;
    std::unique_ptr<juce::Label> File_label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainUIComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

