#include <gtest/gtest.h>

#include "fileHandler.hpp"

using cashoverflow::utils::FileHandler;

TEST(FileHandlerTests, NonExistingFile)
{
  EXPECT_ANY_THROW(FileHandler{ "resources/nonexistingfile.txt" });
}

TEST(FileHandlerTests, ReadEmptyFile)
{
  FileHandler fileHandler{ "resources/empty_file.txt" };
  EXPECT_EQ(fileHandler.read(), "");
}

TEST(FileHandlerTests, ReadFile)
{
  FileHandler fileHandler{ "resources/example_file.txt" };
  constexpr auto expected_output = R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Etiam eget ligula eu lectus lobortis condimentum.
Aliquam nonummy auctor massa.
Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.
Nulla at risus.
Quisque purus magna, auctor et, sagittis ac, posuere eu, lectus.
Nam mattis, felis ut adipiscing.
)";
  EXPECT_EQ(fileHandler.read(), expected_output);
}
