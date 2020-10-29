#ifndef ERROR_H
#define ERROR_H

#include <cstdint>

namespace graph {

  typedef std::uint16_t ErrorNo;

  enum Errors : ErrorNo {
    ErrorNone,
    ErrorFileNotOpen,
    ErrorFileFailedToOpen,
    ErrorFileAlreadyOpen,
    ErrorFileSeekError,
    ErrorFileFlushError
  };

}

#endif // ERROR_H
