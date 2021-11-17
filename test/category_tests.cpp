#include <gtest/gtest.h>

#include "../src/imgui/category.hpp"

using cash_overflow::category::getAllValidCategoryNames;

TEST(CategoryTest, EnumIterationTest)
{
  std::vector<std::string> allValidCategoryNames{ "Assets", "Liabilities", "Incomes", "Expenses" };
  EXPECT_EQ(getAllValidCategoryNames(), allValidCategoryNames);
}
