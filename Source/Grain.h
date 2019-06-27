#pragma once

#include "LiveBuffer.h"
#include "StereoPanner.h"
#include "ioformats.h"
#include "tables.h"
#include "types.h"

class Grain {
public:
  Grain();
  ~Grain();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setBuffer(const LiveBuffer* b);
  void setDelay(const GrainDelay d);
  void setDuration(const GrainDuration d);
  void setPitch(const GrainPitch p);
  void setSkew(const GrainSkew s);
  void setAmplitude(const GrainAmplitude a);
  void setEnvelopeFunction(const FunctionTable* ft);
  void setPan(const GrainPan p);
  void setPanningFunction(const FunctionTable* ft);
  // ********************
  StereoOutput process();
  // ********************
  bool isProcessing() const;
private:
  GrainDelay del;
  GrainDuration dur;
  GrainPitch pitch;
  GrainSkew skew;
  GrainAmplitude amp;
  GrainPan pan;
  const FunctionTable* env;
  const LiveBuffer* buffer;
  // ********************
  StereoPanner panner;
  // ********************
  DiscreteTime t, T;  // Current tau, grain life tau value...
  SampleRate sampRate;
};
