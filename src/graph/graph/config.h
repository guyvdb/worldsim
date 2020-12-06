#ifndef CONFIG_H
#define CONFIG_H


#include <cstdint>
#include <string>
#include <storeable.h>

namespace graph {


  class Config {
    public:
      static const std::size_t DefaultMaxCachePages = 256;
      Config(std::string datadir, std::string logdir) : m_datadir(datadir), m_logdir(logdir), m_pagesize(4096) {};
      std::string Path() { return m_datadir; }
      const char *DataDirectory() { return m_datadir.c_str(); }
      const char *LogDirectory() { return m_logdir.c_str(); }

      // const value_type*
      std::size_t PageSize() { return m_pagesize; }
      void SetPageSize(std::size_t size) { m_pagesize = size; }
      std::size_t GetCacheMaxPages(Storeable::Concept concept);
      void SetCacheMaxPages(Storeable::Concept concept, std::size_t max);
    private:
      std::string m_datadir;
      std::string m_logdir;
      std::size_t m_pagesize;

      std::map<Storeable::Concept, std::size_t> m_CacheMaxPages;
  };

}




#endif // CONFIG_H
