#include <gtest/gtest.h>

#include "money.hpp"

using cash_overflow::money::Money;

TEST(MoneyTests, OutputOperator)
{
  std::stringstream ss;
  ss << Money{ 1.6571 };
  EXPECT_EQ(ss.str(), "1.66");
}

TEST(MoneyTests, Comparison)
{
  Money m1{ 1.6571 };
  Money m2{ 3, 32 };
  EXPECT_LT(m1, m2);
}

TEST(MoneyTests, Add)
{
  Money m1{ 1.6571 };
  Money m2{ 2.8362 };
  EXPECT_EQ(m1 + m2, Money(4, 50));
}
