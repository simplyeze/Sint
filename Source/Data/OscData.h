/*
  ==============================================================================

    OscData.h
    Created: 21 Feb 2021 4:34:01pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    // Scelgo il tipo di onda
    void setWaveType (const int choice);
    // Setto la frequenza dell'onda
    void setWaveFrequency (const int midiNoteNumber);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    void updateFm (const float freq, const float depth);
    
private:
    // Modifica per sample della frequenza
    void processFmOsc (juce::dsp::AudioBlock<float>& block);
    
    // Valori per la modulazione di frequenza
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); } };
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote { 0 };
};
