#include "base.h"

#include <iostream>
#include <type/buffer.h>

namespace graph {
  namespace type {

    FixedString::FixedString() : m_value("") {

    }

    FixedString::FixedString(std::string value) : m_value(value) {

    }

    FixedString::FixedString(ByteBuffer *buffer, int offset) : m_value("") {
      // first byte is len
      int len = (int)buffer->At(offset);

      for(int i=offset+1;i<=len+offset;i++) {
        std::uint8_t c = buffer->At(i);
        this->m_value.push_back((char)c);
      }
    }

    FixedString::~FixedString() {

    }

    std::string FixedString::StdString() {
      return this->m_value;
    }


    void FixedString::SetValue(std::string value) {
      this->m_value = value;
    }

    void FixedString::WriteToBuffer(ByteBuffer *buffer, int offset) {
      int len = this->m_value.size();
      if(len > MAX_FIXED_STRING_LEN) {
        len = MAX_FIXED_STRING_LEN;
      }

      buffer->Set(offset, (std::uint8_t)len);
      int j = 0;
      for(int i=offset+1;i<=this->Size()+offset;i++) {
        if(i > MAX_FIXED_STRING_LEN) {
          // string will be truncated
          break;
        }

        std::cout << m_value.at(j);

        buffer->Set(i, (std::uint8_t)this->m_value.at(j));
        j++;
      }
      std::cout << std::endl;
    }

    int FixedString::Size() {
      return this->m_value.size();
    }
  }
}


/*
        void SetValue(std::string value);
        void WriteValue(ByteBuffer *buffer, int offset);
        int Size();
      private:
        ByteBuffer *m_buffer;
    };
    */
