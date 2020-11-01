#ifndef FILE_H
#define FILE_H

#include <filesystem>
#include <cstdio>
#include <cstdint>

namespace graph {



  class File {
    public:
      File(std::filesystem::path filename);
      ~File();
      bool Open();
      void Close();

      bool Seek(long pos);
      bool Flush();
      long Tell();

      // Read/Write from current position in file
      bool Write(const char *data, std::size_t size);
      bool Write(std::uint8_t data);
      bool Write(std::uint16_t data);
      bool Write(std::uint32_t data);
      bool Read(char *data, std::size_t size);
      bool Read(std::uint8_t *data);
      bool Read(std::uint16_t *data);
      bool Read(std::uint32_t *data);

      // Read/Write from specific position in file
      bool Write(long pos, const char *data, std::size_t size);
      bool Write(long pos, std::uint8_t data);
      bool Write(long pos, std::uint16_t data);
      bool Write(long pos, std::uint32_t data);
      bool Read(long pos, char *data, std::size_t size);
      bool Read(long pos, std::uint8_t *data);
      bool Read(long pos, std::uint16_t *data);
      bool Read(long pos, std::uint32_t *data);

      long Size();
   private:
      bool Exists();
      void Touch();

      std::FILE *m_fd;
      std::filesystem::path m_filename;
      bool m_isopen;


  };

}
#endif // FILE_H
