#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <tl/expected.hpp>

#include <algorithm>
#include <concepts>

namespace cash_overflow::utils {

// WARNING: ignore this if you're starting to learn C++ now
// applies a function to every element on a vector
// refer to the tests for usage examples
template<typename In, std::invocable<In> F, template<typename> typename Container>
auto map(Container<In> const &input, F f) -> Container<decltype(f(input[0]))>
{
  using Out = decltype(f(input[0]));
  Container<Out> output;
  output.resize(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  return output;
}

// WARNING: ignore this if you're starting to learn C++ now
// makes tl::expected printable if the value type and error type are printable
// great for making sense of GTest result
template<typename V, typename E>
requires requires (V v, E e) {
  std::cout << v;
  std::cout << e;
}
std::ostream& operator<<(std::ostream& os, tl::expected<V, E> const& expected) {
  if (expected) {
    os << expected.value();
  } else {
    os << expected.error();
  }
  return os;
}

}// namespace cash_overflow::utils

#endif
