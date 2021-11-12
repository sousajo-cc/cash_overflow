#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

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

}// namespace cash_overflow::utils

#endif
