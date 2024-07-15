/*
  ==============================================================================

    SynthVoice.cpp
    Created: 10 Dec 2020 1:55:41pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "SynthVoice.h"

// Controllo se può riprodurre un suono
bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency (midiNoteNumber);
    adsr.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    filterAdsr.noteOff();
    
    if (! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    // Settaggio parametri di process
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    // Inizializzazione componenti
    osc.prepareToPlay (spec);
    filterAdsr.setSampleRate (sampleRate);
    filter.prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
    adsr.setSampleRate (sampleRate);
    gain.prepare (spec);
    
    gain.setGainLinear (0.3f);
    
    // Conferma tutto è pronto
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    // Controllo se è pronto
    jassert (isPrepared);
    
    if (! isVoiceActive())
        return;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    filterAdsr.applyEnvelopeToBuffer (outputBuffer, 0, numSamples);
    synthBuffer.clear();
        
    // VD
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock (audioBlock);
    // VD
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    // VD
    filter.process (synthBuffer);
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (! adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::updateFilter (const int filterType, const float frequency, const float resonance)
{
    auto modulator = filterAdsr.getNextSample();
    filter.updateParameters (modulator, filterType, frequency, resonance);
}
