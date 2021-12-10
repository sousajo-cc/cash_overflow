#include <gtest/gtest.h>

#include "../src/imgui/queryBuilder.hpp"

using Query = cash_overflow::db::Query;
TEST(InsertQueryTests, Insert)
{
  auto in = Query::insert().into("user").with_value("jorge").on_column("username").with_value("jndaiskjndad").on_column("password").go();
  auto output = "insert into user(username, password) values(jorge, jndaiskjndad)";
  EXPECT_EQ(output, in);
}

TEST(InsertQueryTests, Select)
{
  auto in = Query::select().fields("password").from("user").where("username = my_username").go();
  auto output = "select password from user where username = my_username";
  EXPECT_EQ(output, in);
}
