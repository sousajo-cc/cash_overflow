#ifndef CASH_OVERFLOW_FILEHANDLER_H
#define CASH_OVERFLOW_FILEHANDLER_H

#include <fstream>
#include <sstream>
#include <string>

namespace cashoverflow::utils
{
  struct FileHandler
  {
    explicit FileHandler(std::string fileName_) : fileName(std::move(fileName_)) {
      fileStream.open(fileName.c_str(), std::ios_base::in);
      if(!fileStream.is_open()){
        throw std::runtime_error("could not open the file.");
      }
    };
    FileHandler(FileHandler const&) = delete;
    FileHandler& operator=(FileHandler const&) = delete;
    FileHandler(FileHandler&&) = delete;
    FileHandler& operator=(FileHandler&&) = delete;
    ~FileHandler(){
      if (fileStream.is_open()) {
        fileStream.close();
      }
    }

    std::string read() const {
      std::ostringstream os;
      os << fileStream.rdbuf();
      return os.str();
    };

    std::string fileName;
    std::fstream fileStream;
  };
}

#endif//CASH_OVERFLOW_FILEHANDLER_H