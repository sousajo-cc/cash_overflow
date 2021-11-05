#ifndef CASH_OVERFLOW_ERROR_HPP
#define CASH_OVERFLOW_ERROR_HPP

namespace cash_overflow::error {

struct Error {
  Error(std::string m) : message{m} {}
  Error(const char* m) : message{m} {}
  std::string message;
};

}

#endif//CASH_OVERFLOW_ERROR_HPP
