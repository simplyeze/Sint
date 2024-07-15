/*
  ==============================================================================

    OscComponent.h
    Created: 21 Feb 2021 4:55:21pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent (juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId); // Costruttore per la box di scelta
    ~OscComponent() override;

    // Setto lo sfondo del componente
    void paint (juce::Graphics&) override;
    // Setto le dimensione del componente
    void resized() override;

private:
    // Creo una box per la scelta 
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    // SLider per FM
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmDepthAttachment;
    
    juce::Label waveSelectorLabel { "Wave Type", "Wave Type" };
    juce::Label fmFreqLabel { "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "FM Depth", "FM Depth" };
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
