#pragma once

#include "ioformats.h"
#include "tables.h"
#include "types.h"

class StereoPanner {
public:
  typedef double Pan;
  StereoPanner();
  ~StereoPanner();
  // ********************
  void setPan(Pan p);
  void pointPanningFunction(const FunctionTable* ft);
  // ********************
  StereoOutput process(const Sample i);
private:
  Pan panVal;
  const FunctionTable* funcTab;
};
