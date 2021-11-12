#include <gtest/gtest.h>

#include "../src/imgui/imgui_raii_wrapper.h"

TEST(TableBuilderTests, NoHeaders) {
  auto unexpected = irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(3)
    .build();
  EXPECT_FALSE(unexpected);
}

TEST(TableBuilderTests, TooFewHeaders) {
  auto unexpected = irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(3)
    .with_headers({ "header1", "header2" })
    .build();
  EXPECT_FALSE(unexpected);
}

TEST(TableBuilderTests, TooManyHeaders) {
  auto unexpected = irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(1)
    .with_headers({ "header1", "header2" })
    .build();
  EXPECT_FALSE(unexpected);
}

TEST(TableBuilderTests, TooFewValuesInRow) {
  auto unexpected = irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(3)
    .with_headers({ "header1", "header2", "header3" })
    .add_row({"value1"})
    .build();
  EXPECT_FALSE(unexpected);
}

TEST(TableBuilderTests, TooManyValuesInRow) {
  auto unexpected = irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(2)
    .with_headers({ "header1", "header2" })
    .add_row({"value1", "value2"})
    .add_row({"value1", "value2", "value3"})
    .build();
  EXPECT_FALSE(unexpected);
}
