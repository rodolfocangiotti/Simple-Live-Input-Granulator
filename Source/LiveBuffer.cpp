#include <cassert>
#include <cmath>
#include <iostream>
#include "LiveBuffer.h"
#include "dsputils.h"

LiveBuffer::LiveBuffer():
  buffer(),
  writeIndx(0),
  size(0.0),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing LiveBuffer class..." << '\n';
#endif
}

LiveBuffer::~LiveBuffer() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing LiveBuffer class..." << '\n';
#endif
}

void LiveBuffer::setSampleRate(const SampleRate sr) {
  sampRate = sr;
}

void LiveBuffer::setSize(const Second s) {
  if (s != size) {
    assert(sampRate > 0);
    buffer.resize(s * sampRate);
    for (int i = 0; i < buffer.size(); i++) {
      buffer[i] = 0.0;
    }
    size = s;
  }
}

void LiveBuffer::write(const Sample s) {
  buffer[writeIndx] = s;
  writeIndx++;
  if (writeIndx >= buffer.size()) {
    writeIndx = 0;
  }
}

Sample LiveBuffer::readAfter(const Second s) const {
  //assert(s >= 0.0);
  //assert(s < size);
  assert(sampRate > 0);

  double wrapSecs = s;
  while (wrapSecs < 0.0 || wrapSecs >= size) {  // Simple wrapping block...
    if (wrapSecs >= size) {
      wrapSecs -= size;
    }
    wrapSecs *= -1;
  }

  double i = writeIndx - wrapSecs * sampRate;
  i = i > 0.0 ? i : i + buffer.size();
  long iInt = static_cast<int>(i);
  double iFrac = i - iInt;
  long jInt = iInt + 1;
  jInt = jInt < buffer.size() ? jInt : jInt - buffer.size();
  return computeLinearInterp(buffer[iInt], buffer[jInt], iFrac);
}
