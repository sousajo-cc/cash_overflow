#ifndef CASH_OVERFLOW_FILEHANDLER_H
#define CASH_OVERFLOW_FILEHANDLER_H

#include <fstream>
#include <sstream>
#include <string>

namespace cashoverflow::utils {

class IFileHandler {
  public:
    virtual std::string read() const = 0;
    virtual unsigned int read(char *buffer, int size) = 0;
    virtual std::string getFileName() const = 0;
    virtual ~IFileHandler() = default;
};
class FileHandler: public IFileHandler
{
  public:
    explicit FileHandler(std::string fileName_) : fileName(std::move(fileName_))
    {
      fileStream.open(fileName.c_str(), std::ios_base::in);
      if (!fileStream.is_open()) {
        throw std::runtime_error("could not open the file.");
      }
    };
    FileHandler(FileHandler const &) = delete;
    FileHandler &operator=(FileHandler const &) = delete;
    FileHandler(FileHandler &&) = delete;
    FileHandler &operator=(FileHandler &&) = delete;
    ~FileHandler()
    {
      if (fileStream.is_open()) {
        fileStream.close();
      }
    }
    
    std::string read() const override
    {
      std::ostringstream os;
      os << fileStream.rdbuf();
      std::cout << os.str() << std::endl;
      return os.str();
    }

    unsigned int read(char *buffer, int size) override {
      fileStream.read(buffer, size);
      return static_cast<unsigned int>(fileStream.gcount()); 
    }

    std::string getFileName() const override {
      return fileName;
    }

  private:  
    std::string fileName;
    std::fstream fileStream;
};
}// namespace cashoverflow::utils

#endif
