#include "buffer.h"
#include <cassert>
#include <iostream>

namespace graph {


  ByteBuffer::ByteBuffer() {

  }

  ByteBuffer::ByteBuffer(std::size_t len) {
    this->m_data.reserve(len);
  }

  ByteBuffer::ByteBuffer(ByteBuffer *buf) {

    std::cout << "BUFFER copy from " << ((long)buf) << "\n";

    this->Reserve(buf->Size());
    std::uint8_t *ptr = buf->Data();
    for(std::size_t i =0; i<buf->Size();i++) {
      this->m_data.push_back(ptr[i]);
    }

    std::cout << "copy complete\n";
  }

  void ByteBuffer::Append(std::uint8_t value) {
    this->m_data.push_back(value);
  }

  void ByteBuffer::Append(std::uint8_t *buffer, std::size_t len) {
    for(std::size_t i=0;i<len;i++) {
      this->m_data.push_back(buffer[i]);
    }
  }

  void ByteBuffer::Reserve(std::size_t len) {
    this->m_data.reserve(len);
  }


  void ByteBuffer::Set(int offset, std::uint8_t value) {
    this->m_data[offset] = value;
  }

  void ByteBuffer::Set(int offset, std::uint16_t value) {
    this->m_data[offset] = (std::uint8_t)(value >> 8);
    this->m_data[offset+1] = (std::uint8_t)value;
  }

  void ByteBuffer::Set(int offset, std::uint32_t value) {
    this->m_data[offset] = (std::uint8_t)(value >> 24);
    this->m_data[offset+1] = (std::uint8_t)(value >> 16);
    this->m_data[offset+2] = (std::uint8_t)(value >> 8);
    this->m_data[offset+3] = (std::uint8_t)value;
  }

  void ByteBuffer::Set(int offset, std::uint64_t value) {
    assert(false); // not implemented
  }

  uint8_t ByteBuffer::GetUint8(int offset) {
    return this->m_data[offset];
  }

  uint16_t ByteBuffer::GetUint16(int offset) {
     return (std::uint16_t)((this->m_data[offset] << 8) + this->m_data[offset+1]);
  }

  uint32_t ByteBuffer::GetUint32(int offset) {
    return (std::uint32_t)((this->m_data[offset] << 24) +
                           (this->m_data[offset+1] << 16) +
                           (this->m_data[offset+2] << 8) +
                            this->m_data[offset+3]);
  }

  uint64_t ByteBuffer::GetUint64(int offset) {
    assert(false); // not implemented
  }


}