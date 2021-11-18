#pragma once
#include <string>
#include "fileHandler.hpp"

namespace cash_overflow::db
{
    class Db
    {
    private:
        cashoverflow::utils::FileHandler fileHandler_;
    public:
        Db(cashoverflow::utils::FileHandler fileHandler): fileHandler_(fileHandler) {}
        bool update() {

        }

        bool read() {

        }

        bool create(std::string userName, std::string passWord) {

        }

        bool delete_() {

        }
    };
} // namespace cash_overflow::db
