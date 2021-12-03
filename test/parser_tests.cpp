#include <gtest/gtest.h>
#include "csvparser.hpp"

TEST(ParserTest, ParseHeader)
{

  std::string rawStr = R"(Type1,Type2,Type3,Type4,Type5)";

  // TODO: Pass IFileHandler and column size
  CSV::Parser parserHandler(rawStr, 5);


  // Return true if files contains the headers specified.
  // When empty all first line is the header according to the size.
  auto output = parserHandler.validateHeader();

  ASSERT_TRUE(output);

  auto header = parserHandler.getHeader();

  ASSERT_EQ(header.size(), 5);
  EXPECT_EQ(header.at(0), "Type1");
  EXPECT_EQ(header.at(1), "Type2");
  EXPECT_EQ(header.at(2), "Type3");
  EXPECT_EQ(header.at(3), "Type4");
  EXPECT_EQ(header.at(4), "Type5");
}

TEST(ParserTest, ParseHeaderJustOneColumn)
{

  std::string rawStr = R"(Type1)";
  CSV::Parser parser(rawStr, 2);

  std::vector<std::string> header = parser.getHeader();

  ASSERT_EQ(header.size(), 1);
  EXPECT_EQ(header.at(0), "Type1");
}

TEST(ParserTest, ParseString)
{
  std::string rawStr = "Full Name,Age,Address,Cell Phone\nJohn Wick,44,Casa da Musica,800800800";
  CSV::Parser parser(rawStr, 4);


  auto output = parser.validateHeader();

  ASSERT_TRUE(output);

  auto line = parser.getNextLine();

  std::string FullName = parser.get<std::string>("Full Name");
  std::string Address  = parser.get<std::string>("Address");
  unsigned Age         = parser.get<unsigned>("Age");

  std::cout << FullName << Address << Age << std::endl;

//  EXPECT_EQ(line["Full Name"]),"John Wick");
//  EXPECT_EQ(line["Age"]),44);
//  EXPECT_EQ(line["Address"]),"Casa da Musica");
//  EXPECT_EQ(line["Cell Phone"]),800800800);
}
