#pragma once

#include <vector>
#include "types.h"

class LiveBuffer {
public:
  typedef int64_t Index;
  typedef double Second;
  // ********************
  LiveBuffer();
  ~LiveBuffer();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setSize(const Second s);
  // ********************
  void write(const Sample s);
  Sample readAfter(const Second s) const;
private:
  std::vector<Sample> buffer;
  Index writeIndx;
  Second size;
  SampleRate sampRate;
};
