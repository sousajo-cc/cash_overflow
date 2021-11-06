#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

#include <algorithm>

namespace cash_overflow::util {

template<typename In, typename Out, typename F, template<typename> typename Container>
  requires requires (In input_element, Out output_element, F function) {
    output_element = function(input_element);
  }
Container<Out> map(Container<In> const& input, F f) {
  Container<Out> output;
  output.resize(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  return output;
}

}

#endif//CASH_OVERFLOW_UTIL_H
