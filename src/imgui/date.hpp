#ifndef CASH_OVERFLOW_DATE_HPP
#define CASH_OVERFLOW_DATE_HPP

#include <chrono>
#include <tl/expected.hpp>
#include <fmt/format.h>

#include "error.hpp"
#include "logger.hpp"

using LoggingLevel = cashoverflow::logging::LogLevel;

auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::ERR);

struct Day
{
  Day(int v) : value{ v } {}
  auto operator<=>(Day const &) const = default;
  int value{};
};

struct Year
{
  Year(int v) : value{ v } {}
  auto operator<=>(Year const &) const = default;
  bool isLeapYear()
  {
    return value % 4 == 0 && !(value % 100 == 0 && (value % 400 != 0));
  }
  int value{};
  Day getNumberOfDays(Year year)
  {
      return year.isLeapYear() ? 366 : 365;
  }

};



struct Month
{
  Month(int v) : value{ v } {}
  auto operator<=>(Month const &) const = default;
  int value{};
  Day getNumberOfDays(Year year)
  {
    switch (value) {
    case 11:
    case 4:
    case 6:
    case 9:
      return 30;
    case 12:
    case 10:
    case 8:
    case 7:
    case 5:
    case 3:
    case 1:
      return 31;
    case 2: {
      return year.isLeapYear() ? 29 : 28;
    }
    default:
      return 0;
    }
  }
};


class Date
{
public:
  using Error = cash_overflow::error::Error;
  static tl::expected<Date, Error> create(Year y, Month m, Day d)
  {
    if (y <= 1970) {
      return tl::make_unexpected("Year needs to be in the recent past (until 1970), if you want to go that way back get a time machine asshole.");
    }
    if (m < 1 || m > 12) {
      return tl::make_unexpected("Month must be between one and twelve");
    }

    if (d <= 0) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if ((m == 11 || m == 4 || m == 6 || m == 9) && d > 30) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if (d > 31) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if (m == 2) {
      Day lastDay = y.isLeapYear() ? 29 : 28;
      if (d > lastDay) {
        return tl::make_unexpected("Day is out of range for selected Month");
      }
    }
    return Date(y, m, d);
  }
  std::string toString()
  {
    return fmt::format("{}-{}-{}", year.value, month.value, day.value);
  }
  friend std::ostream &operator<<(std::ostream &os, Date date)
  {
    os << date.toString();
    return os;
  }
  auto operator<=>(Date const &) const = default;
  tl::expected<Date, Error> operator+(Year y)
  {
    return Date::create(year.value + y.value, month, day);
  }
  tl::expected<Date, Error> operator+(Month m)
  {
    if (month.value + m.value < 12) {
      return Date::create(year, month.value + m.value, day);
    }
    int yearsToAdd = m.value / 12;
    LOGGER.write(yearsToAdd, LoggingLevel::DBG);

    int remainingMonths = m.value % 12;
    LOGGER.write(remainingMonths, LoggingLevel::DBG);

    auto monthsToAdd = month.value + remainingMonths;
    LOGGER.write(monthsToAdd, LoggingLevel::DBG);

    if (monthsToAdd > 12) {
      return Date::create(year.value + yearsToAdd + 1, monthsToAdd - 12, day);
    } else {
      return Date::create(year.value + yearsToAdd, monthsToAdd, day);
    }
  }

  tl::expected<Date, Error> operator+(Day d)
  {
    auto m_ = month;
    auto y_ = year;
    auto d_ = day;
    while (d.value > m_.getNumberOfDays(y_)){
      d.value -= m_.getNumberOfDays(y_).value;
      if (m_.value == 12) {
        m_.value = 1;
        ++y_.value;
      } else {
        ++m_.value;
      }
    }
    d_.value += d.value;
    if (d_.value > m_.getNumberOfDays(y_)) {
      d_.value -= m_.getNumberOfDays(y_).value;
      m_.value++;
    }
    return Date::create(y_, m_, d_);
  }

private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d)
  {}
  Year year;
  Month month;
  Day day;
};

// Date::create()

#endif// CASH_OVERFLOW_DATE_HPP
