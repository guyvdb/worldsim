#include <utils.h>
#include <chrono>
#include <types.h>
#include <QDir>
#include <QDebug>
#define TEST_ROOT "data"







void RemoveTestDirectory() {
  QDir dir(TEST_ROOT);
  dir.removeRecursively();
}


const char *CreateTestDirectory() {
  QDir dir(".");
  dir.makeAbsolute();
  dir.mkdir(TEST_ROOT);

  QDir child(dir.path() + dir.separator() + QString(TEST_ROOT));
  return  child.path().toUtf8().constData();
}

std::filesystem::path CreateFilePath(std::string filename) {
  // the path is going to be <test-directory>/filename
  std::filesystem::path p(CreateTestDirectory());
  p /= filename;
  return p;
}

std::string CreateFilePathString(std::string filename) {
  return CreateFilePath(filename).native();
}

graph::gid RandomGraphId() {
  // get wall clock time
  std::chrono::time_point time = std::chrono::system_clock::now();
  unsigned int ticks = (unsigned int)time.time_since_epoch().count();

  // seed RNG
  std::srand(ticks);

  graph::gid result = (graph::gid)std::rand();

  return result;

}
