#ifndef CASH_OVERFLOW_DATE_HPP
#define CASH_OVERFLOW_DATE_HPP

#include <chrono>
#include <tl/expected.hpp>
#include <fmt/format.h>

#include "error.hpp"
#include "logger.hpp"

enum class DaysOfTheWeek {
  Sunday,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
};

inline std::string toString(DaysOfTheWeek d)
{
  switch (d) {
  case DaysOfTheWeek::Sunday:
    return "Sunday";
  case DaysOfTheWeek::Monday:
    return "Monday";
  case DaysOfTheWeek::Tuesday:
    return "Tuesday";
  case DaysOfTheWeek::Wednesday:
    return "Wednesday";
  case DaysOfTheWeek::Thursday:
    return "Thursday";
  case DaysOfTheWeek::Friday:
    return "Friday";
  case DaysOfTheWeek::Saturday:
    return "Saturday";
  default:
    return "";
  }
}

class Day
{
public:
  [[nodiscard]] constexpr explicit Day(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Day const &) const = default;
  [[nodiscard]] constexpr int getValue() const
  {
    return value;
  }
  constexpr Day operator+(Day const &other) const
  {
    return Day{ value + other.value };
  }
  constexpr Day operator-(Day const &other) const
  {
    return Day{ value - other.value };
  }
  constexpr Day operator*(int factor) const
  {
    return Day{ factor * value };
  }
  friend constexpr Day operator*(int factor, Day const &day)
  {
    return day * factor;
  }
  constexpr Day operator/(int factor) const
  {
    return Day{ value / factor };
  }
  constexpr Day operator%(int factor) const
  {
    return Day{ value % factor };
  }
  constexpr Day &operator++()
  {
    ++value;
    return *this;
  }
  constexpr Day const operator++(int)
  {
    Day const d = *this;
    value++;
    return d;
  }

private:
  int value{};
};

class Year
{
public:
  [[nodiscard]] constexpr explicit Year(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Year const &) const = default;
  [[nodiscard]] constexpr int getValue() const
  {
    return value;
  }
  [[nodiscard]] constexpr bool isLeapYear() const
  {
    return value % 4 == 0 && !(value % 100 == 0 && (value % 400 != 0));
  }
  [[nodiscard]] constexpr Year getNumberOfDays() const
  {
    return Year{ isLeapYear() ? 366 : 365 };
  }
  constexpr Year operator+(Year const &other) const
  {
    return Year{ value + other.value };
  }
  constexpr Year operator-(Year const &other) const
  {
    return Year{ value - other.value };
  }
  constexpr Year operator*(int factor) const
  {
    return Year{ factor * value };
  }
  friend constexpr Year operator*(int factor, Year const &Year)
  {
    return Year * factor;
  }
  constexpr Year operator/(int factor) const
  {
    return Year{ value / factor };
  }
  constexpr Year operator%(int factor) const
  {
    return Year{ value % factor };
  }
  constexpr Year &operator++()
  {
    ++value;
    return *this;
  }
  constexpr Year const operator++(int)
  {
    Year const d = *this;
    value++;
    return d;
  }

private:
  int value{};
};

class Month
{
public:
  [[nodiscard]] constexpr explicit Month(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Month const &) const = default;
  [[nodiscard]] constexpr int getValue() const
  {
    return value;
  }
  [[nodiscard]] constexpr Day getNumberOfDays(Year const &year) const
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
  constexpr Month operator+(Month const &other) const
  {
    return Month{ value + other.value };
  }
  constexpr Month operator-(Month const &other) const
  {
    return Month{ value - other.value };
  }
  constexpr Month operator*(int factor) const
  {
    return Month{ factor * value };
  }
  friend constexpr Month operator*(int factor, Month const &Month)
  {
    return Month * factor;
  }
  constexpr Month operator/(int factor) const
  {
    return Month{ value / factor };
  }
  constexpr Month operator%(int factor) const
  {
    return Month{ value % factor };
  }
  constexpr Month &operator++()
  {
    ++value;
    return *this;
  }
  constexpr Month const operator++(int)
  {
    Month const d = *this;
    value++;
    return d;
  }
  [[nodiscard]] constexpr Year toYears() const
  {
    return Year{ value / 12 };
  }
  constexpr bool isOverAYear() const
  {
    return value > 12;
  }

private:
  int value{};
};


class Date
{
public:
  using Error = cash_overflow::error::Error;
  static tl::expected<Date, Error> create(int y, int m, int d)
  {
    return create(Year{ y }, Month{ m }, Day{ d });
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

    if (d > m.getNumberOfDays(y)) {
      return tl::make_unexpected("Day is out of range for selected Month");
    }

    return Date(y, m, d);
  }

  [[nodiscard]] std::string toString() const
  {
    return fmt::format("{}-{}-{}", year.getValue(), month.getValue(), day.getValue());
  }

  friend std::ostream &operator<<(std::ostream &os, Date const &date)
  {
    os << date.toString();
    return os;
  }

  auto operator<=>(Date const &) const = default;

  tl::expected<Date, Error> operator+(Year const &y) const
  {
    return Date::create(year + y, month, day);
  }

  tl::expected<Date, Error> operator+(Month const &m) const
  {
    using LoggingLevel = cashoverflow::logging::LogLevel;

    auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::ERR);

    if (month + m < Month{ 12 }) {
      return Date::create(year, month + m, day);
    }
    Year yearsToAdd = m.toYears();
    LOGGER.write(yearsToAdd.getValue(), LoggingLevel::DBG);

    Month remainingMonths = m % 12;
    LOGGER.write(remainingMonths.getValue(), LoggingLevel::DBG);

    Month monthsToAdd = month + remainingMonths;
    LOGGER.write(monthsToAdd.getValue(), LoggingLevel::DBG);

    if (monthsToAdd.isOverAYear()) {
      ++yearsToAdd;
      monthsToAdd = monthsToAdd - Month{ 12 };
    }

    return Date::create(year + yearsToAdd, monthsToAdd, day);
  }

  tl::expected<Date, Error> operator+(Day d) const
  {
    auto m_ = month;
    auto y_ = year;
    auto d_ = day;
    while (d > m_.getNumberOfDays(y_)) {
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

  // the website design is so bad that we are assuming
  // that everything stated there is true
  // including the algorithm to find the weekday
  // https://www.tondering.dk/claus/cal/chrweek.php#calcdow
  std::string getWeekDay()
  {
    auto a = (14 - month.getValue()) / 12;
    auto y = year.getValue() - a;
    auto m = month.getValue() + (12 * a) - 2;
    auto d = (day.getValue() + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    using LoggingLevel = cashoverflow::logging::LogLevel;
    auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::ERR);
    LOGGER.write(d, LoggingLevel::DBG);
    auto d_ = static_cast<DaysOfTheWeek>(d);
    return ::toString(d_);
  }

private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d) {}
  Year year;
  Month month;
  Day day;
};

#endif// CASH_OVERFLOW_DATE_HPP
