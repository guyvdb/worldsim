#include "bytebuffer.h"
#include <iostream>
#include <cassert>

namespace graph {



  ByteBuffer::ByteBuffer() : m_buf(0x0) {
    this->m_buf = new std::vector<char>();
  }

  ByteBuffer::ByteBuffer(char *data, std::size_t size) : m_buf(0x0) {
    this->m_buf = new std::vector<char>(size);
    for(int i=0;i<(int)size;i++) {
      this->m_buf->push_back(data[i]);
    }
  }

  ByteBuffer::ByteBuffer(std::size_t size) : m_buf(0x0) {
    this->m_buf = new std::vector<char>(size);
  }

  ByteBuffer::~ByteBuffer() {
    delete this->m_buf;
  }

  ByteBuffer *ByteBuffer::Push(uint8_t value) {
    this->m_buf->push_back((char)value);
    return this;
  }

  ByteBuffer *ByteBuffer::Push(uint16_t value) {
    this->m_buf->push_back((char)(value >> 8));
    this->m_buf->push_back((char)value);
    return this;
  }

  ByteBuffer *ByteBuffer::Push(uint32_t value) {
    this->m_buf->push_back((char)(value >> 24));
    this->m_buf->push_back((char)(value >> 16));
    this->m_buf->push_back((char)(value >> 8));
    this->m_buf->push_back((char)value);
    return this;
  }



  uint8_t ByteBuffer::PopUInt8() {
    assert(this->m_buf->size() != 0);
    std::uint8_t value = (std::uint8_t)this->m_buf->back();
    this->m_buf->pop_back();
    return  value;
  }

  uint16_t ByteBuffer::PopUInt16() {
    std::uint8_t v2 = this->PopUInt8();
    std::uint8_t v1 = this->PopUInt8();
    std::uint16_t value = (v1 << 8) + v2;
    return value;
  }

  uint32_t ByteBuffer::PopUInt32() {
    std::uint8_t v4 = this->PopUInt8();
    std::uint8_t v3 = this->PopUInt8();
    std::uint8_t v2 = this->PopUInt8();
    std::uint8_t v1 = this->PopUInt8();
    std::uint32_t value = (v1 << 24) + (v2 << 16) + (v3 << 8) + v4;
    return value;
  }


  char *ByteBuffer::Data() {
    return this->m_buf->data();
  }

  std::size_t ByteBuffer::Size() {
    return (std::size_t)this->m_buf->size();
  }

  void ByteBuffer::Print() {
    std::cout << "[";
    auto len = (int)this->m_buf->size();
    for(int i=0;i<len;i++) {

    }
    std::cout << "]" << std::endl;
  }

}

