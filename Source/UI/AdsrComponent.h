/*
  ==============================================================================

    File gestione componenti per il Attack, Decay, Sustain, Release ( ADSR )

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    // Costruttore
    AdsrComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId); 
    ~AdsrComponent() override;

    // Setto lo sfondo del componente
    void paint(juce::Graphics&) override;
    // Setto le dimensioni degli slider
    void resized() override; 

private:

    // Permette di usare uno slider per il controllo/modifica di un certo valore
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    

    // Slider per i parametri
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    juce::Label attackLabel { "Attack", "A" };
    juce::Label decayLabel { "Decay", "D" };
    juce::Label sustainLabel { "Sustain", "S" };
    juce::Label releaseLabel { "Release", "R" };
    
    juce::String componentName {""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
