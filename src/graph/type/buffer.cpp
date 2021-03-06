#include "buffer.h"
#include <cassert>
#include <iostream>'
#include <type/base.h>

namespace graph {

  namespace type {


    ByteBuffer::ByteBuffer() {

    }

    ByteBuffer::ByteBuffer(std::size_t len) {
      this->m_data = std::vector<std::uint8_t>(len,0x0);
    }


    ByteBuffer::ByteBuffer(ByteBuffer *buf) {
      this->Reserve(buf->Size());
      std::uint8_t *ptr = (std::uint8_t*)buf->Data();
      for(std::size_t i =0; i<buf->Size();i++) {
        this->m_data.push_back(ptr[i]);
      }
    }

    bool ByteBuffer::Equal(ByteBuffer *buf) {
      if(this->Size() != buf->Size()) {
        return false;
      }

      for(std::size_t i =0; i< this->Size();i++) {
        if(this->At(i) != buf->At(i)) {
          return false;
        }
      }
      return true;
    }

    std::uint8_t* ByteBuffer::Slice(int offset) {
      std::uint8_t *ptr = this->m_data.data();
      ptr += offset;
      return ptr;
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

    void ByteBuffer::Set(int offset, type::FixedString value) {
      value.WriteToBuffer(this, offset);
    }
    void ByteBuffer::Set(int offset, bool value) {
      if(value) {
        this->m_data[offset] = 0x1;
      } else {
        this->m_data[offset] = 0x0;
      }
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

    type::FixedString ByteBuffer::GetFixedString(int offset) {
      return type::FixedString(this,offset);
    }

    bool ByteBuffer::GetBool(int offset) {
      if(this->m_data[offset] == 0x1){
        return true;
      }
      return false;
    }

  }
}
