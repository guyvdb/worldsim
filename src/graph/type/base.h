#ifndef BASE_H
#define BASE_H

#include <cstdint>
#include <string>

namespace graph {
  namespace type {

    // Id Types
    typedef std::uint32_t gid;      // Graph Id
    typedef std::uint32_t txid;     // Transaction Id
    typedef std::uint32_t pid;      // Page Id
    typedef std::uint8_t  cid;      // Concept Id
    typedef std::uint8_t  stateid;  // Action Id
    typedef std::uint8_t  ptid;     // Property Type Id

    const gid NullGraphId = 0x0;


    typedef void (*myfunc)();

    enum DataType : ptid {
      Integer,
      IntegerArray,
      Float,
      FloatArray,
      Boolean,
      BooleanArray,
      ShortString,
      ShortStringArray,
      LongString,
      LongStringArray,
      DateTime,
      DataTimeArray,
      LatLon,         // this is a pair
      LatLonArray     // this is an array of pairs
    };

    class ByteBuffer;
    /*
     * |--------------|
     * | FixedString  |
     * |------|-------|
     * | 0    | 1..31 |
     * | len  | value |
     * |------|-------|
     */
    // A fixed string has a maximm size of 30 bytes. It is 31 bytes
    // long with the first byte representing the lenght of the string.
    // All strings are padded so the structure is alway 65 bytes long
    class FixedString {
      public:
        static const int MAX_FIXED_STRING_LEN = 30;
        FixedString(ByteBuffer *buffer, int offset);
        FixedString(std::string value);
        FixedString();
        ~FixedString();
        std::string StdString();
        void SetValue(std::string value);
        void WriteToBuffer(ByteBuffer *buffer, int offset);
        int Size();
      private:
        std::string m_value;
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
