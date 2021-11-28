#include <gtest/gtest.h>
#include "../src/imgui/date.hpp"
#include "../src/imgui/util.hpp"

using cash_overflow::date::Day;
using cash_overflow::date::Week;
using cash_overflow::date::Month;
using cash_overflow::date::Year;
using cash_overflow::date::Date;

template<Duration D>
class DurationArithmeticTest : public ::testing::Test
{
};

TYPED_TEST_SUITE_P(DurationArithmeticTest);

TYPED_TEST_P(DurationArithmeticTest, AddTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 68 };
  EXPECT_EQ(y + z, TypeParam{ 71 });
  EXPECT_EQ(y += TypeParam{ 2 }, TypeParam{ 5 });
  EXPECT_EQ(y, TypeParam{ 5 });
}

TYPED_TEST_P(DurationArithmeticTest, SubtractTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 68 };
  EXPECT_EQ(y - z, TypeParam{ -65 });
  EXPECT_EQ(y -= TypeParam{ 2 }, TypeParam{ 1 });
  EXPECT_EQ(y, TypeParam{ 1 });
  EXPECT_EQ(-z, TypeParam{ -68 });
}

TYPED_TEST_P(DurationArithmeticTest, MultiplyTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(3 * y, TypeParam{ 9 });
  EXPECT_EQ(y * 3, TypeParam{ 9 });
  EXPECT_EQ(y *= 3, TypeParam{ 9 });
  EXPECT_EQ(y, TypeParam{ 9 });
}

TYPED_TEST_P(DurationArithmeticTest, DivideTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(y / 2, TypeParam{ 1 });
  EXPECT_EQ(y /= 3, TypeParam{ 1 });
  EXPECT_EQ(y, TypeParam{ 1 });
}

TYPED_TEST_P(DurationArithmeticTest, RemainderTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(y % 2, TypeParam{ 1 });
}

TYPED_TEST_P(DurationArithmeticTest, PreIncrementTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(++y, TypeParam{ 4 });
  EXPECT_EQ(y, TypeParam{ 4 });
}

TYPED_TEST_P(DurationArithmeticTest, PostIncrementTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(y++, TypeParam{ 3 });
  EXPECT_EQ(y, TypeParam{ 4 });
}

TYPED_TEST_P(DurationArithmeticTest, PreDecrementTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(--y, TypeParam{ 2 });
  EXPECT_EQ(y, TypeParam{ 2 });
}

TYPED_TEST_P(DurationArithmeticTest, PostDecrementTest)
{
  TypeParam y{ 3 };
  EXPECT_EQ(y--, TypeParam{ 3 });
  EXPECT_EQ(y, TypeParam{ 2 });
}

TYPED_TEST_P(DurationArithmeticTest, EqualityTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 3 };
  EXPECT_EQ(y, z);
}

TYPED_TEST_P(DurationArithmeticTest, InequalityTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 68 };
  EXPECT_NE(y, z);
}

TYPED_TEST_P(DurationArithmeticTest, LessThanTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 68 };
  EXPECT_LT(y, z);
  EXPECT_LE(y, z);
}

TYPED_TEST_P(DurationArithmeticTest, GreaterThanTest)
{
  TypeParam y{ 3 };
  TypeParam const z{ 68 };
  EXPECT_GT(z, y);
  EXPECT_GE(z, y);
}

REGISTER_TYPED_TEST_SUITE_P(DurationArithmeticTest,
  AddTest,
  SubtractTest,
  MultiplyTest,
  DivideTest,
  RemainderTest,
  PreIncrementTest,
  PostIncrementTest,
  PreDecrementTest,
  PostDecrementTest,
  EqualityTest,
  InequalityTest,
  LessThanTest,
  GreaterThanTest);

INSTANTIATE_TYPED_TEST_SUITE_P(Year, DurationArithmeticTest, Year);
INSTANTIATE_TYPED_TEST_SUITE_P(Month, DurationArithmeticTest, Month);
INSTANTIATE_TYPED_TEST_SUITE_P(Week, DurationArithmeticTest, Week);
INSTANTIATE_TYPED_TEST_SUITE_P(Day, DurationArithmeticTest, Day);

TEST(WeekTest, ToString)
{
  using cash_overflow::date::toString;
  using cash_overflow::date::DaysOfTheWeek;
  EXPECT_EQ(toString(DaysOfTheWeek::Sunday), "Sunday");
  EXPECT_EQ(toString(DaysOfTheWeek::Monday), "Monday");
  EXPECT_EQ(toString(DaysOfTheWeek::Tuesday), "Tuesday");
  EXPECT_EQ(toString(DaysOfTheWeek::Wednesday), "Wednesday");
  EXPECT_EQ(toString(DaysOfTheWeek::Thursday), "Thursday");
  EXPECT_EQ(toString(DaysOfTheWeek::Friday), "Friday");
  EXPECT_EQ(toString(DaysOfTheWeek::Saturday), "Saturday");
  EXPECT_EQ(toString(static_cast<DaysOfTheWeek>(-1)), "");
}

TEST(YearTest, LeapYear)
{
  EXPECT_TRUE(Year{ 1988 }.isLeapYear());
  EXPECT_TRUE(Year{ 2000 }.isLeapYear());
  EXPECT_FALSE(Year{ 1989 }.isLeapYear());
  EXPECT_FALSE(Year{ 1900 }.isLeapYear());
}

TEST(MonthTest, NumberOfDays)
{
  EXPECT_EQ(Month{ 1 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 2 }.getNumberOfDays(Year{ 1988 }), Day{ 29 });
  EXPECT_EQ(Month{ 2 }.getNumberOfDays(Year{ 1989 }), Day{ 28 });
  EXPECT_EQ(Month{ 3 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 4 }.getNumberOfDays(Year{ 1988 }), Day{ 30 });
  EXPECT_EQ(Month{ 5 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 6 }.getNumberOfDays(Year{ 1988 }), Day{ 30 });
  EXPECT_EQ(Month{ 7 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 8 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 9 }.getNumberOfDays(Year{ 1988 }), Day{ 30 });
  EXPECT_EQ(Month{ 10 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ 11 }.getNumberOfDays(Year{ 1988 }), Day{ 30 });
  EXPECT_EQ(Month{ 12 }.getNumberOfDays(Year{ 1988 }), Day{ 31 });
  EXPECT_EQ(Month{ -1 }.getNumberOfDays(Year{ 1988 }), Day{ 0 });
}

TEST(MonthTest, toString)
{
  EXPECT_EQ(Month{ 1 }.toString(), "January");
  EXPECT_EQ(Month{ 2 }.toString(), "February");
  EXPECT_EQ(Month{ 3 }.toString(), "March");
  EXPECT_EQ(Month{ 4 }.toString(), "April");
  EXPECT_EQ(Month{ 5 }.toString(), "May");
  EXPECT_EQ(Month{ 6 }.toString(), "June");
  EXPECT_EQ(Month{ 7 }.toString(), "July");
  EXPECT_EQ(Month{ 8 }.toString(), "August");
  EXPECT_EQ(Month{ 9 }.toString(), "September");
  EXPECT_EQ(Month{ 10 }.toString(), "October");
  EXPECT_EQ(Month{ 11 }.toString(), "November");
  EXPECT_EQ(Month{ 12 }.toString(), "December");
  EXPECT_EQ(Month{ 13 }.toString(), "");
}

TEST(DateTest, YearTooLow)
{
  EXPECT_FALSE(Date::create(1969, 1, 1));
}

TEST(DateTest, MonthTooLow)
{
  EXPECT_FALSE(Date::create(1989, 0, 1));
}

TEST(DateTest, MonthTooHigh)
{
  EXPECT_FALSE(Date::create(1989, 13, 1));
}

TEST(DateTest, DayTooLow)
{
  EXPECT_FALSE(Date::create(1989, 1, 0));
}

TEST(DateTest, DayTooHigh)
{
  EXPECT_FALSE(Date::create(1989, 1, 32));
  EXPECT_FALSE(Date::create(1989, 2, 29));
  EXPECT_FALSE(Date::create(1988, 2, 30));
  EXPECT_FALSE(Date::create(1900, 2, 29));
  EXPECT_FALSE(Date::create(2000, 2, 30));
  EXPECT_FALSE(Date::create(2001, 2, 29));
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

TEST(DateTest, AddYearTest)
{
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Year{ 3 }, Date::create(1991, 2, 3).value());
  EXPECT_FALSE(Date::create(1988, 2, 29).value() + Year{ 1 });
}

TEST(DateTest, AddMonthTest)
{
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Month{ 3 }, Date::create(1988, 5, 3).value());
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Month{ 13 }, Date::create(1989, 3, 3).value());
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Month{ 23 }, Date::create(1990, 1, 3).value());
  EXPECT_FALSE(Date::create(1988, 2, 29).value() + Month{ 12 });
}

TEST(DateTest, AddDayTest)
{
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Day{ 3 }, Date::create(1988, 2, 6).value());
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Day{ 30 }, Date::create(1988, 3, 4).value());
  EXPECT_EQ(Date::create(1989, 2, 3).value() + Day{ 30 }, Date::create(1989, 3, 5).value());
  EXPECT_EQ(Date::create(1988, 2, 3).value() + Day{ 365 }, Date::create(1989, 2, 2).value());
  EXPECT_EQ(Date::create(1989, 2, 3).value() + Day{ 365 }, Date::create(1990, 2, 3).value());
}

TEST(DateTest, GetWeekDayTest)
{
  EXPECT_EQ(Date::create(1989, 2, 3).value().getWeekDay(), "Friday");
  EXPECT_EQ(Date::create(1988, 2, 3).value().getWeekDay(), "Wednesday");
  EXPECT_EQ(Date::create(2021, 11, 13).value().getWeekDay(), "Saturday");
  EXPECT_EQ(Date::create(2021, 11, 12).value().getWeekDay(), "Friday");
  EXPECT_EQ(Date::create(2022, 07, 13).value().getWeekDay(), "Wednesday");
}

TEST(DateTest, DaysUntilTest)
{
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(1989, 2, 3).value()), Day{ 0 });
  EXPECT_EQ(Date::create(1989, 2, 3).value() - Date::create(1989, 2, 3).value(), Day{ 0 });
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(1989, 2, 27).value()), Day{ 24 });
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(1989, 3, 3).value()), Day{ 28 });
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(1989, 3, 1).value()), Day{ 26 });
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(1990, 1, 6).value()), Day{ 337 });
  EXPECT_EQ(Date::create(1989, 2, 3).value().daysUntil(Date::create(2009, 10, 30).value()), Day{ 7574 });
  EXPECT_EQ(Date::create(2009, 10, 30).value().daysUntil(Date::create(1989, 2, 3).value()), -Day{ 7574 });
}

TEST(DateTest, StreamOperatorOnDate)
{
  std::ostringstream os;
  os << Date::create(1989, 2, 3).value();
  EXPECT_EQ(os.str(), "1989-2-3");
}

TEST(DateTest, StreamOperatorOnExpectedDate)
{
  std::ostringstream os;
  os << Date::create(1989, 2, 3);
  EXPECT_EQ(os.str(), "1989-2-3");
}

TEST(DateTest, StreamOperatorOnUnexpectedDate)
{
  std::ostringstream os;
  os << Date::create(1989, 2, 32);
  EXPECT_NE(os.str(), "1989-2-32");
}

TEST(DateTest, GetMonthName)
{
  EXPECT_EQ(Date::create(1989, 1, 3).value().getMonthName(), "January");
  EXPECT_EQ(Date::create(1989, 2, 3).value().getMonthName(), "February");
  EXPECT_EQ(Date::create(1989, 3, 3).value().getMonthName(), "March");
  EXPECT_EQ(Date::create(1989, 4, 3).value().getMonthName(), "April");
  EXPECT_EQ(Date::create(1989, 5, 3).value().getMonthName(), "May");
  EXPECT_EQ(Date::create(1989, 6, 3).value().getMonthName(), "June");
  EXPECT_EQ(Date::create(1989, 7, 3).value().getMonthName(), "July");
  EXPECT_EQ(Date::create(1989, 8, 3).value().getMonthName(), "August");
  EXPECT_EQ(Date::create(1989, 9, 3).value().getMonthName(), "September");
  EXPECT_EQ(Date::create(1989, 10, 3).value().getMonthName(), "October");
  EXPECT_EQ(Date::create(1989, 11, 3).value().getMonthName(), "November");
  EXPECT_EQ(Date::create(1989, 12, 3).value().getMonthName(), "December");
}
