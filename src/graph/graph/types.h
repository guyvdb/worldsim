#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>

namespace graph {

  // Id Types
  typedef std::uint32_t gid;      // Graph Id
  typedef std::uint32_t txid;     // Transaction Id
  typedef std::uint32_t pid;      // Page Id
  typedef std::uint16_t tid;      // Type Id
  typedef std::uint8_t cid;       // Concept Id
  typedef std::uint8_t stateid;       // Action Id

  const gid InvalidGraphId = 0xFFFFFFFF;

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

  enum DataType : std::uint8_t {
    Complex,
    Integer,
    Float,
    Boolean,
    String,
    DateTime
  };


}
#endif // TYPES_H
