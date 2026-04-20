/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#ifndef myBugMessage
    #define myBugMessage 0
 
#endif


#include <JuceHeader.h>
#include "EARMP_Eq.h"    // Step1: call Eq function

//==============================================================================
/**
*/
class EARMP_ChannelstripAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    EARMP_ChannelstripAudioProcessor();
    ~EARMP_ChannelstripAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool loadAudioFile (const juce::File& file);
    void playLoadedAudio();
    void stopLoadedAudio();
    void setAudioPosition (double seconds);
    double getAudioPosition();
    double getAudioLength();
    bool isAudioFileLoaded() const;
    bool isAudioPlaying();
    juce::String getLoadedAudioFileName() const;

    void control_LowPassfilter(double fc)  //Step 7:UI control link function
    {
        low_fc = fc;
        if(LowPass !=nullptr)
        {
            LowPass = new EARMP_Eq;
            LowPass->lowpass_setup(low_fc.getNextValue(), sampleRate_, LowPass->a, LowPass->b); //call setup for high pass filter
            
        }
        else
            LowPass->lowpass_setup(low_fc.getNextValue(), sampleRate_, LowPass->a, LowPass->b); //call setup for high pass filter
#if myBugMessage
        DBG("Detected LowPass Knob");
        DBG("Sampling Rate: "<<sampleRate_);
        DBG("Low a: "<< LowPass->a[0]<<", "<<LowPass->a[1]<<", "<<LowPass->a[2]);
        DBG("Low b: "<< LowPass->b[0]<<", "<<LowPass->b[1]);
#endif
    }
    void control_HighPassfilter(double fc) //Step 7:UI control link function
    {
        high_fc = fc;
        if(HighPass !=nullptr)
        {
            HighPass = new EARMP_Eq;
            HighPass->highpass_setup(high_fc.getNextValue(), sampleRate_, HighPass->a, HighPass->b); //call setup for high pass filter
            
        }
        else
            HighPass->highpass_setup(high_fc.getNextValue(), sampleRate_, HighPass->a, HighPass->b); //call setup for high pass filter
        
#if myBugMessage
        DBG("Detected HighPass Knob");
        DBG("Sampling Rate: "<<sampleRate_);
        DBG("High a: "<< HighPass->a[0]<<", "<<HighPass->a[1]<<", "<<HighPass->a[2]);
        DBG("High b: "<< HighPass->b[0]<<", "<<HighPass->b[1]);
#endif
    }
    
    double dBscale(double x)
    {
       double y = juce::Decibels::decibelsToGain(x);
       DBG("gain:" << x);
       DBG("dB_gain:" << y);
       return y;
    }

    juce::LinearSmoothedValue<double> masterVol {1};
    bool EqSwitch = false;
    
    //Tree store
    juce::AudioProcessorValueTreeState parameters;
    
    void set_parameters()
    {
        low_fc = (double)*low_fc_store;
        high_fc =(double) *high_fc_store;
        EqSwitch=(bool) *EqSW_store;
    }
private:
    
    std::atomic<float>* low_fc_store =nullptr;
    std::atomic<float>* high_fc_store =nullptr;
    std::atomic<float>* EqSW_store =nullptr;
    std::atomic<float>* level_ctrl =nullptr; //step 1 for paremeter table tree S/R
    
    EARMP_Eq *LowPass, *HighPass;   //Step 3: define a instancePtr function class indicate to Eq class
    juce::LinearSmoothedValue<double> low_fc {8000};
    juce::LinearSmoothedValue<double> high_fc {200};
    double sampleRate_=44100;

    juce::AudioFormatManager audioFormatManager;
    juce::AudioTransportSource audioTransportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> audioReaderSource;
    juce::CriticalSection audioTransportLock;
    juce::File loadedAudioFile;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EARMP_ChannelstripAudioProcessor)
};
