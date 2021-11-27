#include <gtest/gtest.h>
#include "../src/imgui/date.hpp"
#include "../src/imgui/util.hpp"

using cash_overflow::date::Day;
using cash_overflow::date::Week;
using cash_overflow::date::Month;
using cash_overflow::date::Year;
using cash_overflow::date::Date;

TEST(YearArithmeticTest, AddTest)
{
  Year y{ 3 };
  Year const z{ 68 };
  EXPECT_EQ(y + z, Year{ 71 });
  EXPECT_EQ(y += Year{ 2 }, Year{ 5 });
  EXPECT_EQ(y, Year{ 5 });
}

TEST(YearArithmeticTest, SubtractTest)
{
  Year y{ 3 };
  Year const z{ 68 };
  EXPECT_EQ(y - z, Year{ -65 });
  EXPECT_EQ(y -= Year{ 2 }, Year{ 1 });
  EXPECT_EQ(y, Year{ 1 });
  EXPECT_EQ(-z, Year{ -68 });
}

TEST(YearArithmeticTest, MultiplyTest)
{
  Year y{ 3 };
  EXPECT_EQ(3 * y, Year{ 9 });
  EXPECT_EQ(y * 3, Year{ 9 });
  EXPECT_EQ(y *= 3, Year{ 9 });
  EXPECT_EQ(y, Year{ 9 });
}

TEST(YearArithmeticTest, DivideTest)
{
  Year y{ 3 };
  EXPECT_EQ(y / 2, Year{ 1 });
  EXPECT_EQ(y /= 3, Year{ 1 });
  EXPECT_EQ(y, Year{ 1 });
}

TEST(YearArithmeticTest, RemainderTest)
{
  Year y{ 3 };
  EXPECT_EQ(y % 2, Year{ 1 });
}

TEST(YearArithmeticTest, PreIncrementTest)
{
  Year y{ 3 };
  EXPECT_EQ(++y, Year{ 4 });
  EXPECT_EQ(y, Year{ 4 });
}

TEST(YearArithmeticTest, PostIncrementTest)
{
  Year y{ 3 };
  EXPECT_EQ(y++, Year{ 3 });
  EXPECT_EQ(y, Year{ 4 });
}

TEST(YearArithmeticTest, PreDecrementTest)
{
  Year y{ 3 };
  EXPECT_EQ(--y, Year{ 2 });
  EXPECT_EQ(y, Year{ 2 });
}

TEST(YearArithmeticTest, PostDecrementTest)
{
  Year y{ 3 };
  EXPECT_EQ(y--, Year{ 3 });
  EXPECT_EQ(y, Year{ 2 });
}

TEST(MonthTest, ArithmeticTest)
{
  Month m{ 3 };
  Month const n{ 68 };
  EXPECT_EQ(m + n, Month{ 71 });
  EXPECT_EQ(m - n, Month{ -65 });
  EXPECT_EQ(3 * m, Month{ 9 });
  EXPECT_EQ(m * 3, Month{ 9 });
  EXPECT_EQ(m / 2, Month{ 1 });
  EXPECT_EQ(m % 2, Month{ 1 });
  ++m;
  EXPECT_EQ(++m, Month{ 5 });
  m++;
  EXPECT_EQ(m++, Month{ 6 });
  --m;
  EXPECT_EQ(--m, Month{ 5 });
  m--;
  EXPECT_EQ(m--, Month{ 4 });
  EXPECT_EQ(m += Month{ 2 }, Month{ 5 });
  EXPECT_EQ(m -= Month{ 1 }, Month{ 4 });
  EXPECT_EQ(m *= 3, Month{ 12 });
  EXPECT_EQ(m /= 4, Month{ 3 });
  EXPECT_EQ(-m, Month{ -3 });
}

TEST(WeekTest, ArithmeticTest)
{
  Week w{ 3 };
  Week const x{ 68 };
  EXPECT_EQ(w + x, Week{ 71 });
  EXPECT_EQ(w - x, Week{ -65 });
  EXPECT_EQ(3 * w, Week{ 9 });
  EXPECT_EQ(w * 3, Week{ 9 });
  EXPECT_EQ(w / 2, Week{ 1 });
  EXPECT_EQ(w % 2, Week{ 1 });
  ++w;
  EXPECT_EQ(++w, Week{ 5 });
  w++;
  EXPECT_EQ(w++, Week{ 6 });
  --w;
  EXPECT_EQ(--w, Week{ 5 });
  w--;
  EXPECT_EQ(w--, Week{ 4 });
  EXPECT_EQ(w += Week{ 2 }, Week{ 5 });
  EXPECT_EQ(w -= Week{ 1 }, Week{ 4 });
  EXPECT_EQ(w *= 3, Week{ 12 });
  EXPECT_EQ(w /= 4, Week{ 3 });
  EXPECT_EQ(-w, Week{ -3 });
}

TEST(DayTest, ArithmeticTest)
{
  Day d{ 3 };
  Day const e{ 68 };
  EXPECT_EQ(d + e, Day{ 71 });
  EXPECT_EQ(d - e, Day{ -65 });
  EXPECT_EQ(3 * d, Day{ 9 });
  EXPECT_EQ(d * 3, Day{ 9 });
  EXPECT_EQ(d / 2, Day{ 1 });
  EXPECT_EQ(d % 2, Day{ 1 });
  ++d;
  EXPECT_EQ(++d, Day{ 5 });
  d++;
  EXPECT_EQ(d++, Day{ 6 });
  --d;
  EXPECT_EQ(--d, Day{ 5 });
  d--;
  EXPECT_EQ(d--, Day{ 4 });
  EXPECT_EQ(d += Day{ 2 }, Day{ 5 });
  EXPECT_EQ(d -= Day{ 1 }, Day{ 4 });
  EXPECT_EQ(d *= 3, Day{ 12 });
  EXPECT_EQ(d /= 4, Day{ 3 });
  EXPECT_EQ(-d, Day{ -3 });
}

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
