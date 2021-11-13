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
  [[nodiscard]] constexpr explicit Day(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Day const &) const = default;
  int value{};
};

struct Week
{
public:
  [[nodiscard]] constexpr explicit Week(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Week const &) const = default;
  int value{};
};

struct Year
{
  [[nodiscard]] constexpr explicit Year(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Year const &) const = default;
  [[nodiscard]] constexpr bool isLeapYear() const
  {
    return value % 4 == 0 && !(value % 100 == 0 && (value % 400 != 0));
  }
  [[nodiscard]] constexpr Year getNumberOfDays() const
  {
    return Year{ isLeapYear() ? 366 : 365 };
  }
  int value{};
};

struct Month
{
  [[nodiscard]] constexpr explicit Month(int v) : value{ v } {}
  [[nodiscard]] constexpr auto operator<=>(Month const &) const = default;
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
  [[nodiscard]] constexpr Year toYears() const
  {
    return Year{ value / 12 };
  }
  constexpr bool isOverAYear() const
  {
    return value > 12;
  }
  int value{};
};

template<typename T>
struct isDurationType : std::false_type {};

template<typename T>
constexpr bool isDuration = isDurationType<T>::value;

template<>
struct isDurationType<Day> : std::true_type {};

template<>
struct isDurationType<Week> : std::true_type {};

template<>
struct isDurationType<Month> : std::true_type {};

template<>
struct isDurationType<Year> : std::true_type {};

template<typename T>
concept Duration = isDuration<T>;

template<Duration D>
constexpr D operator+(D const &d1, D const &d2)
{
  return D{ d1.value + d2.value };
}
template<Duration D>
constexpr D operator-(D const &d1, D const &d2)
{
  return D{ d1.value - d2.value };
}
template<Duration D>
constexpr D operator*(D const &d, int factor)
{
  return D{ factor * d.value };
}
template<Duration D>
constexpr D operator*(int factor, D const &day)
{
  return day * factor;
}
template<Duration D>
constexpr D operator/(D const &d, int factor)
{
  return D{ d.value / factor };
}
template<Duration D>
constexpr D operator%(D const &d, int factor)
{
  return D{ d.value % factor };
}
template<Duration D>
constexpr D &operator++(D &d)
{
  ++d.value;
  return d;
}
template<Duration D>
constexpr D const operator++(D &d, int)
{
  D const previous = d;
  d.value++;
  return previous;
}
template<Duration D>
constexpr D &operator--(D &d)
{
  --d.value;
  return d;
}
template<Duration D>
constexpr D const operator--(D &d, int)
{
  D const previous = d;
  d.value--;
  return previous;
}
template<Duration D>
constexpr D& operator+=(D &d, D const& other) {
  d.value += other.value;
  return d;
}
template<Duration D>
constexpr D& operator-=(D &d, D const& other) {
  d.value -= other.value;
  return d;
}
template<Duration D>
constexpr D& operator*=(D &d, int factor) {
  d.value *= factor;
  return d;
}
template<Duration D>
constexpr D& operator/=(D &d, int factor) {
  d.value /= factor;
  return d;
}
template<Duration D>
constexpr D& operator%=(D &d, int factor) {
  d.value %= factor;
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
    return fmt::format("{}-{}-{}", year.value, month.value, day.value);
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
    LOGGER.write(yearsToAdd.value, LoggingLevel::DBG);

    Month remainingMonths = m % 12;
    LOGGER.write(remainingMonths.value, LoggingLevel::DBG);

    Month monthsToAdd = month + remainingMonths;
    LOGGER.write(monthsToAdd.value, LoggingLevel::DBG);

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
      d = Day{ d.value - m_.getNumberOfDays(y_).value };
      if (m_.value == 12) {
        m_ = Month{ 1 };
        y_ = Year{ y_.value + 1 };
      } else {
        m_ = Month{ m_.value + 1 };
      }
    }
    d_ = Day{ d_.value + d.value };
    if (d_ > m_.getNumberOfDays(y_)) {
      d_ = Day{ d_.value - m_.getNumberOfDays(y_).value };
      m_ = Month{ m_.value + 1 };
    }
    return Date::create(y_, m_, d_);
  }

  // the website design is so bad that we are assuming
  // that everything stated there is true
  // including the algorithm to find the weekday
  // https://www.tondering.dk/claus/cal/chrweek.php#calcdow
  std::string getWeekDay()
  {
    auto a = (14 - month.value) / 12;
    auto y = year.value - a;
    auto m = month.value + (12 * a) - 2;
    auto d = (day.value + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
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
