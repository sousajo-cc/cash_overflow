#ifndef CASH_OVERFLOW_DATE_HPP
#define CASH_OVERFLOW_DATE_HPP

#include <chrono>
#include <tl/expected.hpp>
#include <fmt/format.h>

#include "error.hpp"

struct Year {
  Year(int v) : value{v} {}
  auto operator<=>(Year const&) const = default;
  bool isLeapYear()
  {
    return value % 4 == 0 && !(value % 100 == 0 && (value % 400 != 0));
  }
  int value{};
};

struct Month {
  Month(int v) : value{v} {}
  auto operator<=>(Month const&) const = default;
  int value{};
};

struct Day {
  Day(int v) : value{v} {}
  auto operator<=>(Day const&) const = default;
  int value{};
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
  std::string toString() {
    return fmt::format("{}-{}-{}", year.value, month.value, day.value);
  }
  friend std::ostream& operator<<(std::ostream& os, Date date) {
    os << date.toString();
    return os;
  }
  auto operator<=>(Date const&) const = default;
  tl::expected<Date, Error> operator+(Year y) {
    return Date::create(year.value + y.value, month, day);
  }
private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d)
  {
    // we have to check this here for now but then each class should check this
  }
  Year year;
  Month month;
  Day day;
};

// Date::create()

#endif// CASH_OVERFLOW_DATE_HPP
