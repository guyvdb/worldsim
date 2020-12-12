#ifndef FILE_H
#define FILE_H

#include <filesystem>
#include <cstdio>
#include <cstdint>

namespace graph {


  // TODO need to create a readonly file and a read write file

  class File {
    public:
      File(std::filesystem::path filename);
      ~File();
      bool Open();
      void Close();
      bool Exists();
      bool Seek(long pos);
      bool SeekEOF();
      bool Flush();
      long Tell();


      bool IsOpen() { return this->m_isopen; }
      bool Write(void *data, std::size_t size);
      bool Write(long pos, void *data, std::size_t size);
      bool Write(char* data, std::size_t size);
      bool Write(long pos, char* data, std::size_t size);


      bool Read(void *data, std::size_t size);
      bool Read(long pos, void *data, std::size_t size);
      bool Read(char *data, std::size_t size);
      bool Read(long pos, char *data, std::size_t size);


      long Size();
   private:

      void Touch();
      long FileSize();
      //bool Grow(long size);
      //void CheckGrow(long pos, long size);
      //bool Grow(std::size_t size);

      long m_size;
      //std::size_t m_pagesize;
      //int m_growPageCount;
      std::FILE *m_fd;
      std::filesystem::path m_filename;
      bool m_isopen;
  };


  class ExtendedFile : public File {
    public:
      ExtendedFile(std::filesystem::path filename) : File(filename) {}



      bool WriteInt(std::uint8_t data);
      bool WriteInt(std::uint16_t data);
      bool WriteInt(std::uint32_t data);
      bool WriteInt(std::uint64_t data);
      bool WriteInt(long pos, std::uint8_t data);
      bool WriteInt(long pos, std::uint16_t data);
      bool WriteInt(long pos, std::uint32_t data);
      bool WriteInt(long pos, std::uint64_t data);



      bool ReadInt(std::uint8_t *data);
      bool ReadInt(std::uint16_t *data);
      bool ReadInt(std::uint32_t *data);
      bool ReadInt(std::uint64_t *data);
      bool ReadInt(long pos, std::uint8_t *data);
      bool ReadInt(long pos, std::uint16_t *data);
      bool ReadInt(long pos, std::uint32_t *data);
      bool ReadInt(long pos, std::uint64_t *data);

  };

}
#endif // FILE_H
