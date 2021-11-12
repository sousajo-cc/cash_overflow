#include <gtest/gtest.h>
#include "../src/imgui/date.hpp"

TEST(DateTest, BasicAssertions)
{
  auto unexpected = Date::create(-1, -1, -1);
  EXPECT_FALSE(unexpected);
}

TEST(DateTest, InvalidYears)
{
  auto unexpected = Date::create(1969, -1, -1);
  EXPECT_FALSE(unexpected);
}

TEST(DateTest, ValidYears)
{
  auto unexpected = Date::create(1979, 2, 1);
  EXPECT_TRUE(unexpected);
}
