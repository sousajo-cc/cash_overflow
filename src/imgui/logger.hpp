#ifndef CASH_OVERFLOW_LOGGER_HPP
#define CASH_OVERFLOW_LOGGER_HPP

#include <iostream>
#include <fmt/color.h>

namespace cashoverflow::logging {

enum struct LogLevel {
  DBG,
  INF,
  WARN,
  ERR,
};

std::string toString(LogLevel lvl)
{
  switch (lvl) {
  case LogLevel::DBG:
    return "DBG";
  case LogLevel::INF:
    return "INF";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::ERR:
    return "ERR";
  default:
    return "DBG";
  }
}

std::ostream &operator<<(std::ostream &os, LogLevel &lvl)
{
  switch (lvl) {
  case LogLevel::DBG:
    os << "DBG";
    break;
  case LogLevel::INF:
    os << "INF";
    break;
  case LogLevel::WARN:
    os << "WARN";
    break;
  case LogLevel::ERR:
    os << "ERR";
    break;
  }
  return os;
}

class Logger
{
public:
  static Logger &log(LogLevel lvl)
  {
    switch (lvl) {
    case LogLevel::DBG: {
      static Logger instance(lvl);
      return instance;
    }
    case LogLevel::INF: {
      static Logger instance(lvl);
      return instance;
    }
    case LogLevel::WARN: {
      static Logger instance(lvl);
      return instance;
    }
    case LogLevel::ERR: {
      static Logger instance(lvl);
      return instance;
    }
    default: {
      static Logger instance(LogLevel::WARN);
      return instance;
    }
    }
  }

  fmt::color getColor(LogLevel lvl)
  {
    switch (lvl) {
    case LogLevel::DBG:
      return fmt::color::white_smoke;
    case LogLevel::INF:
      return fmt::color::steel_blue;
    case LogLevel::WARN:
      return fmt::color::yellow;
    case LogLevel::ERR:
      return fmt::color::crimson;
    default:
      return fmt::color::white_smoke;
    }
  }

  // fixme: make this
  // auto write(LogLevel lvl, T const &...msg)
  template<typename T>
  auto write(T const &msg, LogLevel lvl)
  {
    fmt::color color = getColor(lvl);
    if (lvl >= logLevel)
      fmt::print(fg(color) | fmt::emphasis::bold,
        "[{}] {}\n",
        toString(lvl),
        msg);
  }

private:
  Logger(LogLevel lvl) : logLevel(lvl) {}
  Logger() = default;
  ~Logger() = default;
  Logger(Logger const &) = delete;
  Logger &operator=(Logger const &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

  LogLevel logLevel;
};
}// namespace cashoverflow::logging

#endif
