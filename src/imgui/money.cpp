#include "money.hpp"

#include <cmath>
#include <iomanip>

namespace cash_overflow::money {

Money::Money(double a) : amount{ static_cast<int>(std::round(100 * a)) } {}

std::ostream &operator<<(std::ostream &os, Money money)
{
  os << money.amount / 100 << '.' << money.amount % 100;
  return os;
}

}// namespace cash_overflow::money
