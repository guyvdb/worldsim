#ifndef LOG_H
#define LOG_H


namespace graph {


  class Logger;



  class Logger {
    public:
      static Logger* Current();
    private:
      Logger();

      static void *current;
  };



  static Logger* Log() {
    return Logger::Current();
  }

}
#endif // LOG_H
