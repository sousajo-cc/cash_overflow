#ifndef CASH_OVERFLOW_ERROR_HPP
#define CASH_OVERFLOW_ERROR_HPP

#include <iostream>

namespace cash_overflow::error {

struct Error
{
  Error(std::string m) : message{ m } {}
  Error(const char *m) : message{ m } {}
  std::string message;
  friend std::ostream &operator<<(std::ostream &os, Error const &e)
  {
    os << e.message;
    return os;
  }
};

}// namespace cash_overflow::error

#endif
