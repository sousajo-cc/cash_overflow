#include <gtest/gtest.h>

#include "logger.hpp"

using cashoverflow::logging::Logger;
using cashoverflow::logging::LogLevel;

class LoggerTests : public ::testing::Test {
protected:
  void SetUp() override {
    originalBuf = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
  }
  void TearDown() override {
    std::cout.rdbuf(originalBuf);
  }
  std::string output() {
    return ss.str();
  }
private:
  std::ostringstream ss{};
  std::streambuf* originalBuf{};
};

TEST_F(LoggerTests, WriteDbgOnDbgLogger) {
  auto& logger = Logger::log(LogLevel::DBG);
  logger.write("message", LogLevel::DBG);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;245;245;245m[DBG] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteInfOnDbgLogger) {
  auto& logger = Logger::log(LogLevel::DBG);
  logger.write("message", LogLevel::INF);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;070;130;180m[INF] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteWarnOnDbgLogger) {
  auto& logger = Logger::log(LogLevel::DBG);
  logger.write("message", LogLevel::WARN);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;255;255;000m[WARN] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteErrOnDbgLogger) {
  auto& logger = Logger::log(LogLevel::DBG);
  logger.write("message", LogLevel::ERR);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;220;020;060m[ERR] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteDbgOnInfLogger) {
  auto& logger = Logger::log(LogLevel::INF);
  logger.write("message", LogLevel::DBG);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteInfOnInfLogger) {
  auto& logger = Logger::log(LogLevel::INF);
  logger.write("message", LogLevel::INF);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;070;130;180m[INF] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteWarnOnInfLogger) {
  auto& logger = Logger::log(LogLevel::INF);
  logger.write("message", LogLevel::WARN);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;255;255;000m[WARN] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteErrOnInfLogger) {
  auto& logger = Logger::log(LogLevel::INF);
  logger.write("message", LogLevel::ERR);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;220;020;060m[ERR] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteDbgOnWarnLogger) {
  auto& logger = Logger::log(LogLevel::WARN);
  logger.write("message", LogLevel::DBG);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteInfOnWarnLogger) {
  auto& logger = Logger::log(LogLevel::WARN);
  logger.write("message", LogLevel::INF);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteWarnOnWarnLogger) {
  auto& logger = Logger::log(LogLevel::WARN);
  logger.write("message", LogLevel::WARN);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;255;255;000m[WARN] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteErrOnWarnLogger) {
  auto& logger = Logger::log(LogLevel::WARN);
  logger.write("message", LogLevel::ERR);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;220;020;060m[ERR] message\n\x1B[0m");
}

TEST_F(LoggerTests, WriteDbgOnErrLogger) {
  auto& logger = Logger::log(LogLevel::ERR);
  logger.write("message", LogLevel::DBG);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteInfOnErrLogger) {
  auto& logger = Logger::log(LogLevel::ERR);
  logger.write("message", LogLevel::INF);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteWarnOnErrLogger) {
  auto& logger = Logger::log(LogLevel::ERR);
  logger.write("message", LogLevel::WARN);
  EXPECT_EQ(output(), "");
}

TEST_F(LoggerTests, WriteErrOnErrLogger) {
  auto& logger = Logger::log(LogLevel::ERR);
  logger.write("message", LogLevel::ERR);
  EXPECT_EQ(output(), "\x1B[1m\x1B[38;2;220;020;060m[ERR] message\n\x1B[0m");
}
