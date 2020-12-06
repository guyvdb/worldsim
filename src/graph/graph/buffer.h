#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <vector>

namespace graph {
  class ByteBuffer {
    public:
      ByteBuffer();
      ByteBuffer(std::size_t len);
      ByteBuffer(ByteBuffer *buf);

      bool Equal(ByteBuffer *buf);

      void Append(std::uint8_t value);
      void Append(std::uint8_t *buffer, std::size_t len);

      void Set(int offset, std::uint8_t value);
      void Set(int offset, std::uint16_t value);
      void Set(int offset, std::uint32_t value);
      void Set(int offset, std::uint64_t value);


      uint8_t GetUint8(int offset);
      uint16_t GetUint16(int offset);
      uint32_t GetUint32(int offset);
      uint64_t GetUint64(int offset);

      void Reserve(std::size_t len);
      std::uint8_t At(int index) { return this->m_data.at(index); }
      std::uint8_t operator[](int index) { return this->At(index); }
      std::size_t Capacity() { return this->m_data.capacity(); }
      std::size_t Size() { return this->m_data.size(); }
      void *Data() { return (void*) this->m_data.data(); }
      //std::uint8_t *Data() { return this->m_data.data(); }
      //char *CharData() { return (char*)this->m_data.data(); }
      //void *VoidData() { return (void*)this->m_data.data(); }

       // return a slice of the buffer read only
       std::uint8_t* Slice(int offset);
    private:
      std::vector<std::uint8_t> m_data;
  };
}
#endif // BUFFER_H

/*
 *       void SetUInt8(std::uint8_t value, char *data);
      void SetUInt16(std::uint16_t value, char *data);
      void SetUInt32(std::uint32_t value, char *data);
      std::uint8_t GetUInt8(const char *data);
      std::uint16_t GetUInt16(const char *data);
      std::uint32_t GetUInt32(const char *data);
      */
