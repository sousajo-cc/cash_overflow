#ifndef CASH_OVERFLOW_FILEHANDLER_H
#define CASH_OVERFLOW_FILEHANDLER_H

#include <fstream>
#include <sstream>
#include <string>

namespace cashoverflow::utils {
struct FileHandler
{
  explicit FileHandler(std::string fileName_) : fileName(std::move(fileName_))
  {
    
  };
  FileHandler(FileHandler const &) = default;
  FileHandler &operator=(FileHandler const &) = default;
  FileHandler(FileHandler &&) = default;
  FileHandler &operator=(FileHandler &&) = default;
  ~FileHandler() = default;
  // {
  //   if (fileStream.is_open()) {
  //     fileStream.close();
  //   }
  // }
  void open() {
    fileStream.open(fileName.c_str(), std::ios_base::in);
      if (!fileStream.is_open()) {
        throw std::runtime_error("could not open the file.");
      }
  }
  std::string read() const
  {
    std::ostringstream os;
    os << fileStream.rdbuf();
    return os.str();
  };

  std::string fileName;
  std::fstream fileStream;
};
}// namespace cashoverflow::utils

#endif
