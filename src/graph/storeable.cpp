#include "storeable.h"

namespace graph {


  Storeable::Storeable(gid id) : m_id(id) {

  }
  Storeable::~Storeable() {

  }



  void Storeable::SetUInt8(std::uint8_t value, char *data) {
    data[0] = (char)value;
  }

  void Storeable::SetUInt16(std::uint16_t value, char *data) {
    data[0] = (char)(value >> 8);
    data[1] = (char)value;
  }

  void Storeable::SetUInt32(std::uint32_t value, char *data) {
    data[0] = (char)(value >> 24);
    data[1] = (char)(value >> 16);
    data[2] = (char)(value >> 8);
    data[3] = (char)value;
  }

  std::uint8_t Storeable::GetUInt8(const char *data) {
    return (std::uint8_t)data[0];
  }

  std::uint16_t Storeable::GetUInt16(const char *data) {
    return (std::uint16_t)((data[0] << 8) + data[1]);
  }

  std::uint32_t Storeable::GetUInt32(const char *data) {
    return (std::uint32_t)((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
  }

}
