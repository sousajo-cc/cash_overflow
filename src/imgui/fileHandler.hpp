#ifndef CASH_OVERFLOW_FILEHANDLER_H
#define CASH_OVERFLOW_FILEHANDLER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace cashoverflow::utils {

/**
 * TODO: FileHandle should not be defined as text file handler,
 * Should be implemented a class derived from FileHandle to
 * deal with file text
 */
class IFileHandler
{
public:
  virtual std::string read() const = 0;
  virtual unsigned int read(char *buffer, int size) = 0;
  virtual std::string readLine() = 0;
  virtual void write(std::string const &entry) = 0;
  virtual std::string getFileName() const = 0;
  virtual ~IFileHandler() = default;
};

class FileHandler : public IFileHandler
{
public:
  explicit FileHandler(std::string fileName_) : fileName(std::move(fileName_))
  {
    std::cout << fileName_ << '\n';
    fileStream.open(fileName.c_str(), std::ios_base::in | std::ios_base::app);
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
    return os.str();
  }

  unsigned int read(char *buffer, int size) override
  {
    fileStream.read(buffer, size);
    return static_cast<unsigned int>(fileStream.gcount());
  }

  std::string readLine() override
  {
    std::string lineBuffer{};
    std::getline(fileStream, lineBuffer);
    return lineBuffer;
  }

  std::string getFileName() const override
  {
    return fileName;
  }

  void write(std::string const &entry) override
  {
    fileStream << entry;
    fileStream << '\n';
  }

private:
  std::string fileName;
  std::fstream fileStream;
};
}// namespace cashoverflow::utils

#endif
