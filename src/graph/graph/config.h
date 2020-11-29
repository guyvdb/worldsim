#ifndef CONFIG_H
#define CONFIG_H


#include <cstdint>
#include <string>

namespace graph {


  class Config {
    public:
      Config(std::string datadir, std::string logdir) : m_datadir(datadir), m_logdir(logdir), m_pagesize(4096) {};
      std::string Path() { return m_datadir; }

      const char *DataDirectory() { return m_datadir.c_str(); }
      const char *LogDirectory() { return m_logdir.c_str(); }

      // const value_type*
      std::size_t PageSize() { return m_pagesize; }
      void SetPageSize(std::size_t size) { m_pagesize = size; }
    private:
      std::string m_datadir;
      std::string m_logdir;
      std::size_t m_pagesize;
  };

}




#endif // CONFIG_H
