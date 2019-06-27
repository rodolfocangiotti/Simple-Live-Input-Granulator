#include <cassert>
#include <cmath>
#include <iostream>
#include "Grain.h"
#include "dsputils.h"

Grain::Grain():
  del(0.0),
  dur(0.0),
  pitch(0.0), skew(0.0),
  amp(0.0),
  pan(0.0),
  env(nullptr), buffer(nullptr),
  panner(),
  t(0), T(0),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing Grain class..." << '\n';
#endif
}

Grain::~Grain() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing Grain class..." << '\n';
#endif
}

void Grain::setSampleRate(const SampleRate sr) {
  assert(sr > 0);
  sampRate = sr;
}

void Grain::setBuffer(const LiveBuffer* b) {
  buffer = b;
}

void Grain::setDelay(const GrainDelay d) {
  del = d;
}

void Grain::setDuration(const GrainDuration d) {
  assert(d > 0.0);
  dur = d;
  T = static_cast<DiscreteTime>(d * sampRate);  // Duration in samples...
  //assert(T > 0);
  // XXX With randomly generated very low duration values, casting to an integer-derived data type can set T to zero...
  T = T > 0 ? T : 1;
}

void Grain::setPitch(const GrainPitch p) {
  pitch = p;
}

void Grain::setSkew(const GrainSkew s) {
  skew = s;
}

void Grain::setAmplitude(const GrainAmplitude a) {
  amp = a;
}

void Grain::setEnvelopeFunction(const FunctionTable* ft) {
  env = ft;
}

void Grain::setPan(const GrainPan p) {
  pan = p;
}

void Grain::setPanningFunction(const FunctionTable* ft) {
  panner.pointPanningFunction(ft);
}

StereoOutput Grain::process() {
  assert(env != nullptr);
  assert(buffer != nullptr);
  assert(T > 0); // XXX Considering the comment at line 37, yes, this assertion is almost useless...
  assert(t < T);

  double i = static_cast<double>(t) / static_cast<double>(T) * (env->size() - 1);  // Do not consider guard point, then subtract it from table size...
  long iInt = static_cast<long>(i);
  double iFrac = i - iInt;
  Sample envSamp = computeLinearInterp(env->at(iInt), env->at(iInt + 1), iFrac);

  /*
  double factor = abs(skew) + 1.0;
  double pitchVar = pow(static_cast<double>(t) / static_cast<double>(T), factor);
  pitchVar = skew > 0.0 ? pitchVar : 1.0 - pitchVar;

  double delVar = (pitch - 1.0) * (static_cast<double>(t) / static_cast<double>(sampRate)); // Calculate the variation of delay time taking into account pitch and skew factor...
  Sample buffSamp = buffer->readAfter(del - delVar);
  */

  double sampPeriod = 1.0 / static_cast<double>(sampRate);
  double w = static_cast<double>(t) * sampPeriod;
  double r = pow(static_cast<double>(t) / static_cast<double>(T), skew) * static_cast<double>(T) * sampPeriod * pitch;
  Sample buffSamp = buffer->readAfter(del + (w - r));

  Sample outSamp = buffSamp * envSamp * amp;
  panner.setPan(pan);
  StereoOutput pannerOut = panner.process(outSamp);

  t++;
  return pannerOut;
}

bool Grain::isProcessing() const {
  return t < T ? true: false;
}
