#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

namespace cash_overflow::exception {

class BadTable: public std::exception {
public:
   explicit BadTable(std::string msg): error_message(std::move(msg)) {}
   explicit BadTable(const char* msg): error_message(msg) {}

   const char* what() const noexcept {
      return error_message.c_str();
   }
private:
   std::string error_message{};
};

} // namespace cash_overflow::exception

#endif // CUSTOM_EXCEPTIONS_H
