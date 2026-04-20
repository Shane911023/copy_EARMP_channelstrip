/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EARMP_ChannelstripAudioProcessorEditor::EARMP_ChannelstripAudioProcessorEditor (EARMP_ChannelstripAudioProcessor& p) 
    : AudioProcessorEditor (&p), audioProcessor (p), MainUI(p) //step[8]:©I¥s¶Ç»¼ , MainUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (150, 600);   //step[9]: §ó§ïµøµ¡­¶­±¤j¤p
    addAndMakeVisible(MainUI);  //step[10]: ©I¥sÅã¥Ü¦¹µøµ¡¤¸¥ó
}

EARMP_ChannelstripAudioProcessorEditor::~EARMP_ChannelstripAudioProcessorEditor()
{
}

//==============================================================================
void EARMP_ChannelstripAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   /* g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
}

void EARMP_ChannelstripAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
