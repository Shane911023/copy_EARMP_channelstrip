/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EARMP_ChannelstripAudioProcessor::EARMP_ChannelstripAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
//Tree store definition
    parameters (*this, nullptr, juce::Identifier (JucePlugin_Name),
            {
    std::make_unique<juce::AudioParameterFloat> (ParameterID { "HighPassFc",  1 },            // parameterID
                                                 "HighPassFc",            // parameter name
                                                 20.0f,              // minimum value
                                                 500.0f,              // maximum value
                                                 250.0f),
    std::make_unique<juce::AudioParameterFloat> (ParameterID { "LowPassFc",1},      // parameterID
                                                 "LowPassFc",     // parameter name
                                                 2500.0f,   // minimum value
                                                      18000.0f,   // maximum value
                                                      5000.0f) ,
        std::make_unique<juce::AudioParameterInt> (ParameterID { "Eq_switch",  1 },      // parameterID
                                                   "Eq_switch",     // parameter name
                                                   0,
                                                   1,
                                                   0),              // default value
        std::make_unique<juce::AudioParameterInt>(ParameterID{"Level_control",1}, "Level_control", -60, 10, 0), //step 2 for paremeter table tree S/R
        
     })
#endif
{
    high_fc_store = parameters.getRawParameterValue ("HighPassFc");
 //   tubeon2 =parameters.getRawParameterValue("Clean_sw");
    low_fc_store = parameters.getRawParameterValue("LowPassFc");
    EqSW_store = parameters.getRawParameterValue("Eq_switch");
    
    //step 3 for paremeter table tree S/R
    level_ctrl = parameters.getRawParameterValue("Level_control");

    audioFormatManager.registerBasicFormats();
}

EARMP_ChannelstripAudioProcessor::~EARMP_ChannelstripAudioProcessor()
{
    //delete HighPass; //Step 5.1: delete ptr
    //delete LowPass;  //Step 5.2: delete ptr

    if (LowPass != nullptr)
    {
        LowPass = nullptr;
    }
    if (HighPass != nullptr)
    {
        HighPass = nullptr;
    }

    audioTransportSource.setSource (nullptr);
}

//==============================================================================
const juce::String EARMP_ChannelstripAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EARMP_ChannelstripAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EARMP_ChannelstripAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EARMP_ChannelstripAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EARMP_ChannelstripAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EARMP_ChannelstripAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EARMP_ChannelstripAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EARMP_ChannelstripAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EARMP_ChannelstripAudioProcessor::getProgramName (int index)
{
    return {};
}

void EARMP_ChannelstripAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EARMP_ChannelstripAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    sampleRate_=sampleRate;
    
    if(LowPass !=nullptr)
    { LowPass=nullptr;}
    if(HighPass !=nullptr)
    { HighPass=nullptr;}
    
    HighPass = new EARMP_Eq;   //Call class ptr
    HighPass->highpass_setup(high_fc.getCurrentValue(), sampleRate, HighPass->a, HighPass->b); //call setup for high pass filter
    
    LowPass = new EARMP_Eq;
    LowPass->lowpass_setup(low_fc.getCurrentValue(), sampleRate, LowPass->a, LowPass->b); //call setup for high pass filter

    {
        const juce::ScopedLock sl (audioTransportLock);
        audioTransportSource.prepareToPlay (samplesPerBlock, sampleRate);
    }
    
#if myBugMessage
    DBG("Sampling Rate: "<<sampleRate);
    DBG("Low a: "<< LowPass->a[0]<<", "<<LowPass->a[1]<<", "<<LowPass->a[2]);
    DBG("Low b: "<< LowPass->b[0]<<", "<<LowPass->b[1]);
    DBG("High a: "<< HighPass->a[0]<<", "<<HighPass->a[1]<<", "<<HighPass->a[2]);
    DBG("High b: "<< HighPass->b[0]<<", "<<HighPass->b[1]);
#endif
}

void EARMP_ChannelstripAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    const juce::ScopedLock sl (audioTransportLock);
    audioTransportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EARMP_ChannelstripAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EARMP_ChannelstripAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto isUsingLoadedAudio = false;

    {
        const juce::ScopedLock sl (audioTransportLock);

        if (audioReaderSource != nullptr)
        {
            isUsingLoadedAudio = true;
            buffer.clear();
            juce::AudioSourceChannelInfo sourceInfo (&buffer, 0, buffer.getNumSamples());
            audioTransportSource.getNextAudioBlock (sourceInfo);
        }
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    const auto eqEnabled = EqSW_store != nullptr ? (EqSW_store->load() > 0.5f) : EqSwitch;
    EqSwitch = eqEnabled;

    const auto channelsToProcess = isUsingLoadedAudio ? totalNumOutputChannels : totalNumInputChannels;

    for (int channel = 0; channel < channelsToProcess; ++channel)
    {
        auto* inputdata = buffer.getReadPointer(channel);
        auto* outputdata = buffer.getWritePointer (channel);
        double x; //buffer
        
        for (int samples=0;samples < buffer.getNumSamples(); ++samples) // Buffer [.] array processing
        {
            
            x=inputdata[samples];
//            DBG("before X:"<<x);
            if (eqEnabled && HighPass != nullptr && LowPass != nullptr) {
                x = HighPass->filterProcess(x, HighPass->a, HighPass->b, HighPass->xbuf[channel], HighPass->ybuf[channel]);
                x = LowPass->filterProcess(x, LowPass->a, LowPass->b, LowPass->xbuf[channel], LowPass->ybuf[channel]); //Processing High Pass filter
            }
            outputdata[samples]=(float) (x *masterVol.getNextValue()) ;   //Read samples in each Buffer
            
            
        }
        // ..do something to the data...
    }
}

//==============================================================================
bool EARMP_ChannelstripAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EARMP_ChannelstripAudioProcessor::createEditor()
{
    return new EARMP_ChannelstripAudioProcessorEditor (*this);
}

//==============================================================================
void EARMP_ChannelstripAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    
    copyXmlToBinary (*xml, destData);
}

void EARMP_ChannelstripAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
        std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    
        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName (parameters.state.getType()))
                parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
              
}

bool EARMP_ChannelstripAudioProcessor::loadAudioFile (const juce::File& file)
{
    std::unique_ptr<juce::AudioFormatReader> reader (audioFormatManager.createReaderFor (file));

    if (reader == nullptr)
        return false;

    auto sourceSampleRate = reader->sampleRate;
    auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader.release(), true);

    {
        const juce::ScopedLock sl (audioTransportLock);
        audioTransportSource.stop();
        audioTransportSource.setSource (nullptr);
        audioReaderSource = std::move (newSource);
        audioTransportSource.setSource (audioReaderSource.get(), 0, nullptr, sourceSampleRate);
        loadedAudioFile = file;
    }

    return true;
}

void EARMP_ChannelstripAudioProcessor::playLoadedAudio()
{
    const juce::ScopedLock sl (audioTransportLock);

    if (audioReaderSource != nullptr)
        audioTransportSource.start();
}

void EARMP_ChannelstripAudioProcessor::stopLoadedAudio()
{
    const juce::ScopedLock sl (audioTransportLock);
    audioTransportSource.stop();
}

void EARMP_ChannelstripAudioProcessor::setAudioPosition (double seconds)
{
    const juce::ScopedLock sl (audioTransportLock);

    if (audioReaderSource != nullptr)
        audioTransportSource.setPosition (juce::jlimit (0.0, audioTransportSource.getLengthInSeconds(), seconds));
}

double EARMP_ChannelstripAudioProcessor::getAudioPosition()
{
    const juce::ScopedLock sl (audioTransportLock);
    return audioTransportSource.getCurrentPosition();
}

double EARMP_ChannelstripAudioProcessor::getAudioLength()
{
    const juce::ScopedLock sl (audioTransportLock);
    return audioTransportSource.getLengthInSeconds();
}

bool EARMP_ChannelstripAudioProcessor::isAudioFileLoaded() const
{
    return loadedAudioFile.existsAsFile();
}

bool EARMP_ChannelstripAudioProcessor::isAudioPlaying()
{
    const juce::ScopedLock sl (audioTransportLock);
    return audioTransportSource.isPlaying();
}

juce::String EARMP_ChannelstripAudioProcessor::getLoadedAudioFileName() const
{
    return loadedAudioFile.existsAsFile() ? loadedAudioFile.getFileName() : juce::String ("No file loaded");
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EARMP_ChannelstripAudioProcessor();
}
