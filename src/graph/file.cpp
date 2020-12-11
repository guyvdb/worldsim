#include "file.h"
#include <iostream>
#include <cassert>
#include <vector>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  File::File(std::filesystem::path filename) : m_size(0), m_fd(0x0), m_filename(filename), m_isopen(false) {
    std::cout << "[FILE] Create file object - filename=" << m_filename << std::endl;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  File::~File() {
    if(this->m_isopen) {
      this->Close();
    }
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Open() {
    std::cout << "[FILE] Open " << this->m_filename << std::endl;

    // Check if the file exists... if not touch it
    if(!this->Exists()) {
      std::cout << "[FILE] Touch file " << this->m_filename << std::endl;
      this->Touch();
    }

    // open the file
    this->m_fd = std::fopen(this->m_filename.c_str(), "r+ab");
    if(this->m_fd == 0x0){
      std::cout << "[FILE] Error - failed to open " << this->m_filename.native() << std::endl;
      return false;
    }

    std::cout << "[FILE] File " << this->m_filename.native() << " is open" << std::endl;

    this->m_size = this->FileSize();

    // set the flags
    this->m_isopen = true;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void File::Close() {
    // if the file is open flush it and close it
    if(this->m_isopen) {
      this->Flush();
      std::fclose(this->m_fd);
      this->m_fd = 0x0;
      this->m_isopen = false;
    }
  }

  /* ----------------------------------------------------------------------------------------
   * Write data size long to the pos in the file
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, void *data, std::size_t size){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(void *data, std::size_t size) {
    // write size bytes at the current position
    std::size_t written = std::fwrite(data,1,size,this->m_fd);
    long pos = this->Tell();
    if(this->m_size < pos) {
      this->m_size = pos;
    }
    return written == size;
  }

  bool File::Write(long pos, char *data, std::size_t size) {
    return this->Write(pos, (void*)data, size);
  }

  bool File::Write(char *data, std::size_t size) {
    return this->Write((void*)data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(long pos, void *data, std::size_t size) {
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data,size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(void *data, std::size_t size) {
    std::size_t read = std::fread(data,1,size,this->m_fd);
    return read == size;
  }

  bool File::Read(long pos, char *data, std::size_t size) {
    return this->Read(pos, (void*)data, size);
  }

  bool File::Read(char *data, std::size_t size) {
    return this->Read((void*)data, size);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Seek(long pos) {
    return std::fseek(this->m_fd,pos,SEEK_SET) == 0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::SeekEOF() {
    return std::fseek(this->m_fd,0,SEEK_END) == 0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Flush() {
    return std::fflush(this->m_fd) == 0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  long File::Tell() {
     return std::ftell(this->m_fd);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  long File::Size() {
    return m_size;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  long File::FileSize() {
    long pos = this->Tell();
    std::fseek(this->m_fd,0,SEEK_END);
    long size = this->Tell();
    this->Seek(pos);
    return size;
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Exists() {
    assert(!this->m_isopen);

    // open the file for read... if it fails the file does not exist
    FILE *fd = 0x0;
    std::fopen(this->m_filename.c_str(),"r");
    if(fd == 0x0) {
      return false;
    }
    std::fclose(fd);
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void File::Touch() {
    assert(!this->m_isopen);
    // make sure the file does not exist... open the file for write to create it
    FILE *fd = 0x0;
    std::fopen(this->m_filename.c_str(),"a+");
    if(fd != 0x0) {
      std::fclose(fd);
    }
  }


  // ============================= ExtendedFile =====================================


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
 /* bool ExtendedFile::Write(char* data, std::size_t size) {
    void *ptr = (void*)data;
    this->Write(ptr,size);
  }*/

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  /*bool ExtendedFile::Write(long pos, char* data, std::size_t size) {
    void *ptr = (void*)data;
    return this->Write(pos, ptr, size);
  }*/


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(long pos, std::uint8_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->WriteInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(long pos, std::uint16_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->WriteInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(long pos, std::uint32_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->WriteInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(long pos, std::uint64_t data) {
    if(!this->Seek(pos)) {
      return false;
    }
    return this->WriteInt(data);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(std::uint8_t data) {
    char buf[1];
    buf[0] = (char)data;
    return this->Write(buf,1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(std::uint16_t data) {
    char buf[2];
    buf[0] = (char)(data >> 8);
    buf[1] = (char)(data);
    return this->Write(buf,2);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(std::uint32_t data) {
    char buf[4];
    buf[0] = (char)(data >> 24);
    buf[1] = (char)(data >> 16);
    buf[2] = (char)(data >> 8);
    buf[3] = (char)(data);
    return this->Write(buf,4);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::WriteInt(std::uint64_t data) {
    char buf[8];
    buf[0] = (char)(data >> 56);
    buf[1] = (char)(data >> 48);
    buf[2] = (char)(data >> 40);
    buf[3] = (char)(data >> 32);
    buf[4] = (char)(data >> 24);
    buf[5] = (char)(data >> 16);
    buf[6] = (char)(data >> 8);
    buf[7] = (char)(data);
    return this->Write(buf,8);
  }



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(long pos, std::uint8_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->ReadInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(long pos, std::uint16_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->ReadInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(long pos, std::uint32_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->ReadInt(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(long pos, std::uint64_t *data) {
    if(!this->Seek(pos)) {
      return false;
    }
    return this->ReadInt(data);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(std::uint8_t *data) {
    return this->Read((char*)data, 1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(std::uint16_t *data) {
    std::uint8_t buf[2];
    if(!this->Read((char*)buf,2)) {
      return false;
    }
    *data = (buf[0] << 8) + (buf[1]);
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(std::uint32_t *data) {
    std::uint8_t buf[4];
    if(!this->Read((char*)buf,4)) {
      return false;
    }
    *data = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool ExtendedFile::ReadInt(std::uint64_t *data) {
    uint8_t buf[8];
    if(!this->Read((char*)buf,8)) {
      return false;
    }

    *data = ((std::uint64_t)buf[0] << 56) +
            ((std::uint64_t)buf[1] << 48) +
            ((std::uint64_t)buf[2] << 40) +
            ((std::uint64_t)buf[3] << 32) +
            ((std::uint64_t)buf[4] << 24) +
            ((std::uint64_t)buf[5] << 16) +
            ((std::uint64_t)buf[6] << 8) +
            ((std::uint64_t)buf[7]);

    return true;
  }


}







/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
/*bool File::Read(long pos, char *data, std::size_t size){
  if(!this->Seek(pos)) {
    return false;
  }
  return this->Read(data,size);
}*/


/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
/*bool File::Write(const char* data, std::size_t size){
  return this->Write((void*)data, size);
}*/



/* ----------------------------------------------------------------------------------------
 * Grow the file by appending size bytes to it. Set value of bytes to 0x0
 * --------------------------------------------------------------------------------------*/
/*bool File::Grow(long size) {
  std::vector<std::uint8_t> buf;
  buf.reserve(size);
  for(long i=0;i<size;i++){
    buf.push_back(0x0);
  }
  //std::fill(buf.begin(), buf.end(), 0x0);
  std::cout << "will grow - buf=" << buf.size() << std::endl;

  return this->Write(this->m_size,buf.data(), size);
}*/


/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
/* void File::CheckGrow(long pos, long size) {
  // pos to read/write from
  // size bytes to read/write
  if (pos + size > this->m_size) {
    long finalsize = (pos / m_pagesize) + (this->m_growPageCount * this->m_pagesize);
    long growth = finalsize - this->m_size;
    this->Grow(growth);
  }
}*/

