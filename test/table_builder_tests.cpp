#include <gtest/gtest.h>

#include "../src/imgui/imgui_raii_wrapper.h"

TEST(TableBuilderTests, NoHeaders) {
  EXPECT_THROW({
    try {
      irw::Table::Builder{}
        .with_id("Table")
        .with_number_of_columns(3)
        .build();
    }
    catch(const cash_overflow::exception::BadTable& error) {
        EXPECT_STREQ("Too few headers!\nTable has 3 columns but has 0 headers.\nHeaders: []", error.what());
        throw;
    }
  }, cash_overflow::exception::BadTable);
}

TEST(TableBuilderTests, TooFewHeaders) {
  EXPECT_THROW({
    try {
      irw::Table::Builder{}
        .with_id("Table")
        .with_number_of_columns(3)
        .with_headers({ "header1", "header2" })
        .build();
    }
    catch(const cash_overflow::exception::BadTable& error) {
        EXPECT_STREQ("Too few headers!\nTable has 3 columns but has 2 headers.\nHeaders:"
          " [\"header1\", \"header2\"]", error.what());
        throw;
    }
  }, cash_overflow::exception::BadTable);
}

TEST(TableBuilderTests, TooManyHeaders) {
  EXPECT_THROW({
    try {
      irw::Table::Builder{}
        .with_id("Table")
        .with_number_of_columns(1)
        .with_headers({ "header1", "header2" })
        .build();
    }
    catch(const cash_overflow::exception::BadTable& error) {
        EXPECT_STREQ("Too many headers!\nTable has 1 columns but has 2 headers.\nHeaders:"
          " [\"header1\", \"header2\"]", error.what());
        throw;
    }
  }, cash_overflow::exception::BadTable);
}

TEST(TableBuilderTests, TooFewValuesInRow) {
  EXPECT_THROW({
    try {
      irw::Table::Builder{}
        .with_id("Table")
        .with_number_of_columns(3)
        .with_headers({ "header1", "header2", "header3" })
        .add_row({"value1"})
        .build();
    }
    catch(const cash_overflow::exception::BadTable& error) {
        EXPECT_STREQ("Too few values in row!\nTable has 3 columns but row has 1 values.\nRow:"
          " [\"value1\"]", error.what());
        throw;
    }
  }, cash_overflow::exception::BadTable);
}

TEST(TableBuilderTests, TooManyValuesInRow) {
  EXPECT_THROW({
    try {
      irw::Table::Builder{}
        .with_id("Table")
        .with_number_of_columns(2)
        .with_headers({ "header1", "header2" })
        .add_row({"value1", "value2"})
        .add_row({"value1", "value2", "value3"})
        .build();
    }
    catch(const cash_overflow::exception::BadTable& error) {
        EXPECT_STREQ("Too many values in row!\nTable has 2 columns but row has 3 values.\nRow:"
          " [\"value1\", \"value2\", \"value3\"]", error.what());
        throw;
    }
  }, cash_overflow::exception::BadTable);
}
