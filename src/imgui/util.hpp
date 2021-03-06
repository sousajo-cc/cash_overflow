#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <tl/expected.hpp>

#include <algorithm>
#include <iostream>
#include <ranges>
#include <concepts>

namespace cash_overflow::utils {

inline std::string toLowerCase(std::string const &str)
{
  return str
         | ranges::views::transform([](unsigned char c) -> char { return static_cast<char>(std::tolower(c)); })
         | ranges::to<std::string>();
}

// WARNING: ignore this if you're starting to learn C++ now
// makes sure a type is printable
template<typename T>
concept Printable = requires(T t)
{
  std::cout << t << std::endl;
};

template<typename T>
concept EnumIterable = std::is_enum_v<T> && requires(T t)
{
  T::First;
  T::Last;
};

template<EnumIterable Enum>
class EnumIterator
{
public:
  class Iterator
  {
  public:
    constexpr Iterator(int value) : m_value(value) {}
    constexpr Enum operator*() const
    {
      return static_cast<Enum>(m_value);
    }
    constexpr void operator++()
    {
      ++m_value;
    }
    constexpr auto operator<=>(Iterator const &) const = default;

  private:
    int m_value;
  };
};

template<EnumIterable T>
constexpr std::size_t size()
{
  return static_cast<std::size_t>(T::Last) + 1;
}

template<EnumIterable T>
constexpr EnumIterator<T>::Iterator begin(EnumIterator<T>)
{
  return typename EnumIterator<T>::Iterator(static_cast<int>(T::First));
}

template<EnumIterable T>
constexpr EnumIterator<T>::Iterator end(EnumIterator<T>)
{
  return typename EnumIterator<T>::Iterator(static_cast<int>(T::Last) + 1);
}

}// namespace cash_overflow::utils

// WARNING: ignore this if you're starting to learn C++ now
// makes tl::expected printable if the value type and error type are printable
// great for making sense of GTest result
template<cash_overflow::utils::Printable V, cash_overflow::utils::Printable E>
std::ostream &operator<<(std::ostream &os, tl::expected<V, E> const &expected)
{
  if (expected) {
    os << expected.value();
  } else {
    os << expected.error();
  }
  return os;
}

#endif
