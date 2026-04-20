/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainUIComponent.h"//step[1]: ¤Þ¥ÎMainUIComponent
//==============================================================================
/**
*/
class EARMP_ChannelstripAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EARMP_ChannelstripAudioProcessorEditor (EARMP_ChannelstripAudioProcessor&);
    ~EARMP_ChannelstripAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EARMP_ChannelstripAudioProcessor& audioProcessor;

    MainUIComponent MainUI;  //step[2]: «Å§i¹êÅé¤ÆªºMainUIComponent

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EARMP_ChannelstripAudioProcessorEditor)
};
