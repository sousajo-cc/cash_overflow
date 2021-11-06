#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <algorithm>

namespace cash_overflow::util {

template<typename F, typename ReturnType, typename... ParamTypes>
concept Callable = requires (F function, ReturnType result, ParamTypes... params) {
  result = function(params...);
};

//WARNING: ignore this if you're starting to learn C++ now
//applies a function to every element on a vector
//refer to the tests for usage examples
template<typename Out, typename In, Callable<Out, In> F, template<typename> typename Container>
Container<Out> map(Container<In> const& input, F f) {
  Container<Out> output;
  output.resize(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  return output;
}

}

#endif//CASH_OVERFLOW_UTIL_H
