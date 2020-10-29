#include "log.h"
#include <filesystem>
#include <iostream>

namespace graph {

  Log::Log(const char *logdir) : m_logdir(logdir),
    m_file(0x0), m_isopen(false), m_lastError(ErrorNone) {

  }

  bool Log::Open() {
    // open the log in binary append mode. seek to the end ready for next write
    if(this->m_isopen) {
      this->m_lastError = ErrorFileAlreadyOpen;
      return false;
    }

    std::filesystem::path filename(this->m_logdir);
    filename /= LOG_NAME;

    this->m_file = std::fopen(filename.c_str(),"wba");
    this->m_isopen = true;
    return true;
  }

  bool Log::Close() {
    // Force the generation of a shutdown checkpoint

    // Flush the log file
    std::fflush(this->m_file);

    // Close the log file
    std::fclose(this->m_file);
    this->m_file = 0x0;
    this->m_isopen = false;
    return true;
  }

}


