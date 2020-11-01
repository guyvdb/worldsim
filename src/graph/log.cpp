#include "log.h"
#include <filesystem>
#include <iostream>
#include <cerrno>

namespace graph {

  Log::Log(const char *logdir) : m_logdir(logdir),
    m_fd(0x0), m_isopen(false), m_lastError(ErrorNone) {

  }

  bool Log::Open() {
    // open the log in binary append mode. seek to the end ready for next write
    if(this->m_isopen) {
      this->m_lastError = ErrorFileAlreadyOpen;
      return false;
    }

    std::filesystem::path filename(this->m_logdir);
    filename /= LOG_NAME;

    std::cout << "[LOG] Open log file: " << filename.c_str() << std::endl;

    this->m_fd = std::fopen(filename.c_str(),"wba");

    std::cout << "[LOG] fd=" << this->m_fd << ", errno=" << errno << std::endl;

    this->m_isopen = true;
    return true;
  }

  bool Log::Close() {
    // Force the generation of a shutdown checkpoint

    // Flush the log file
    std::fflush(this->m_fd);

    // Close the log file
    std::fclose(this->m_fd);
    this->m_fd = 0x0;
    this->m_isopen = false;
    return true;
  }

}


