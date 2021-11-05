#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <algorithm>
#include <functional>

namespace cash_overflow::util {

template<typename In, typename Out>
std::vector<Out> map(std::vector<In> const& input, std::function<Out(In)> const& f) {
  std::vector<Out> output;
  output.resize(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  return output;
}

}

#endif//CASH_OVERFLOW_UTIL_H
