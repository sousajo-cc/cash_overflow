#ifndef CASH_OVERFLOW_DATE_HPP
#define CASH_OVERFLOW_DATE_HPP

#include <chrono>
#include <tl/expected.hpp>

#include "error.hpp"

using Day = int;
using Month = int;
using Year = int;

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
      Day lastDay = isLeapYear(y) ? 29 : 28;
      if (d > lastDay) {
        return tl::make_unexpected("Day is out of range for selected Month");
      }
    }
    return Date(y, m, d);
  }

private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d)
  {
    // we have to check this here for now but then each class should check this
  }
  Year year;
  Month month;
  Day day;
  static bool isLeapYear(Year y)
  {
    return y % 4 == 0 && !(y % 100 == 0 && (y % 400 != 0));
  }
};

// Date::create()

#endif// CASH_OVERFLOW_DATE_HPP
