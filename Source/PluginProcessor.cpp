/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleLiveInputGranulatorAudioProcessor::SimpleLiveInputGranulatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
  : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                    .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                    .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                   ),
  parameters(*this, nullptr, "SimpleLiveInputGranulatorParams", createParameters()),
#endif
  grainStream() {
  minTimeDelta = parameters.getRawParameterValue("minTimeDelta");
  maxTimeDelta = parameters.getRawParameterValue("maxTimeDelta");
  minDelay = parameters.getRawParameterValue("minDelay");
  maxDelay = parameters.getRawParameterValue("maxDelay");
  minDuration = parameters.getRawParameterValue("minDuration");
  maxDuration = parameters.getRawParameterValue("maxDuration");
  minPitch = parameters.getRawParameterValue("minPitch");
  maxPitch = parameters.getRawParameterValue("maxPitch");
  minSkew = parameters.getRawParameterValue("minSkew");
  maxSkew = parameters.getRawParameterValue("maxSkew");
  minAmplitude = parameters.getRawParameterValue("minAmplitude");
  maxAmplitude = parameters.getRawParameterValue("maxAmplitude");
  minPan = parameters.getRawParameterValue("minPan");
  maxPan = parameters.getRawParameterValue("maxPan");
  envelope = parameters.getRawParameterValue("envelope");
}

SimpleLiveInputGranulatorAudioProcessor::~SimpleLiveInputGranulatorAudioProcessor() {
}

//==============================================================================
const String SimpleLiveInputGranulatorAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool SimpleLiveInputGranulatorAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool SimpleLiveInputGranulatorAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool SimpleLiveInputGranulatorAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double SimpleLiveInputGranulatorAudioProcessor::getTailLengthSeconds() const {
  return 0.0;
}

int SimpleLiveInputGranulatorAudioProcessor::getNumPrograms() {
  return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
  // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleLiveInputGranulatorAudioProcessor::getCurrentProgram() {
  return 0;
}

void SimpleLiveInputGranulatorAudioProcessor::setCurrentProgram (int index) {
}

const String SimpleLiveInputGranulatorAudioProcessor::getProgramName (int index) {
  return {};
}

void SimpleLiveInputGranulatorAudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void SimpleLiveInputGranulatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  initGrainStream();
}

void SimpleLiveInputGranulatorAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleLiveInputGranulatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
  ignoreUnused (layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
      && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

  // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void SimpleLiveInputGranulatorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
  ScopedNoDenormals noDenormals;
  auto totalNumInputChannels  = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.
  auto* leftChan = buffer.getWritePointer(0);
  auto* rightChan = buffer.getWritePointer(1);

  setGrainStreamParams();

  for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
    StereoInput in;
    in.leftSample = leftChan[sample];
    in.rightSample = rightChan[sample];
    StereoOutput out = grainStream.process(in);
    leftChan[sample] = out.leftSample;
    rightChan[sample] = out.rightSample;
  }
}

//==============================================================================
bool SimpleLiveInputGranulatorAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleLiveInputGranulatorAudioProcessor::createEditor() {
  return new SimpleLiveInputGranulatorAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleLiveInputGranulatorAudioProcessor::getStateInformation (MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.

  auto state = parameters.copyState();
  std::unique_ptr<XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void SimpleLiveInputGranulatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.

  std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
  if (xmlState.get() != nullptr) {
    if (xmlState->hasTagName(parameters.state.getType())) {
      parameters.replaceState(ValueTree::fromXml(*xmlState));
    }
  }

}

// ********************
AudioProcessorValueTreeState::ParameterLayout SimpleLiveInputGranulatorAudioProcessor::createParameters() {
  std::vector<std::unique_ptr<RangedAudioParameter>> params;

  params.push_back(std::make_unique<AudioParameterFloat>("minTimeDelta", "Min. Time Delta", NormalisableRange<float>(1.0, 500.0, 0.1, 0.33333), 50.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxTimeDelta", "Max. Time Delta", NormalisableRange<float>(1.0, 500.0, 0.1, 0.33333), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minDelay", "Min. Delay", NormalisableRange<float>(1.0, 5000.0, 0.1, 0.5), 50.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxDelay", "Max. Delay", NormalisableRange<float>(1.0, 5000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minDuration", "Min. Duration", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxDuration", "Max. Duration", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 500.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minPitch", "Min. Pitch", NormalisableRange<float>(0.1, 10.0, 0.001, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxPitch", "Max. Pitch", NormalisableRange<float>(0.1, 10.0, 0.001, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minSkew", "Min. Skew", NormalisableRange<float>(0.1, 10.0, 0.001, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxSkew", "Max. Skew", NormalisableRange<float>(0.1, 10.0, 0.001, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minAmplitude", "Min. Amplitude", NormalisableRange<float>(0.0, 1.0, 0.001, 0.5), 0.50));
  params.push_back(std::make_unique<AudioParameterFloat>("maxAmplitude", "Max. Amplitude", NormalisableRange<float>(0.0, 1.0, 0.001, 0.5), 0.75));
  params.push_back(std::make_unique<AudioParameterChoice>("envelope", "Envelope", StringArray("Bell", "Triangle", "Trapezoid", "Sawtooth", "Rectangle", "Random"), 0));
  params.push_back(std::make_unique<AudioParameterFloat>("minPan", "Min. Pan", NormalisableRange<float>(0.0, 1.0, 0.01, 1.0), 0.5));
  params.push_back(std::make_unique<AudioParameterFloat>("maxPan", "Max. Pan", NormalisableRange<float>(0.0, 1.0, 0.01, 1.0), 0.5));

  return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new SimpleLiveInputGranulatorAudioProcessor();
}

void SimpleLiveInputGranulatorAudioProcessor::initGrainStream() {
  setGrainStreamParams();
}

void SimpleLiveInputGranulatorAudioProcessor::setGrainStreamParams() {
  //std::cout << "Before limit:\t" << *minTimeDelta << '\t' << *maxTimeDelta << '\n';

  *minTimeDelta = *minTimeDelta >= *maxTimeDelta ? *maxTimeDelta : *minTimeDelta;
  *maxTimeDelta = *maxTimeDelta <= *minTimeDelta ? *minTimeDelta : *maxTimeDelta;
  *minDelay = *minDelay >= *maxDelay ? *maxDelay : *minDelay;
  *maxDelay = *maxDelay <= *minDelay ? *minDelay : *maxDelay;
  *minDuration = *minDuration >= *maxDuration ? *maxDuration : *minDuration;
  *maxDuration = *maxDuration <= *minDuration ? *minDuration : *maxDuration;
  *minPitch = *minPitch >= *maxPitch ? *maxPitch : *minPitch;
  *maxPitch = *maxPitch <= *minPitch ? *minPitch : *maxPitch;
  *minSkew = *minSkew >= *maxSkew ? *maxSkew : *minSkew;
  *maxSkew = *maxSkew <= *minSkew ? *minSkew : *maxSkew;
  *minAmplitude = *minAmplitude >= *maxAmplitude ? *maxAmplitude : *minAmplitude;
  *maxAmplitude = *maxAmplitude <= *minAmplitude ? *minAmplitude : *maxAmplitude;
  *minPan = *minPan >= *maxPan ? *maxPan : *minPan;
  *maxPan = *maxPan <= *minPan ? *minPan : *maxPan;

  //std::cout << "After limit:\t" << *minTimeDelta << '\t' << *maxTimeDelta << '\n';

  grainStream.setSampleRate(getSampleRate());
  grainStream.setBufferSize(5.0);
  grainStream.setMinimumTimeDelta(*minTimeDelta * 0.001);
  grainStream.setMaximumTimeDelta(*maxTimeDelta * 0.001);
  grainStream.setMinimumDelay(*minDelay * 0.001);
  grainStream.setMaximumDelay(*maxDelay * 0.001);
  grainStream.setMinimumDuration(*minDuration * 0.001);
  grainStream.setMaximumDuration(*maxDuration * 0.001);
  grainStream.setMinimumPitch(*minPitch);
  grainStream.setMaximumPitch(*maxPitch);
  grainStream.setMinimumSkew(*minSkew);
  grainStream.setMaximumSkew(*maxSkew);
  grainStream.setMinimumAmplitude(*minAmplitude);
  grainStream.setMaximumAmplitude(*maxAmplitude);
  grainStream.setMinimumPan(*minPan);
  grainStream.setMaximumPan(*maxPan);
  
  EnvelopeID eid = static_cast<EnvelopeID>(*envelope);
  grainStream.setEnvelopeFunction(eid);
}
