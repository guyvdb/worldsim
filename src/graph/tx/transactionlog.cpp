#include "transactionlog.h"
#include <filesystem>
#include <iostream>
#include <cerrno>
#include <ctime>

namespace graph {

  namespace tx {


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionLog::TransactionLog(const char *logdir) : m_logdir(logdir),
      m_file(0x0), m_isopen(false), m_lastError(ErrorNone) {
      std::filesystem::path fn(this->m_logdir);
      fn /= LOG_NAME;
      this->m_file = new ExtendedFile(fn);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionLog::~TransactionLog() {
      if(this->m_file->IsOpen()) {
        this->m_file->Flush();
        this->m_file->Close();
      }
      delete this->m_file;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionLog::Open() {
      // open the log in binary append mode. seek to the end ready for next write
      if(this->m_isopen) {
        this->m_lastError = ErrorFileAlreadyOpen;
        return false;
      }


      if(this->m_file->Open()) {
        type::txid txno;
        // get the next transaction number
        if(!this->LastTransactionNumber(&txno)) {
          this->m_file->Close();
          std::cout << "[TXLOG] Error - failed to look up last transaction number." << std::endl;
          return false;
        }
        this->m_counter = txno;


        // seek eof and ready for appends
        if(!this->m_file->SeekEOF()) {
          this->m_file->Close();
          std::cout << "[TXLOG] Error - failed to seek to eof." << std::endl;
          return false;
        }

        this->m_isopen = true;
        return true;
      }
      return false;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionLog::Close() {
      // Force the generation of a shutdown checkpoint

      if(this->m_isopen) {
        this->m_file->Close();
        this->m_isopen = false;
      }
      return true;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void TransactionLog::Lock(){
      this->m_mutex.lock();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void TransactionLog::Release(){
      this->m_mutex.unlock();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::txid TransactionLog::FrameStart(){
      this->m_framepointer = (std::uint64_t)this->m_file->Tell();

      //  | 16 bit  | 32 bit  | 64 bit    |  32 bit      |
      //  | magic   | txno    | timestamp | record count |
      //write the transaction frame header

      std::uint8_t magic[2];
      magic[0] = FRAME_HEADER_MAGIC0;
      magic[1] = FRAME_HEADER_MAGIC1;

      std::uint64_t timestamp = (std::uint64_t)std::time(0x0);

      if(!this->m_file->Write((char*)magic,2)) {
        std::cout << "[TXLOG] Error - failed to write frame header magic." << std::endl;
        return false;
      }

      this->m_counter++;
      if(!this->m_file->WriteInt((std::uint32_t)this->m_counter)){
        std::cout << "[TXLOG] Error - failed to write frame txno." << std::endl;
        return false;
      }

      if(!this->m_file->WriteInt(timestamp)) {
        std::cout << "[TXLOG] Error - failed to write frame timestamp." << std::endl;
        return false;
      }

      return this->m_counter;

      /*txid id = this->m_counter;
      this->m_counter++;
      return id;
      */
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionLog::FrameAppend(type::gid id, Storeable::Concept concept, TransactionOp op, ByteBuffer *buffer){
      this->m_transactionData.push_back(new FrameRecord(id,concept,op,buffer));
      return true;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionLog::FrameEnd(){
      // write the number of records into header
      std::uint32_t count = (std::uint32_t)this->m_transactionData.size();
      if(!this->m_file->WriteInt(count)) {
        std::cout << "[TXLOG] Error - failed to write frame record count." << std::endl;
        return false;
      }



      // Start records
      // Frame Record: | type   | opcode | record len | data...   | ... <next record>
      //               |  8 bit |  8 bit |  32 bit    | len bytes |

      // write out the records
      for (auto rec : this->m_transactionData) {
        std::uint8_t type = (std::uint8_t)rec->Type();
        std::uint8_t op = (std::uint8_t)rec->Op();
        std::uint32_t size = (std::uint32_t)rec->Buf()->Size();

        if(!this->m_file->WriteInt(type)) {
          std::cout << "[TXLOG] Error - failed to write record type." << std::endl;
          return false;
        }

        if(!this->m_file->WriteInt(op)) {
          std::cout << "[TXLOG] Error - failed to write record op." << std::endl;
          return false;
        }

        if(!this->m_file->WriteInt(size)) {
          std::cout << "[TXLOG] Error - failed to write record size." << std::endl;
          return false;
        }

        if(!this->m_file->Write(rec->Buf()->Data(),rec->Buf()->Size())) {
          std::cout << "[TXLOG] Error - failed to write record data." << std::endl;
          return false;
        }
      }

      // Write out the footer
      // Frame Footer: | start of frame pointer | checksum | magic
      //                        64 bit               32 bit   16 bit
      if(!this->m_file->WriteInt(this->m_framepointer)) {
        std::cout << "[TXLOG] Error - failed to frame pointer." << std::endl;
        return false;
      }

      std::uint32_t checksum = 0; // not implemented
      if(!this->m_file->WriteInt(checksum)) {
        std::cout << "[TXLOG] Error - failed to frame checksums." << std::endl;
        return false;
      }

      std::uint8_t magic[2];
      magic[0] = FRAME_FOOTER_MAGIC0;
      magic[1] = FRAME_FOOTER_MAGIC1;
      if(!this->m_file->Write((char*)magic, 2)) {
        std::cout << "[TXLOG] Error - failed to frame footer magic." << std::endl;
        return false;
      }

      // clean up
      this->m_framepointer = 0;
      for(auto rec : this->m_transactionData) {
        delete rec;
      }
      this->m_transactionData.clear();


      // done
      return this->m_file->Flush();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    //bool TransactionLog::TransactionEnd(TransactionStatus status){


    //}

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    //bool TransactionLog::TransactionRelease() {
    //  this->m_mutex.unlock();
    //  return true;
    //}

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
   // bool TransactionLog::TransactionAppend(Storeable::Type type, TransactionOp op, gid id, const std::uint8_t *data, std::size_t len) {
   //   this->m_transactionData.push_back(new FrameRecord(type,op,id,data,len));
   //   return true;
   // }

    /* ----------------------------------------------------------------------------------------
     * Find the last recorded transaction number in the log
     * --------------------------------------------------------------------------------------*/
    bool TransactionLog::LastTransactionNumber(type::txid *result) {
      if (this->m_file->Size() == 0) {
        *result = 0;
        return true;
      }

      // seek to end of file
      long pos = this->LastFrameStartAddress();

      if(!this->m_file->Seek(pos)) {
        std::cout << "[TXLOG] Error - falied to seek to last transaction" << std::endl;
        return false;
      }

      // the header is as follows:

      //  | 16 bit  | 32 bit  | 64 bit    |  32 bit      |
      //  | magic   | txno    | timestamp | record count |
      //write the transaction frame header
      std::uint8_t magic[2];
      if(!this->m_file->Read((char*)magic,2)){
        std::cout << "[TXLOG] Error - falied to read last frame magic." << std::endl;
        return false;
      }

      std::uint32_t txno;
      if(!this->m_file->ReadInt(&txno)) {
        std::cout << "[TXLOG] Error - falied to read last frame transaction number." << std::endl;
        return false;
      }

      *result = (type::txid)txno;
      return true;



      //       char Magic[2];
      //       txid TxNo;

  /*
  #define FRAME_START_1 0xCC
  #define FRAME_START_2 0xDD
  #define FRAME_END_1   0xAA
  #define FRAME_END_2   0xBB
      */
    }

    /* ----------------------------------------------------------------------------------------
     * Where in the log does the last frame start?
     * --------------------------------------------------------------------------------------*/
    long TransactionLog::LastFrameStartAddress() {

      long size = this->m_file->Size();
      long pos = size - FRAME_FOOTER_SIZE;
      if(!this->m_file->Seek(pos)) {
        std::cout << "[TXLOG] Error - failed to seek to last frame start of footer." << std::endl;
        return -1;
      }

      std::uint64_t address;
      std::uint32_t checksum;
      std::uint8_t magic[2];

      if(!this->m_file->ReadInt(&address)) {
        std::cout << "[TXLOG] Error - failed to read address of start of last frame." << std::endl;
        return -1;
      }

      if(!this->m_file->ReadInt(&checksum)) {
        std::cout << "[TXLOG] Error - failed to read checksum of last frame." << std::endl;
        return -1;
      }
      if(!this->m_file->Read((char*)magic,2)) {
        std::cout << "[TXLOG] Error - failed to read magic footer of last frame." << std::endl;
        return -1;
      }

      if(magic[0] != FRAME_FOOTER_MAGIC0 || magic[1] != FRAME_FOOTER_MAGIC1) {
        std::cout << "[TXLOG] Error - magic number of last frame footer mismatch." << std::endl;
        return -1;
      }

      // do crc check here
      return (long)address;

      //   // Frame Footer: | start of frame pointer | checksum | magic
           //                       64 bit                32 bit   16 bit
           //                       8 byte                4 byte   2 byte
    }


  }
}


