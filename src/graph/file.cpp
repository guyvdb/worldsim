#include "file.h"
#include <iostream>
#include <cassert>

namespace graph {


  File::File(std::filesystem::path filename) : m_fd(0x0), m_filename(filename), m_isopen(false) {

  }

  File::~File() {
    if(this->m_isopen) {
      this->Close();
    }
  }

  bool File::Open() {
    // Check if the file exists... if not touch it
    if(!this->Exists()) {
      this->Touch();
    }
    // Open the file
    // open the file
    this->m_fd = std::fopen(this->m_filename.c_str(), "r+ab");
    if(this->m_fd == 0x0){
      std::cout << "[FILE] Error - failed to open " << this->m_filename.native() << std::endl;
      return false;
    }

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
  bool File::Write(long pos, const char *data, std::size_t size){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, std::uint8_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, std::uint16_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, std::uint32_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(long pos, char *data, std::size_t size){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data,size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(long pos, std::uint8_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(long pos, std::uint16_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(long pos, std::uint32_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->Read(data);
  }



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(const char *data, std::size_t size) {
    // std::size_t fwrite( const void* buffer, std::size_t size, std::size_t count, std::FILE* stream );


    std::cout << "WRITE: start tell=" << this->Tell() << ", data=";

    const char *ptr = data;
    for(std::size_t i=0; i<size; i++) {
      std::uint8_t d = (std::uint8_t)*ptr;
      std::printf("0x%X ", d);
      ptr++;
    }


    // write size bytes at the current position
    std::size_t written = std::fwrite((void*)data,1,size,this->m_fd);

    std::cout << ", size=" << size << ", end tell=" << this->Tell() << std::endl;

    return written == size;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(std::uint8_t data) {
    char buf[1];
    buf[0] = (char)data;
    return this->Write(buf,1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(std::uint16_t data) {
    char buf[2];
    buf[0] = (char)(data >>8);
    buf[1] = (char)(data);
    return this->Write(buf,2);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(std::uint32_t data) {
    char buf[4];
    buf[0] = (char)(data >> 24);
    buf[1] = (char)(data >> 16);
    buf[2] = (char)(data >> 8);
    buf[3] = (char)(data);
    return this->Write(buf,4);
  }

  /* ----------------------------------------------------------------------------------------
   * data needs to be at least size bytes long
   * --------------------------------------------------------------------------------------*/
  bool File::Read(char *data, std::size_t size) {
    std::cout << "READ: start tell=" << this->Tell() << ", data=";

    std::size_t read = std::fread((void*)data,1,size,this->m_fd);


    const char *ptr = data;
    for(std::size_t i=0; i<size; i++) {
      std::uint8_t d = (std::uint8_t)*ptr;
      std::printf("0x%X ", d);
      ptr++;
    }

      std::cout << ", size=" << size << ", end tell=" << this->Tell() << std::endl;

    return read == size;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(std::uint8_t *data) {
    return this->Read((char*)data, 1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(std::uint16_t *data) {
    char buf[2];
    if(!this->Read(buf,2)) {
      return false;
    }

    *data = (buf[0] <<8) + buf[1];
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Read(std::uint32_t *data) {
    char buf[4];
    if(!this->Read(buf,4)) {
      return false;
    }
    *data = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return true;
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
  bool File::Exists() {
    assert(!this->m_isopen);

    // open the file for read... if it fails the file does not exist
    FILE *fd;
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
    FILE *fd;
    std::fopen(this->m_filename.c_str(),"c");
    std::fclose(fd);
  }


}
