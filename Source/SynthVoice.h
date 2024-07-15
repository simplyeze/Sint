/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Dec 2020 1:55:41pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    // funzioni implementate nel SynthVoice.cpp
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    // Da commentare fino a 38
    void updateFilter (const int filterType, const float frequency, const float resonance);
    
    // Ottengo i valori aggiornati dai Data dei componenti
    OscData& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    FilterData& getFilter() { return filter; }
    
private:
    // buffer aggiuntivo per evitare click
    juce::AudioBuffer<float> synthBuffer;
    
    // Eredito i dati dei vari componenti
    OscData osc;
    AdsrData adsr;
    AdsrData filterAdsr;
    FilterData filter;
    juce::dsp::Gain<float> gain;
    
    bool isPrepared { false };
};
