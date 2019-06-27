#pragma once

#include <vector>
#include "Grain.h"
#include "LiveBuffer.h"
#include "ioformats.h"
#include "tables.h"
#include "types.h"

class GrainStream {
public:
  GrainStream();
  ~GrainStream();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setBufferSize(const LiveBuffer::Second s);
  void setMinimumTimeDelta(const GrainTimeDelta td);
  void setMaximumTimeDelta(const GrainTimeDelta td);
  void setMinimumDelay(const GrainDelay d);
  void setMaximumDelay(const GrainDelay d);
  void setMinimumDuration(const GrainDuration d);
  void setMaximumDuration(const GrainDuration d);
  void setMinimumPitch(const GrainPitch p);
  void setMaximumPitch(const GrainPitch p);
  void setMinimumSkew(const GrainSkew s);
  void setMaximumSkew(const GrainSkew s);
  void setMinimumAmplitude(const GrainAmplitude a);
  void setMaximumAmplitude(const GrainAmplitude a);
  void setEnvelopeFunction(const EnvelopeID id);
  void setMinimumPan(const GrainPan p);
  void setMaximumPan(const GrainPan p);
  // ********************
  StereoOutput process(StereoInput sin);
private:
  typedef std::vector<Grain> InstanceManager;
  // ********************
  const FunctionTable* getPointerToTable(const EnvelopeID id);
  void generateInstanceTimeDelta();
  void instanciateGrain();
  // ********************
  InstanceManager grains;
  LiveBuffer buffer;
  // ********************
  Status status;
  GrainTimeDelta minDeT, maxDeT;
  GrainDelay minDel, maxDel;
  GrainDuration minDur, maxDur;
  GrainPitch minPitch, maxPitch;
  GrainSkew minSkew, maxSkew;
  GrainAmplitude minAmp, maxAmp;
  GrainPan minPan, maxPan;
  EnvelopeID envID;
  FunctionTable bell;
  FunctionTable triangle;
  FunctionTable trapezoid;
  FunctionTable sawtooth;
  FunctionTable rectangle;
  FunctionTable cosineQuarter;
  DiscreteTime t, T;
  SampleRate sampRate;
};
