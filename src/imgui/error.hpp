#ifndef CASH_OVERFLOW_ERROR_HPP
#define CASH_OVERFLOW_ERROR_HPP

#include <iostream>
#include <source_location>

namespace cash_overflow::error {

enum class ErrorType {
  TableError,
  DateError,
};

inline std::string toString(ErrorType t)
{
  switch (t) {
  case ErrorType::TableError:
    return "Table Error";
  case ErrorType::DateError:
    return "Date Error";
  default:
    return "";
  }
}

template<ErrorType t>
struct Error
{
  Error(std::string m, const std::source_location location = std::source_location::current()) : message{ m } {}
  Error(const char *m, const std::source_location location = std::source_location::current()) : message{ m } {}
  std::string message;
  void log(const std::source_location location =
           std::source_location::current())
  {
    std::cout << "file: "
              << location.file_name() << "("
              << location.line() << ":"
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
  }
};
/*
 *
 * #include <iostream>
#include <string_view>
#include <source_location>

void log(const std::string_view message,
         const std::source_location location =
               std::source_location::current())
{
    std::cout << "file: "
              << location.file_name() << "("
              << location.line() << ":"
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}

template <typename T> void fun(T x)
{
    log(x);
}

int main(int, char*[])
{
    log("Hello world!");
    fun("Hello C++20!");
}
 */

}// namespace cash_overflow::error

#endif
