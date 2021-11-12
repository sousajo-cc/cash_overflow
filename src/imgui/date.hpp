#ifndef CASH_OVERFLOW_DATE_HPP
#define CASH_OVERFLOW_DATE_HPP

#include <chrono>
#include <tl/expected.hpp>
#include <fmt/format.h>

#include "error.hpp"
#include "logger.hpp"

class Day
{
public:
  [[nodiscard]] constexpr explicit Day(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Day const &) const = default;
  [[nodiscard]] constexpr int getValue() const {
    return value;
  }
private:
  int value{};
};

class Year
{
public:
  [[nodiscard]] constexpr explicit Year(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Year const &) const = default;
  [[nodiscard]] constexpr int getValue() const {
    return value;
  }
  [[nodiscard]] constexpr bool isLeapYear() const
  {
    return value % 4 == 0 && !(value % 100 == 0 && (value % 400 != 0));
  }
  [[nodiscard]] constexpr Day getNumberOfDays(Year const& year) const
  {
    return Day{ year.isLeapYear() ? 366 : 365 };
  }
private:
  int value{};
};

class Month
{
public:
  [[nodiscard]] constexpr explicit Month(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Month const&) const = default;
  [[nodiscard]] constexpr int getValue() const {
    return value;
  }
  [[nodiscard]] constexpr Day getNumberOfDays(Year const& year)
  {
    switch (value) {
    case 11:
    case 4:
    case 6:
    case 9:
      return Day{ 30 };
    case 12:
    case 10:
    case 8:
    case 7:
    case 5:
    case 3:
    case 1:
      return Day{ 31 };
    case 2: {
      return Day{ year.isLeapYear() ? 29 : 28 };
    }
    default:
      return Day{ 0 };
    }
  }
private:
  int value{};
};


class Date
{
public:
  using Error = cash_overflow::error::Error;
  static tl::expected<Date, Error> create(int y, int m, int d) {
    return create(Year{y}, Month{m}, Day{d}); //TODO: remove
  }
  static tl::expected<Date, Error> create(Year y, Month m, Day d)
  {
    if (y < Year{ 1970 }) {
      return tl::make_unexpected("Year needs to be in the recent past (until 1970), if you want to go that way back get a time machine asshole.");
    }
    if (m < Month{ 1 } || m > Month{ 12 }) {
      return tl::make_unexpected("Month must be between one and twelve");
    }

    if (d <= Day{ 0 }) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if ((m == Month{ 11 } || m == Month{ 4 } || m == Month{ 6 } || m == Month{ 9 }) && d > Day{ 30 }) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if (d > Day{ 31 }) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    if (m == Month{ 2 }) {
      Day lastDay = Day{ y.isLeapYear() ? 29 : 28 };
      if (d > lastDay) {
        return tl::make_unexpected("Day is out of range for selected Month");
      }
    }
    return Date(y, m, d);
  }
  std::string toString() const
  {
    return fmt::format("{}-{}-{}", year.getValue(), month.getValue(), day.getValue());
  }
  friend std::ostream &operator<<(std::ostream &os, Date const& date)
  {
    os << date.toString();
    return os;
  }
  auto operator<=>(Date const &) const = default;
  tl::expected<Date, Error> operator+(Year const& y) const
  {
    return Date::create(Year{ year.getValue() + y.getValue() }, month, day);
  }
  tl::expected<Date, Error> operator+(Month const& m) const
  {
    using LoggingLevel = cashoverflow::logging::LogLevel;

    auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::ERR);
    
    if (month.getValue() + m.getValue() < 12) {
      return Date::create(year, Month{ month.getValue() + m.getValue() }, day);
    }
    int yearsToAdd = m.getValue() / 12;
    LOGGER.write(yearsToAdd, LoggingLevel::DBG);

    int remainingMonths = m.getValue() % 12;
    LOGGER.write(remainingMonths, LoggingLevel::DBG);

    auto monthsToAdd = month.getValue() + remainingMonths;
    LOGGER.write(monthsToAdd, LoggingLevel::DBG);

    if (monthsToAdd > 12) {
      return Date::create(Year{ year.getValue() + yearsToAdd + 1 }, Month{ monthsToAdd - 12 }, day);
    } else {
      return Date::create(Year{ year.getValue() + yearsToAdd }, Month{ monthsToAdd }, day);
    }
  }

  tl::expected<Date, Error> operator+(Day d) const
  {
    auto m_ = month;
    auto y_ = year;
    auto d_ = day;
    while (d > m_.getNumberOfDays(y_)){
      d = Day{ d.getValue() - m_.getNumberOfDays(y_).getValue() };
      if (m_.getValue() == 12) {
        m_ = Month{ 1 };
        y_ = Year{ y_.getValue() + 1 };
      } else {
        m_ = Month{ m_.getValue() + 1 };
      }
    }
    d_ = Day{ d_.getValue() + d.getValue() };
    if (d_ > m_.getNumberOfDays(y_)) {
      d_ = Day{ d_.getValue() - m_.getNumberOfDays(y_).getValue() };
      m_ = Month{ m_.getValue() + 1 };
    }
    return Date::create(y_, m_, d_);
  }
private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d) {}
  Year year;
  Month month;
  Day day;
};

#endif// CASH_OVERFLOW_DATE_HPP
