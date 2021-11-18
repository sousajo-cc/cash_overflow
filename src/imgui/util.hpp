#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <tl/expected.hpp>

#include <ranges>
#include <concepts>

namespace cash_overflow::utils {

// WARNING: ignore this if you're starting to learn C++ now
// applies a function to every element on a vector
// refer to the tests for usage examples
auto map(std::ranges::range auto const &input, auto f)
{
  using Out = decltype(f(input[0]));
  std::vector<Out> output{};
  for (auto val : input | std::ranges::views::transform(f)) {
    output.push_back(val);
  }
  return output;
}

inline std::string toString(std::vector<char> const &in)
{
  std::string s(in.begin(), in.end());
  return s;
}

inline std::string toLowerCase(std::string str)
{
  constexpr auto toLower = [](unsigned char c) -> char { return static_cast<char>(std::tolower(c)); };
  return toString(map(str, toLower));
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
