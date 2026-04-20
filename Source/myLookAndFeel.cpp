/*
 ==============================================================================
 
 Original Created: 14 Dec 2017 10:16:04am
 Author:  Stefan Remberg
 Modified by Rich 2021, fix path problem
 ==============================================================================
 */

#include "myLookAndFeel.h"
#include <cmath>
using namespace juce;
//==============================================================================
mySilder::mySilder()
{
}
static void drawTriangle (Graphics& g, float x1, float y1, float x2, float y2, float x3, float y3, Colour fill, Colour outline)
{
    Path p;
    p.addTriangle (x1, y1, x2, y2, x3, y3);
    g.setColour (fill);
    g.fillPath (p);

    g.setColour (outline);
    g.strokePath (p, PathStrokeType (0.3f));
}

void mySilder::drawLinearSlider (Graphics& g,
                                       int x, int y, int w, int h,
                                       float sliderPos, float minSliderPos, float maxSliderPos,
                                       const Slider::SliderStyle style,
                                       Slider& slider)
{
    //g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style == Slider::LinearBar)
    {
        g.setColour (slider.findColour (Slider::thumbColourId));
        g.fillRect (x, y, (int) sliderPos - x, h);

        g.setColour (slider.findColour (Slider::textBoxTextColourId).withMultipliedAlpha (0.5f));
        g.drawRect (x, y, (int) sliderPos - x, h);
    }
    else
    {
        g.setColour (slider.findColour (Slider::trackColourId)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.3f));

        if (slider.isHorizontal())
        {
            g.fillRect (x, y + roundToInt ((float) h * 0.6f),
                        w, roundToInt ((float) h * 0.2f));
        }
        else
        {
            g.fillRect (x + roundToInt ((float) w * 0.5f - jmin (3.0f, (float) w * 0.1f)), y,
                        jmin (4, roundToInt ((float) w * 0.2f)), h);
        }

        float alpha = 0.35f;

        if (slider.isEnabled())
            alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.7f;

        const Colour fill (slider.findColour (Slider::thumbColourId).withAlpha (alpha));
        const Colour outline (Colours::black.withAlpha (slider.isEnabled() ? 0.7f : 0.35f));

        if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
        {
          drawTriangle (g,
                          (float) x + (float) w * 0.5f + jmin (4.0f, (float) w * 0.3f), minSliderPos,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), minSliderPos - 7.0f,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), minSliderPos,
                          fill, outline);

          drawTriangle (g,
                          (float) x + (float) w * 0.5f + jmin (4.0f, (float) w * 0.3f), maxSliderPos,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), maxSliderPos,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), maxSliderPos + 7.0f,
                          fill, outline);
        }
        else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g,
                          minSliderPos, (float) y + (float) h * 0.6f - jmin (4.0f, (float) h * 0.3f),
                          minSliderPos - 7.0f, (float) y + (float) h * 0.9f,
                          minSliderPos, (float) y + (float) h * 0.9f,
                          fill, outline);

            drawTriangle (g,
                          maxSliderPos, (float) y + (float) h * 0.6f - jmin (4.0f, (float) h * 0.3f),
                          maxSliderPos, (float) y + (float) h * 0.9f,
                          maxSliderPos + 7.0f, (float) y + (float) h * 0.9f,
                          fill, outline);
        }

        if (style == Slider::LinearHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g,
                          sliderPos, (float) y + (float) h * 0.9f,
                          sliderPos - 7.0f, (float) y + (float) h * 0.2f,
                          sliderPos + 7.0f, (float) y + (float) h * 0.2f,
                          fill, outline);
        }
        else if (style == Slider::LinearVertical || style == Slider::ThreeValueVertical)
        {
            drawTriangle (g,
                          (float) x + (float) w * 0.5f + jmin (4.0f, (float) w * 0.3f), sliderPos,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), sliderPos - 7.0f,
                          (float) x + (float) w * 0.5f - jmin (8.0f, (float) w * 0.4f), sliderPos + 7.0f,
                          fill, outline);
        }
    }
}

//==============================================================================

//==============================================================================
myLookAndFeelV3::myLookAndFeelV3()
{
}
void myLookAndFeelV3::setknobimage(const char* png,const int pngSize)
{
    img2 = ImageCache::getFromMemory(png, pngSize);
    
}
Label* myLookAndFeelV3::createSliderTextBox (Slider& slider)
{
    auto* l = LookAndFeel_V2::createSliderTextBox (slider);
    slider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    l->setColour (Label::textWhenEditingColourId, Colours::yellow);
//    l->setFont(juce::Font (15.0f, juce::Font::bold));
 //   l->setFont(juce::Font (getTypefaceForCalibri_Regular_Font()).withHeight(15.0f).withStyle(1));
//    DBG( juce::String(15.0f * slider.getHeight()/30.0f));
//        DBG(juce::String(slider.getHeight())));
    return l;
}
Font myLookAndFeelV3::getLabelFont (Label& label)
{
   // label.setFont(juce::Font (getTypefaceForCalibri_Regular_Font()).withHeight(15.0f).withStyle(1));
    return{ jmin (20.0f, (float) label.getHeight() * 0.85f) };
}
Font myLookAndFeelV3::getComboBoxFont (ComboBox& box)
{
    return { jmin (20.0f, (float) box.getHeight() * 0.85f) };
}

//==============================================================================
void myLookAndFeelV3::drawRotarySlider(Graphics& g,
                                       int x, int y, int width, int height, float sliderPos,
                                       float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    if (img2.isValid())
    {
        const double rotation = (slider.getValue()
                                 - slider.getMinimum())
        / (slider.getMaximum()
           - slider.getMinimum());
        
        float frames = 0;
        if(imgwidth_parameters==0)
                frames =  img2.getHeight()/  img2.getWidth();
        else
                frames =  img2.getHeight()/ imgwidth_parameters;
        const int frameId = (int)ceil(rotation * (frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

//        auto* l = LookAndFeel_V2::createSliderTextBox (slider);
//        slider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
//        l->setColour (Label::textWhenEditingColourId, Colours::yellow);
//    //    l->setFont(juce::Font (15.0f, juce::Font::bold));
//        l->setFont(juce::Font (getTypefaceForCalibri_Regular_Font()).withHeight(15.0f*width).withStyle(1));
//        delete(l);
//        g.setFont(juce::Font (getTypefaceForCalibri_Regular_Font()).withHeight(15.0f*width).withStyle(1));
        g.drawImage(img2,
                    (int)rx,
                    (int)ry,
                    2 * (int)radius,
                    2 * (int)radius,
                    0,
                    frameId* img2.getHeight()/frames,//img2.getWidth(),
                    img2.getWidth(),
                    img2.getHeight()/frames);
        
        
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
                                     0.5f * height, width * textPpercent, 0.5f * height);
        
        g.setColour(Colours::white);
        
        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
                         Justification::horizontallyCentred | Justification::centred, 1);
    }
}
