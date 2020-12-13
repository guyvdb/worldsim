#ifndef IDSCANNER_H
#define IDSCANNER_H

#include <store/scanner.h>

namespace graph {
  namespace id {

/*
    class IdScanner : public store::Scanner{
      public:
        IdScanner() : m_lastId(type::NullGraphId) { }

      private:
        void Reclaim(type::gid id);
        type::gid m_lastId;
    };

    */
  }
}

/*


    class IdScanner : public IdAccumulator{
      public:
        IdScanner(store::Store *store);
        type::gid NextId();
        virtual void Reclaim(type::gid id);
        void SetActive(bool value) { this->m_active = value; }
        store::Store *GetStore() { return m_store; }
        int ReclaimedIdCount() { return this->m_data.size(); }
        long FileOffset() { return this->m_fileoffset; }
        void SetFileOffset(long offset) { this->m_fileoffset = offset; }
        std::uint16_t IdLoadCount() { return this->m_idloadcount; }
        void SetIdLoadCount(std::uint16_t count) { this->m_idloadcount = count; }
        type::gid Counter() { return this->m_counter; }
        virtual void SetCounter(type::gid count) { this->m_counter = count; }
        std::vector<type::gid> &Data() {return this->m_data;}
      private:
        type::gid m_counter;
        std::mutex m_mutex;
        std::vector<type::gid> m_data;
        store::Store *m_store;
        bool m_active;
        long m_fileoffset; // used in storing this is the offset in the file
                           // where the data offset is written
                           //
                           // used in loading this is the actual data offset
        std::uint16_t m_idloadcount;
        type::gid m_lastId;
    };



*/

#endif // IDSCANNER_H
