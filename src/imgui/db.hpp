#pragma once
#include <string>
#include "fileHandler.hpp"

namespace cash_overflow::db {
using FileHandlerPtr = std::unique_ptr<cashoverflow::utils::IFileHandler>;
class Db
{
private:
  FileHandlerPtr fileHandler;

public:
  Db(FileHandlerPtr fileHandlerArg) : fileHandler(std::move(fileHandlerArg)) {}
  bool update()
  {
    return true;
  }

  bool read(const std::string &user)
  {
    std::string content = fileHandler->read();
    std::size_t found = content.find(user);
    return found != std::string::npos;
  }

  // create needs to write a line to db
  // creating a user can be: user:password
  // another entity can be: ola:eu:estou:aqui
  // lets discuss after
  bool create(std::string const &username, std::string const &password)
  {
    if (!read(username)) {
      auto entry = username + ":" + password;
      fileHandler->write(entry);
    }
    return true;
  }

  bool delete_()
  {
    return true;
  }
};
}// namespace cash_overflow::db
