/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleLiveInputGranulatorAudioProcessorEditor  : public AudioProcessorEditor {
public:
  SimpleLiveInputGranulatorAudioProcessorEditor (SimpleLiveInputGranulatorAudioProcessor&);
  ~SimpleLiveInputGranulatorAudioProcessorEditor();

  //==============================================================================
  void paint (Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  SimpleLiveInputGranulatorAudioProcessor& processor;

  Slider minTimeDeltaSlider;
  Label minTimeDeltaLabel;
  Slider maxTimeDeltaSlider;
  Label maxTimeDeltaLabel;
  Slider minDelaySlider;
  Label minDelayLabel;
  Slider maxDelaySlider;
  Label maxDelayLabel;
  Slider minDurationSlider;
  Label minDurationLabel;
  Slider maxDurationSlider;
  Label maxDurationLabel;
  Slider minPitchSlider;
  Label minPitchLabel;
  Slider maxPitchSlider;
  Label maxPitchLabel;
  Slider minSkewSlider;
  Label minSkewLabel;
  Slider maxSkewSlider;
  Label maxSkewLabel;
  Slider minAmplitudeSlider;
  Label minAmplitudeLabel;
  Slider maxAmplitudeSlider;
  Label maxAmplitudeLabel;
  Slider minPanSlider;
  Label minPanLabel;
  Slider maxPanSlider;
  Label maxPanLabel;
  ComboBox envelopeCombo;
  Label envelopeLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleLiveInputGranulatorAudioProcessorEditor)

public:

  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minTimeDeltaValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxTimeDeltaValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minDelayValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxDelayValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minDurationValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxDurationValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minPitchValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxPitchValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minSkewValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxSkewValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minAmplitudeValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxAmplitudeValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minPanValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxPanValue;
  std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> envelopeValue;

};
