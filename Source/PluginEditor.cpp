/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleLiveInputGranulatorAudioProcessorEditor::SimpleLiveInputGranulatorAudioProcessorEditor (SimpleLiveInputGranulatorAudioProcessor& p)
  : AudioProcessorEditor (&p), processor (p) {
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize (400, 750);

  // TODO Improve this class constructor in order to avoid repetition of the following code blocks!

  minTimeDeltaValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minTimeDelta", minTimeDeltaSlider);

  minTimeDeltaSlider.setBounds(5, 5, 300, 45);
  minTimeDeltaSlider.setSliderStyle(Slider::LinearHorizontal);
  minTimeDeltaSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minTimeDeltaSlider.setTextValueSuffix(" ms");
  minTimeDeltaSlider.onValueChange = [this] {
    if (minTimeDeltaSlider.getValue() >= maxTimeDeltaSlider.getValue()) {
      maxTimeDeltaSlider.setValue(minTimeDeltaSlider.getValue());
    }
  };
  addAndMakeVisible(minTimeDeltaSlider);

  minTimeDeltaLabel.setBounds(305, 5, 80, 40);
  minTimeDeltaLabel.setText("Min. Time Delta", dontSendNotification);
  minTimeDeltaLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minTimeDeltaLabel);

  // ********************

  maxTimeDeltaValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxTimeDelta", maxTimeDeltaSlider);

  maxTimeDeltaSlider.setBounds(5, 55, 300, 45);
  maxTimeDeltaSlider.setSliderStyle(Slider::LinearHorizontal);
  maxTimeDeltaSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxTimeDeltaSlider.setTextValueSuffix(" ms");
  maxTimeDeltaSlider.onValueChange = [this] {
    if (maxTimeDeltaSlider.getValue() <= minTimeDeltaSlider.getValue()) {
      minTimeDeltaSlider.setValue(maxTimeDeltaSlider.getValue());
    }
  };
  addAndMakeVisible(maxTimeDeltaSlider);

  maxTimeDeltaLabel.setBounds(305, 55, 80, 40);
  maxTimeDeltaLabel.setText("Max. Time Delta", dontSendNotification);
  maxTimeDeltaLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxTimeDeltaLabel);

  // ********************

  minDelaySlider.setBounds(5, 105, 300, 45);
  minDelaySlider.setSliderStyle(Slider::LinearHorizontal);
  minDelaySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minDelaySlider.setTextValueSuffix(" ms");
  minDelaySlider.onValueChange = [this] {
    if (minDelaySlider.getValue() >= maxDelaySlider.getValue()) {
      maxDelaySlider.setValue(minDelaySlider.getValue());
    }
  };
  addAndMakeVisible(minDelaySlider);

  minDelayLabel.setBounds(305, 105, 80, 40);
  minDelayLabel.setText("Min. Delay", dontSendNotification);
  minDelayLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minDelayLabel);

  minDelayValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minDelay", minDelaySlider);

  // ********************

  maxDelaySlider.setBounds(5, 155, 300, 45);
  maxDelaySlider.setSliderStyle(Slider::LinearHorizontal);
  maxDelaySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxDelaySlider.setTextValueSuffix(" ms");
  maxDelaySlider.onValueChange = [this] {
    if (maxDelaySlider.getValue() <= minDelaySlider.getValue()) {
      minDelaySlider.setValue(maxDelaySlider.getValue());
    }
  };
  addAndMakeVisible(maxDelaySlider);

  maxDelayLabel.setBounds(305, 155, 80, 40);
  maxDelayLabel.setText("Max. Delay", dontSendNotification);
  maxDelayLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxDelayLabel);

  maxDelayValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxDelay", maxDelaySlider);

  // ********************

  minDurationSlider.setBounds(5, 205, 300, 45);
  minDurationSlider.setSliderStyle(Slider::LinearHorizontal);
  minDurationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minDurationSlider.setTextValueSuffix(" ms");
  minDurationSlider.onValueChange = [this] {
    if (minDurationSlider.getValue() >= maxDurationSlider.getValue()) {
      maxDurationSlider.setValue(minDurationSlider.getValue());
    }
  };
  addAndMakeVisible(minDurationSlider);

  minDurationLabel.setBounds(305, 205, 80, 40);
  minDurationLabel.setText("Min. Duration", dontSendNotification);
  minDurationLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minDurationLabel);

  minDurationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minDuration", minDurationSlider);

  // ********************

  maxDurationSlider.setBounds(5, 255, 300, 45);
  maxDurationSlider.setSliderStyle(Slider::LinearHorizontal);
  maxDurationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxDurationSlider.setTextValueSuffix(" ms");
  maxDurationSlider.onValueChange = [this] {
    if (maxDurationSlider.getValue() <= minDurationSlider.getValue()) {
      minDurationSlider.setValue(maxDurationSlider.getValue());
    }
  };
  addAndMakeVisible(maxDurationSlider);

  maxDurationLabel.setBounds(305, 255, 80, 40);
  maxDurationLabel.setText("Max. Duration", dontSendNotification);
  maxDurationLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxDurationLabel);

  maxDurationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxDuration", maxDurationSlider);

  // ********************

  minPitchSlider.setBounds(5, 305, 300, 45);
  minPitchSlider.setSliderStyle(Slider::LinearHorizontal);
  minPitchSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minPitchSlider.onValueChange = [this] {
    if (minPitchSlider.getValue() >= maxPitchSlider.getValue()) {
      maxPitchSlider.setValue(minPitchSlider.getValue());
    }
  };
  addAndMakeVisible(minPitchSlider);

  minPitchLabel.setBounds(305, 305, 80, 40);
  minPitchLabel.setText("Min. Pitch", dontSendNotification);
  minPitchLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minPitchLabel);

  minPitchValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minPitch", minPitchSlider);

  // ********************

  maxPitchSlider.setBounds(5, 355, 300, 45);
  maxPitchSlider.setSliderStyle(Slider::LinearHorizontal);
  maxPitchSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxPitchSlider.onValueChange = [this] {
    if (maxPitchSlider.getValue() <= minPitchSlider.getValue()) {
      minPitchSlider.setValue(maxPitchSlider.getValue());
    }
  };
  addAndMakeVisible(maxPitchSlider);

  maxPitchLabel.setBounds(305, 355, 80, 40);
  maxPitchLabel.setText("Max. Pitch ", dontSendNotification);
  maxPitchLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxPitchLabel);

  maxPitchValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxPitch", maxPitchSlider);

  // ********************

  minSkewSlider.setBounds(5, 405, 300, 45);
  minSkewSlider.setSliderStyle(Slider::LinearHorizontal);
  minSkewSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minSkewSlider.onValueChange = [this] {
    if (minSkewSlider.getValue() >= maxSkewSlider.getValue()) {
      maxSkewSlider.setValue(minSkewSlider.getValue());
    }
  };
  addAndMakeVisible(minSkewSlider);

  minSkewLabel.setBounds(305, 405, 80, 40);
  minSkewLabel.setText("Min. Skew", dontSendNotification);
  minSkewLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minSkewLabel);

  minSkewValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minSkew", minSkewSlider);

  // ********************

  maxSkewSlider.setBounds(5, 455, 300, 45);
  maxSkewSlider.setSliderStyle(Slider::LinearHorizontal);
  maxSkewSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxSkewSlider.onValueChange = [this] {
    if (maxSkewSlider.getValue() <= minSkewSlider.getValue()) {
      minSkewSlider.setValue(maxSkewSlider.getValue());
    }
  };
  addAndMakeVisible(maxSkewSlider);

  maxSkewLabel.setBounds(305, 455, 80, 40);
  maxSkewLabel.setText("Max. Skew ", dontSendNotification);
  maxSkewLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxSkewLabel);

  maxSkewValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxSkew", maxSkewSlider);

  // ********************

  minAmplitudeSlider.setBounds(5, 505, 300, 45);
  minAmplitudeSlider.setSliderStyle(Slider::LinearHorizontal);
  minAmplitudeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minAmplitudeSlider.onValueChange = [this] {
    if (minAmplitudeSlider.getValue() >= maxAmplitudeSlider.getValue()) {
      maxAmplitudeSlider.setValue(minAmplitudeSlider.getValue());
    }
  };
  addAndMakeVisible(minAmplitudeSlider);

  minAmplitudeLabel.setBounds(305, 505, 80, 40);
  minAmplitudeLabel.setText("Min. Amplitude", dontSendNotification);
  minAmplitudeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minAmplitudeLabel);

  minAmplitudeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minAmplitude", minAmplitudeSlider);

  // ********************

  maxAmplitudeSlider.setBounds(5, 555, 300, 45);
  maxAmplitudeSlider.setSliderStyle(Slider::LinearHorizontal);
  maxAmplitudeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxAmplitudeSlider.onValueChange = [this] {
    if (maxAmplitudeSlider.getValue() <= minAmplitudeSlider.getValue()) {
      minAmplitudeSlider.setValue(maxAmplitudeSlider.getValue());
    }
  };
  addAndMakeVisible(maxAmplitudeSlider);

  maxAmplitudeLabel.setBounds(305, 555, 80, 40);
  maxAmplitudeLabel.setText("Max. Amplitude", dontSendNotification);
  maxAmplitudeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxAmplitudeLabel);

  maxAmplitudeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxAmplitude", maxAmplitudeSlider);

  // ********************

  minPanSlider.setBounds(5, 605, 300, 45);
  minPanSlider.setSliderStyle(Slider::LinearHorizontal);
  minPanSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minPanSlider.onValueChange = [this] {
    if (minPanSlider.getValue() >= maxPanSlider.getValue()) {
      maxPanSlider.setValue(minPanSlider.getValue());
    }
  };
  addAndMakeVisible(minPanSlider);

  minPanLabel.setBounds(305, 605, 80, 40);
  minPanLabel.setText("Min. Pan", dontSendNotification);
  minPanLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minPanLabel);

  minPanValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minPan", minPanSlider);

  // ********************

  maxPanSlider.setBounds(5, 655, 300, 45);
  maxPanSlider.setSliderStyle(Slider::LinearHorizontal);
  maxPanSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxPanSlider.onValueChange = [this] {
    if (maxPanSlider.getValue() <= minPanSlider.getValue()) {
      minPanSlider.setValue(maxPanSlider.getValue());
    }
  };
  addAndMakeVisible(maxPanSlider);

  maxPanLabel.setBounds(305, 655, 80, 40);
  maxPanLabel.setText("Max. Pan", dontSendNotification);
  maxPanLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxPanLabel);

  maxPanValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxPan", maxPanSlider);

  // ********************

  envelopeCombo.setBounds(5, 705, 295, 40);
  envelopeCombo.setJustificationType(Justification::centred);
  envelopeCombo.addItem("Bell", 1);
  envelopeCombo.addItem("Triangle", 2);
  envelopeCombo.addItem("Trapezoid", 3);
  envelopeCombo.addItem("Sawtooth", 4);
  envelopeCombo.addItem("Rectangle", 5);
  envelopeCombo.addItem("Random", 6);
  addAndMakeVisible(envelopeCombo);

  envelopeLabel.setBounds(305, 705, 80, 40);
  envelopeLabel.setText("Envelope Shape", dontSendNotification);
  envelopeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(envelopeLabel);

  envelopeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.parameters, "envelope", envelopeCombo);

}

SimpleLiveInputGranulatorAudioProcessorEditor::~SimpleLiveInputGranulatorAudioProcessorEditor() {
}

//==============================================================================
void SimpleLiveInputGranulatorAudioProcessorEditor::paint (Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

  g.setColour (Colours::white);
  g.setFont (15.0f);
  //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void SimpleLiveInputGranulatorAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
}
