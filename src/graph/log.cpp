#include "log.h"
#include <filesystem>
#include <iostream>
#include <cerrno>

namespace graph {

  Log::Log(const char *logdir) : m_logdir(logdir),
    m_file(0x0), m_isopen(false), m_lastError(ErrorNone) {
    std::filesystem::path fn(this->m_logdir);
    fn /= LOG_NAME;
    this->m_file = new File(fn);
  }

  Log::~Log() {
    delete this->m_file;
  }

  bool Log::Open() {
    // open the log in binary append mode. seek to the end ready for next write
    if(this->m_isopen) {
      this->m_lastError = ErrorFileAlreadyOpen;
      return false;
    }


    if(this->m_file->Open()) {
      this->m_isopen = true;
      return true;
    }
    return false;
  }

  bool Log::Close() {
    // Force the generation of a shutdown checkpoint

    if(this->m_isopen) {
      this->m_file->Close();
      this->m_isopen = false;
    }
    return true;
  }

}


