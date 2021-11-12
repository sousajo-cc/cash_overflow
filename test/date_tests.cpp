#include <gtest/gtest.h>
#include "../src/imgui/date.hpp"

TEST(DateTest, YearOutOfRange)
{
  auto unexpected = Date::create(-1, 1, 1);
  EXPECT_FALSE(unexpected);
}

TEST(DateTest, MonthOutOfRange)
{
  EXPECT_FALSE(Date::create(1989, -1, 1));
  EXPECT_FALSE(Date::create(1989, 13, 1));
}

TEST(DateTest, DayOutOfRange)
{
  EXPECT_FALSE(Date::create(1989, 1, -1));
  EXPECT_FALSE(Date::create(1989, 1, 32));
  EXPECT_FALSE(Date::create(1989, 2, 29));
  EXPECT_FALSE(Date::create(1989, 3, 32));
  EXPECT_FALSE(Date::create(1989, 4, 31));
  EXPECT_FALSE(Date::create(1989, 5, 32));
  EXPECT_FALSE(Date::create(1989, 6, 31));
  EXPECT_FALSE(Date::create(1989, 7, 32));
  EXPECT_FALSE(Date::create(1989, 8, 32));
  EXPECT_FALSE(Date::create(1989, 9, 31));
  EXPECT_FALSE(Date::create(1989, 10, 32));
  EXPECT_FALSE(Date::create(1989, 11, 31));
  EXPECT_FALSE(Date::create(1989, 12, 32));
}

TEST(DateTest, DayOutOfRangeOnLeapYear)
{
  EXPECT_FALSE(Date::create(1988, 2, 30));
  EXPECT_FALSE(Date::create(1900, 2, 29));
  EXPECT_FALSE(Date::create(2000, 2, 30));
  EXPECT_FALSE(Date::create(2001, 2, 29));
}

TEST(DateTest, ToStringTest)
{
  auto date = Date::create(1988, 2, 3);
  ASSERT_TRUE(date);
  EXPECT_EQ(date.value().toString(), "1988-2-3");
}

TEST(DateTest, ComparisonTest)
{
  EXPECT_EQ(Date::create(1988, 2, 3).value(), Date::create(1988, 2, 3).value());
  EXPECT_NE(Date::create(1988, 2, 3).value(), Date::create(1988, 2, 4).value());
  EXPECT_NE(Date::create(1988, 2, 3).value(), Date::create(1988, 3, 3).value());
  EXPECT_NE(Date::create(1988, 2, 3).value(), Date::create(1984, 2, 3).value());
  EXPECT_GT(Date::create(1988, 2, 3).value(), Date::create(1984, 2, 3).value());
  EXPECT_GE(Date::create(1988, 2, 3).value(), Date::create(1984, 2, 3).value());
  EXPECT_LT(Date::create(1984, 2, 3).value(), Date::create(1988, 2, 3).value());
  EXPECT_LE(Date::create(1984, 2, 3).value(), Date::create(1988, 2, 3).value());
}
