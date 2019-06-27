#include <cassert>
#include <iostream>
#include "GrainStream.h"
#include "commons.h"
#include "dsputils.h"

GrainStream::GrainStream():
  grains(),
  status(OFF),
  minDeT(0.0), maxDeT(0.0),
  minDel(0.0), maxDel(0.0),
  minDur(0.0), maxDur(0.0),
  minPitch(0.0), maxPitch(0.0),
  minSkew(0.0), maxSkew(0.0),
  minAmp(0.0), maxAmp(0.0),
  minPan(0.0), maxPan(0.0),
  envID(BELL_ENVELOPE),
  bell(initBell(4096)), triangle(initTriangle(4096)), trapezoid(initTrapezoid(4096)), sawtooth(initSawtooth(4096)),
  rectangle(initRectangle(4)),
  cosineQuarter(initCosineQuarter(1024)),
  t(0), T(0),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing GrainStream class..." << '\n';
#endif
  grains.reserve(MAX_INSTANCES);
  initRandomSeed();
}

GrainStream::~GrainStream() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing GrainStream class..." << '\n';
#endif
}

void GrainStream::setSampleRate(const SampleRate sr) {
  assert(sr > 0);
  sampRate = sr;
  buffer.setSampleRate(sr);
}

void GrainStream::setBufferSize(const LiveBuffer::Second s) {
  buffer.setSize(s);
}

void GrainStream::setMinimumTimeDelta(const GrainTimeDelta td) {
  minDeT = td;
}

void GrainStream::setMaximumTimeDelta(const GrainTimeDelta td) {
  maxDeT = td;
}

void GrainStream::setMinimumDelay(const GrainDelay d) {
  minDel = d;
}

void GrainStream::setMaximumDelay(const GrainDelay d) {
  maxDel = d;
}

void GrainStream::setMinimumDuration(const GrainDuration d) {
  minDur = d;
}

void GrainStream::setMaximumDuration(const GrainDuration d) {
  maxDur = d;
}

void GrainStream::setMinimumPitch(const GrainPitch p) {
  minPitch = p;
}

void GrainStream::setMaximumPitch(const GrainPitch p) {
  maxPitch = p;
}

void GrainStream::setMinimumSkew(const GrainSkew s) {
  minSkew = s;
}

void GrainStream::setMaximumSkew(const GrainSkew s) {
  maxSkew = s;
}

void GrainStream::setMinimumAmplitude(const GrainAmplitude a) {
  minAmp = a;
}

void GrainStream::setMaximumAmplitude(const GrainAmplitude a) {
  maxAmp = a;
}

void GrainStream::setEnvelopeFunction(const EnvelopeID id) {
  envID = id;
}

void GrainStream::setMinimumPan(const GrainPan p) {
  minPan = p;
}

void GrainStream::setMaximumPan(const GrainPan pr) {
  maxPan = pr;
}

StereoOutput GrainStream::process(StereoInput sin) {
  assert(sampRate > 0);

  // Write input to buffer...
  Sample inLeft = sin.leftSample;
  Sample inRight = sin.rightSample;
  buffer.write((inLeft + inRight) * 0.5);

  // Instanciate new grains...
  if (T - t <= 0) {
    generateInstanceTimeDelta();
    instanciateGrain();
  }

  // Process each grain and write output...
  StereoOutput outStream;
  outStream.leftSample = 0.0;
  outStream.rightSample = 0.0;
  if (!(grains.empty())) {
    for (InstanceManager::iterator i = grains.begin(); i != grains.end(); i) {
      if (i->isProcessing()) {
        StereoOutput grain = i->process();
        outStream.leftSample += grain.leftSample;
        outStream.rightSample += grain.rightSample;
        i++;
      } else {
        grains.erase(i);
      }
    }
  }

  t++;
  return outStream;
}

const FunctionTable* GrainStream::getPointerToTable(const EnvelopeID id) {
  switch (id) {
  case BELL_ENVELOPE:
    return &bell;
  case TRIANGLE_ENVELOPE:
    return &triangle;
  case TRAPEZOID_ENVELOPE:
    return &trapezoid;
  case SAWTOOTH_ENVELOPE:
    return &sawtooth;
  case RECTANGLE_ENVELOPE:
    return &rectangle;
  default:
    return nullptr;
  }
}

void GrainStream::generateInstanceTimeDelta() {
  GrainTimeDelta newDeT = getRandomInRange<GrainTimeDelta>(minDeT, maxDeT);
  t = 0;
  T = static_cast<DiscreteTime>(newDeT * sampRate);
}

void GrainStream::instanciateGrain() {
  if (grains.size() < MAX_INSTANCES) {
    Grain newGrain;

    GrainDelay newDel = getRandomInRange<GrainDelay>(minDel, maxDel);
    GrainDuration newDur = getRandomInRange<GrainDuration>(minDur, maxDur);
    GrainPitch newPitch = getRandomInRange<GrainPitch>(minPitch, maxPitch);
    GrainSkew newSkew = getRandomInRange<GrainSkew>(minSkew, maxSkew);
    GrainAmplitude newAmp = getRandomInRange<GrainAmplitude>(minAmp, maxAmp);
    GrainPan newPan = getRandomInRange<GrainPan>(minPan, maxPan);
    EnvelopeID newEnvID = envID == RANDOM_ENVELOPE ? getRandomInRange<EnvelopeID>(BELL_ENVELOPE, RANDOM_ENVELOPE) : envID;
    std::cout << "newEnvID: " << newEnvID << '\n';

    newGrain.setSampleRate(sampRate);
    newGrain.setBuffer(&buffer);
    newGrain.setDelay(newDel);
    newGrain.setDuration(newDur);
    newGrain.setPitch(newPitch);
    newGrain.setSkew(newSkew);
    newGrain.setAmplitude(newAmp);
    newGrain.setEnvelopeFunction(getPointerToTable(newEnvID));
    newGrain.setPan(newPan);
    newGrain.setPanningFunction(&cosineQuarter);
    grains.push_back(newGrain);
  }
}
