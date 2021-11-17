#include <gtest/gtest.h>
#include "../src/imgui/error.hpp"
#include "../src/imgui/util.hpp"

using namespace cash_overflow::error;
using ErrorType = cash_overflow::error::ErrorType;

TEST(ErrorTest, TableErrorTest)
{
  std::cout << Error<ErrorType::TableError>("failed to build table");

}

TEST(ErrorTest, DateErrorTest)
{

}