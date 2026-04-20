/*
 ==============================================================================
 
 Created: 14 Dec 2017 10:16:04am
 Author:  Stefan Remberg
 Update: Modified by Rich 2021, fix path problem
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

//==============================================================================

using namespace juce;

//==============================================================================
class myLookAndFeelV3 : public LookAndFeel_V4
{
    
public:
    myLookAndFeelV3();
    
    
    void setknobimage(const char* png,const int pngSize);
//    static void setSizeRatio(float ratio) {
//        lsize= ratio;
//    }
    Label* createSliderTextBox (Slider& slider) override;
    Font getLabelFont (Label& label) override;
    Font getComboBoxFont (ComboBox&) override;

    void set_imgwidth_parameters(int x){ imgwidth_parameters= x;}
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    /*static const Typeface::Ptr getTypefaceForCalibri_Regular_Font()
    {
        static Typeface::Ptr myFont = Typeface::createSystemTypefaceFor(BinaryData::Calibri_Regular_ttf,
            BinaryData::Calibri_Regular_ttfSize);
        return myFont;
    }
    static const Typeface::Ptr getTypefaceForAlluraRegular_Font()
    {
        static Typeface::Ptr myFont = Typeface::createSystemTypefaceFor(BinaryData::AlluraRegular_ttf,
            BinaryData::AlluraRegular_ttfSize);
        
        return myFont;
    }*/
private:
    Image img2;
    float knobheight=1,knobheight_temp=1;
    int imgwidth_parameters=0;
};

//==============================================================================
class mySilder : public LookAndFeel_V1
{
    
public:
    mySilder();
    void drawLinearSlider (Graphics&, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle, Slider&) override;
};
    
