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

// WARNING: ignore this if you're starting to learn C++ now
// makes sure a type is printable
template<typename T>
concept Printable = requires(T t)
{
  std::cout << t << std::endl;
};

template<class Enum>
class IterableEnum
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
template<typename T>
constexpr IterableEnum<T>::Iterator begin(IterableEnum<T>)
{
  return typename IterableEnum<T>::Iterator(static_cast<int>(T::First));
}
template<typename T>
constexpr IterableEnum<T>::Iterator end(IterableEnum<T>)
{
  return typename IterableEnum<T>::Iterator(static_cast<int>(T::Last) + 1);
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
