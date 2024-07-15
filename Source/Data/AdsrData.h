/*
  ==============================================================================

    AdsrData.h
    Created: 7 Feb 2021 2:29:21pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    // Agggiorna i valori dell'ADSR
    void update (const float attack, const float decay, const float sustain, const float release);
    
private:
    // eredita i valori dall'ADSR di juce
    juce::ADSR::Parameters adsrParams;
};
