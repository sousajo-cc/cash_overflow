#ifndef CASH_OVERFLOW_MONEY_HPP
#define CASH_OVERFLOW_MONEY_HPP

#include <iostream>

namespace cash_overflow::money {

class Money
{
public:
  explicit Money(double a);
  constexpr explicit Money(int currency, int cents) : amount{ 100 * currency + cents } {}
  friend std::ostream &operator<<(std::ostream &os, Money money);
  [[nodiscard]] constexpr auto operator<=>(Money const &) const = default;
  constexpr auto operator+(Money const other) const
  {
    return Money{ 0, amount + other.amount };
  }
  constexpr auto operator-(Money const other) const
  {
    return Money{ 0, amount - other.amount };
  }
  constexpr auto operator-() const
  {
    return Money{ 0, -amount };
  }
  constexpr auto &operator+=(Money const &other)
  {
    amount += other.amount;
    return *this;
  }
  constexpr auto &operator-=(Money const &other)
  {
    amount -= other.amount;
    return *this;
  }

private:
  int amount;
};

}// namespace cash_overflow::money

#endif//CASH_OVERFLOW_MONEY_HPP
