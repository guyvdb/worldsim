#ifndef UTILS_H
#define UTILS_H

#include <filesystem>
#include <graph/type/base.h>
// some useful utility functions around the file system

void RemoveTestDirectory();
const char *CreateTestDirectory();
std::filesystem::path CreateFilePath(std::string filename);
std::string CreateFilePathString(std::string filename);
graph::type::gid RandomGraphId();

#endif // UTILS_H
