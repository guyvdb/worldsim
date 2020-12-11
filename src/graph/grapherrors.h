#ifndef GRAPHERRORS_H
#define GRAPHERRORS_H

#include <cstdint>

// Error Types
typedef std::uint16_t ErrorNo;
enum Errors : ErrorNo {
  ErrorNone,
  ErrorFileNotOpen,
  ErrorFileFailedToOpen,
  ErrorFileAlreadyOpen,
  ErrorFileSeekError,
  ErrorFileFlushError
};

#endif // GRAPHERRORS_H
