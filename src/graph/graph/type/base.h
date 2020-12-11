#ifndef BASE_H
#define BASE_H

#include <cstdint>
#include <string>

#include <buffer.h>
#include <types.h>

namespace graph {
  namespace type {

    enum DataType : dtid {
      ComplexType,
      IntegerType,
      FloatType,
      BooleanType,
      FixedStringType,
      DynamicStringType,
      IntegerArrayType,
      FloatArrayType,
      BooleanArrayType,
      DateTimeType
    };

    /*
     * |--------------|
     * | FixedString  |
     * |------|-------|
     * | 0    | 1..64 |
     * | len  | value |
     * |------|-------|
     */
    // A fixed string has a maximm size of 64 bytes. It is 65 bytes
    // long with the first byte representing the lenght of the string.
    // All strings are padded so the structure is alway 65 bytes long
    class FixedString {
      public:
        FixedString(std::string value);
        FixedString();
        ~FixedString();
        std::string GetValue();
        void SetValue(std::string value);
        int Size();
      private:
        ByteBuffer *m_buffer;
    };

    // A dynamic string is a variable size string. The string is written into property buckets.
    // New buckets are allocated as needed. The first 2 bytes of the string are its size.
    //
    class DynamicString {

    };

    // A DateTime is stored as an unsigned 64 bit number
    class DateTime {
    };

    template <class T>
    class NumberArray {
    };

  }
}

#endif // BASE_H
