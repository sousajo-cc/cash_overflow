#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <algorithm>

namespace cash_overflow::util {

template<typename In, typename Out, typename F, template<typename> typename Container>
Container<Out> map(Container<In> const& input, F f) {
  Container<Out> output;
  output.resize(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  return output;
}

}

#endif//CASH_OVERFLOW_UTIL_H
