#include "file.h"
#include <iostream>
#include <cassert>

namespace graph {


  File::File(std::filesystem::path filename) : m_fd(0x0), m_filename(filename), m_isopen(false) {
    std::cout << "[FILE] Create file object - filename=" << m_filename << std::endl;
  }

  File::~File() {
    if(this->m_isopen) {
      this->Close();
    }
  }

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
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, const char* data, std::size_t size) {
    return this->Write(pos, (void*)data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(long pos, std::uint8_t *data, std::size_t size) {
    return this->Write(pos, (void*)data, size);
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
  bool File::Write(long pos, std::uint64_t data) {
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data);
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
  bool File::Read(long pos, std::uint64_t *data) {
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data);
  }

  bool File::Write(const char* data, std::size_t size){
    return this->Write((void*)data, size);
  }

  bool File::Write(std::uint8_t *data, std::size_t size) {
    return this->Write((void*)data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(void *data, std::size_t size) {
    // write size bytes at the current position
    std::size_t written = std::fwrite(data,1,size,this->m_fd);
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
    buf[0] = (char)(data >> 8);
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
   *
   * --------------------------------------------------------------------------------------*/
  bool File::Write(std::uint64_t data) {
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
   * data needs to be at least size bytes long
   * --------------------------------------------------------------------------------------*/
  bool File::Read(char *data, std::size_t size) {    
    std::size_t read = std::fread((void*)data,1,size,this->m_fd);
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
  bool File::Read(std::uint32_t *data) {
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
  bool File::Read(std::uint64_t *data) {
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


}
