#ifndef CASH_OVERFLOW_UTIL_H
#define CASH_OVERFLOW_UTIL_H

namespace util {
template<typename Vec, typename Arg, typename... Args>
void emplace_back_all(Vec& row, Arg arg, Args... args) {
  row.emplace_back(arg);
  if constexpr (sizeof...(Args) != 0) {
    emplace_back_all<Vec, Args...>(row, args...);
  }
}
}

#endif//CASH_OVERFLOW_UTIL_H
