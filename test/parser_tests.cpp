#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "csvparser.hpp"
#include "fileHandler.hpp"

using ::testing::Return;


class MockFileHandler : public cashoverflow::utils::IFileHandler
{
public:
  MOCK_METHOD(std::string, read, (), (const, override));
  MOCK_METHOD(unsigned int, read, (char *buffer, int size), (override));
  MOCK_METHOD(std::string, readLine, (), (override));
  MOCK_METHOD(std::string, getFileName, (), (const, override));
};

TEST(ParserTest, ParseHeader)
{
  std::unique_ptr<MockFileHandler> fileHandler = std::make_unique<MockFileHandler>();

  EXPECT_CALL(*fileHandler, readLine()).WillOnce(Return("Type1,Type2,Type3,Type4,Type5"));

  CSV::Parser parserHandler(std::move(fileHandler));

  auto header = parserHandler.getHeader(5).value_or(CSV::Row{});

  ASSERT_EQ(header.size(), 5);
  EXPECT_EQ(header.at(0), "Type1");
  EXPECT_EQ(header.at(1), "Type2");
  EXPECT_EQ(header.at(2), "Type3");
  EXPECT_EQ(header.at(3), "Type4");
  EXPECT_EQ(header.at(4), "Type5");
}

TEST(ParserTest, ParseHeaderJustOneColumn)
{

  std::unique_ptr<MockFileHandler> fileHandler = std::make_unique<MockFileHandler>();

  EXPECT_CALL(*fileHandler, readLine()).WillOnce(Return("Type1"));
  CSV::Parser parser(std::move(fileHandler));

  auto header = parser.getHeader(1).value_or(CSV::Row{});

  ASSERT_EQ(header.size(), 1);
  EXPECT_EQ(header.at(0), "Type1");
}

TEST(ParserTest, ParseString)
{
  std::unique_ptr<MockFileHandler> fileHandler = std::make_unique<MockFileHandler>();

  EXPECT_CALL(*fileHandler, readLine())
    .Times(2)
    .WillOnce(Return("Full Name,Age,Address,Cell Phone"))
    .WillOnce(Return("John Wick,44,Casa da Musica,800800800"));

  CSV::Parser parser(std::move(fileHandler));

  auto header = parser.getHeader(4).value_or(CSV::Row{});

  auto line = parser.parseNextLine();

  std::string FullName = line.get<std::string>("Full Name");
  std::string Address = line.get<std::string>("Address");
  unsigned Age = line.get<unsigned>("Age");
  unsigned CellPhone = line.get<unsigned>("Cell Phone");

  EXPECT_EQ(FullName, "John Wick");
  EXPECT_EQ(Address, "Casa da Musica");
  EXPECT_EQ(Age, 44);
  EXPECT_EQ(CellPhone, 800800800);
}
