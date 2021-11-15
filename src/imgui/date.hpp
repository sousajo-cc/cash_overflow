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

struct Day
{
  [[nodiscard]] constexpr explicit Day(int v) : durationValue{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Day const &) const = default;
  int durationValue{};
};

struct Week
{
public:
  [[nodiscard]] constexpr explicit Week(int v) : durationValue{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Week const &) const = default;
  int durationValue{};
};

struct Year
{
  [[nodiscard]] constexpr explicit Year(int v) : durationValue{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Year const &) const = default;
  [[nodiscard]] constexpr bool isLeapYear() const
  {
    return durationValue % 4 == 0 && !(durationValue % 100 == 0 && (durationValue % 400 != 0));
  }
  [[nodiscard]] constexpr Year getNumberOfDays() const
  {
    return Year{ isLeapYear() ? 366 : 365 };
  }
  int durationValue{};
};

struct Month
{
  [[nodiscard]] constexpr explicit Month(int v) : durationValue{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Month const &) const = default;
  [[nodiscard]] constexpr Day getNumberOfDays(Year const &year) const
  {
    switch (durationValue) {
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
  [[nodiscard]] constexpr Year toYears() const
  {
    return Year{ durationValue / 12 };
  }
  constexpr bool isOverAYear() const
  {
    return durationValue > 12;
  }
  int durationValue{};
};

template<typename T>
concept Duration = std::is_same_v<T, Day> || std::is_same_v<T, Week> || std::is_same_v<T, Month> || std::is_same_v<T, Year>;

template<Duration D>
constexpr D operator+(D const &d1, D const &d2)
{
  return D{ d1.durationValue + d2.durationValue };
}
template<Duration D>
constexpr D operator-(D const &d1, D const &d2)
{
  return D{ d1.durationValue - d2.durationValue };
}
template<Duration D>
constexpr D operator*(D const &d, int factor)
{
  return D{ factor * d.durationValue };
}
template<Duration D>
constexpr D operator*(int factor, D const &day)
{
  return day * factor;
}
template<Duration D>
constexpr D operator/(D const &d, int factor)
{
  return D{ d.durationValue / factor };
}
template<Duration D>
constexpr D operator%(D const &d, int factor)
{
  return D{ d.durationValue % factor };
}
template<Duration D>
constexpr D &operator++(D &d)
{
  ++d.durationValue;
  return d;
}
template<Duration D>
constexpr D const operator++(D &d, int)
{
  D const previous = d;
  d.durationValue++;
  return previous;
}
template<Duration D>
constexpr D &operator--(D &d)
{
  --d.durationValue;
  return d;
}
template<Duration D>
constexpr D const operator--(D &d, int)
{
  D const previous = d;
  d.durationValue--;
  return previous;
}
template<Duration D>
constexpr D &operator+=(D &d, D const &other)
{
  d.durationValue += other.durationValue;
  return d;
}
template<Duration D>
constexpr D &operator-=(D &d, D const &other)
{
  d.durationValue -= other.durationValue;
  return d;
}
template<Duration D>
constexpr D &operator*=(D &d, int factor)
{
  d.durationValue *= factor;
  return d;
}
template<Duration D>
constexpr D &operator/=(D &d, int factor)
{
  d.durationValue /= factor;
  return d;
}
template<Duration D>
constexpr D &operator%=(D &d, int factor)
{
  d.durationValue %= factor;
  return d;
}

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
    return fmt::format("{}-{}-{}", year.durationValue, month.durationValue, day.durationValue);
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
    LOGGER.write(yearsToAdd.durationValue, LoggingLevel::DBG);

    Month remainingMonths = m % 12;
    LOGGER.write(remainingMonths.durationValue, LoggingLevel::DBG);

    Month monthsToAdd = month + remainingMonths;
    LOGGER.write(monthsToAdd.durationValue, LoggingLevel::DBG);

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
      d = Day{ d.durationValue - m_.getNumberOfDays(y_).durationValue };
      if (m_.durationValue == 12) {
        m_ = Month{ 1 };
        y_ = Year{ y_.durationValue + 1 };
      } else {
        m_ = Month{ m_.durationValue + 1 };
      }
    }
    d_ = Day{ d_.durationValue + d.durationValue };
    if (d_ > m_.getNumberOfDays(y_)) {
      d_ = Day{ d_.durationValue - m_.getNumberOfDays(y_).durationValue };
      m_ = Month{ m_.durationValue + 1 };
    }
    return Date::create(y_, m_, d_);
  }

  // the website design is so bad that we are assuming
  // that everything stated there is true
  // including the algorithm to find the weekday
  // https://www.tondering.dk/claus/cal/chrweek.php#calcdow
  std::string getWeekDay()
  {
    auto a = (14 - month.durationValue) / 12;
    auto y = year.durationValue - a;
    auto m = month.durationValue + (12 * a) - 2;
    auto d = (day.durationValue + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    using LoggingLevel = cashoverflow::logging::LogLevel;
    auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::ERR);
    LOGGER.write(d, LoggingLevel::DBG);
    auto d_ = static_cast<DaysOfTheWeek>(d);
    return ::toString(d_);
  }
  std::string getMonthName() const
  {
    switch (month.durationValue) {
    case 11:
      return "November";
    case 4:
      return "April";
    case 6:
      return "June";
    case 9:
      return "September";
    case 12:
      return "December";
    case 10:
      return "October";
    case 8:
      return "August";
    case 7:
      return "July";
    case 5:
      return "May";
    case 3:
      return "March";
    case 1:
      return "January";
    case 2:
      return "February";
    default:
      return "Onzember";
    }
  }
private:
  Date(Year y, Month m, Day d) : year(y), month(m), day(d) {}
  Year year;
  Month month;
  Day day;
};

#endif// CASH_OVERFLOW_DATE_HPP
