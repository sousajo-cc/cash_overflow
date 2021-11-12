#include <gtest/gtest.h>

#include "../src/imgui/util.hpp"

using cash_overflow::utils::map;

TEST(MapTests, DoubleTheNumbersInVec)
{
  std::vector<int> input{ 6, 42, -3 };
  std::vector<long int> expected_output{ 12l, 84l, -6l };
  auto output = map(input, [](int n) { return 2l * n; });
  EXPECT_EQ(output, expected_output);
}

TEST(MapTests, VecElementsToStringWithGenericLambda)
{
  std::vector<int> input{ 6, 42, -3 };
  std::vector<std::string> expected_output{ "6", "42", "-3" };
  auto output = map(input, [](auto n) { return std::to_string(n); });
  EXPECT_EQ(output, expected_output);
}

double halve(int i)
{
  return .5 * i;
}

TEST(MapTests, FunctionPointer)
{
  std::vector<int> input{ 6, 42, -3 };
  std::vector<double> expected_output{ 3.0, 21.0, -1.5 };
  auto output = map(input, halve);
  EXPECT_EQ(output, expected_output);
}

TEST(MapTests, Functor)
{
  std::vector<int> input{ 6, 42, -3 };
  std::vector<int> expected_output{ -7, -43, 2 };
  struct Functor
  {
    int operator()(int i)
    {
      return -(i + 1);
    }
  };
  auto output = map(input, Functor{});
  EXPECT_EQ(output, expected_output);
}
