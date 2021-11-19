#pragma once
#include <string>
#include "fileHandler.hpp"

namespace cash_overflow::db
{
    using FileHandlerPtr = std::unique_ptr<cashoverflow::utils::IFileHandler>;
    class Db
    {
    private:
        FileHandlerPtr fileHandler;
    public:
        Db(FileHandlerPtr fileHandlerArg): fileHandler(std::move(fileHandlerArg)) {}
        bool update() {
            return true;
        }

        bool read(const std::string &user) {
            std::string content = fileHandler->read();
            std::size_t found = content.find(user);
            return found != std::string::npos;
        }

        // bool create(std::string userName, std::string passWord) {
        //     std::string content = fileHandler_.read();
        //     std::cout << content << std::endl;
        //     return true;
        // }

        bool delete_() {
            return true;
        }
    };
} // namespace cash_overflow::db
