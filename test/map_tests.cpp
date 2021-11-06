#include <gtest/gtest.h>

#include "../src/imgui/util.h"

using cash_overflow::util::map;

TEST(MapTests, DoubleTheNumbersInVec) {
  std::vector<int> input{6, 42, -3};
  std::vector<long int> expected_output{12l, 84l, -6l};
  auto output = map(input, [](int n) { return 2l*n; });
  EXPECT_EQ(output, expected_output);
}

TEST(MapTests, VecElementsToString) {
  std::vector<int> input{6, 42, -3};
  std::vector<std::string> expected_output{"6", "42", "-3"};
  auto output = map(input, [](int n) { return std::to_string(n); });
  EXPECT_EQ(output, expected_output);
}
