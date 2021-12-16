#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "fileHandler.hpp"
#include "error.hpp"

#include <string>
#include <tl/expected.hpp>


namespace cash_overflow {
namespace csv {

  using Row = std::vector<std::string>;
  using Error = cash_overflow::error::Error;

  namespace detail {

    tl::expected<Row, Error> tokenizer(const std::string_view lineContent, size_t columnSize)
    {

      std::size_t currentPos = 0;
      std::size_t start;
      std::size_t end;
      Row output;

      do {
        std::size_t found = lineContent.find(',', currentPos);

        start = currentPos;
        if (found != std::string::npos) {
          end = found - currentPos;
        } else {
          end = std::string::npos;
        }

        output.emplace_back(lineContent.substr(start, end));

        if (lineContent[found] == ',' && found + 1 < lineContent.size())
          found++;
        currentPos = found;

      } while (end != std::string::npos);

      if (output.size() != columnSize)
        return tl::make_unexpected("Column size not correct");

      return output;
    }


    template<typename T>
    T parse(const std::string &value)
    {
      return {};
    }

    template<>
    std::string parse<std::string>(const std::string &value)
    {
      return value;
    }

    template<>
    unsigned int parse<unsigned int>(const std::string &value)
    {
      unsigned int integer = 0;
      for (const char &c : value) {
        if (std::isdigit(c)) {
          integer = integer * 10 + static_cast<unsigned int>(c - '0');
        }
      }
      return integer;
    }

    /**
     * Need to check the overflow, and call the unsigned version in the end **/

    template<>
    int parse<int>(const std::string &value)
    {
      int integer = 0;
      bool first = true;
      for (const char &c : value) {
        if (first) {
          if (c == '-') {
            integer = -1;
          } else {
            integer = 1;
          }
        }
        first = false;
      }

      return integer;
    }


  }// namespace detail

  class AnyType
  {
    std::unordered_map<std::string, std::string> any;

  public:
    AnyType(Row header, Row values)
    {
      auto it_header = header.begin();
      auto it_value = values.begin();

      while (it_header != header.end() && it_value != values.end()) {
        any.emplace(std::make_pair(*it_header, *it_value));

        ++it_header;
        ++it_value;
      }
    }

    template<typename Type>
    Type get(std::string key) const
    {
      auto search = any.find(key);
      if (search == any.end()) {
        return {};
      }

      return detail::parse<Type>(search->second);
    }
  };

  class Parser
  {
    using FileHandler = cashoverflow::utils::IFileHandler;

    std::string fileName;
    Row header;

    size_t columSize;
    std::unique_ptr<FileHandler> fileHandler;

    tl::expected<bool, Error> validateHeader(size_t headerSize)
    {
      if (auto output = detail::tokenizer(fileHandler->readLine(), headerSize); output)
        header = std::move(output.value());
      else
        return tl::make_unexpected("Not able to parse the header");

      return true;
    }

  public:
    Parser(std::unique_ptr<FileHandler> argFileHandler) : fileHandler{ std::move(argFileHandler) }
    {
    }

    tl::expected<Row, Error> getHeader(size_t headerSize)
    {
      if (auto output = this->validateHeader(headerSize); !output) {
        return tl::make_unexpected("Invalid header");
      }

      return header;
    }

    size_t getColumnSize() const
    {
      return header.size();
    }

    AnyType parseNextLine() const
    {
      auto lineParsed = detail::tokenizer(fileHandler->readLine(), getColumnSize());

      if (header.empty() || !lineParsed) {
        return AnyType(csv::Row{}, csv::Row{});
      }

      AnyType type{ header, lineParsed.value() };
      return type;
    }
  };


}// namespace csv
}// namespace cash_overflow

#endif
