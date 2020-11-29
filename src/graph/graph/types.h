#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>

namespace graph {

  // Id Types
  typedef std::uint32_t gid;      // Graph Id
  typedef std::uint32_t txid;     // Transaction Id
  typedef std::uint32_t pid;      // Page Id
  typedef std::uint8_t cid;       // Concept Id

  // The Null Graph Id Type
  enum GraphIds : gid {
    NullId = 0xFFFFFFFF
  };


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



}
#endif // TYPES_H