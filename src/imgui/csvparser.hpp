#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "fileHandler.hpp"
#include "error.hpp"

#include <string>
#include <tl/expected.hpp>


namespace CSV {

using Row = std::vector<std::string>;
using Error = cash_overflow::error::Error;

namespace MISC {

  tl::expected<Row, Error> tokenizer(const std::string_view lineContent, size_t columnSize)
  {

    size_t currentPos = 0;
    size_t start;
    size_t end;
    Row output;


    do {
      std::size_t found = lineContent.find(',', currentPos);

      if (found != std::string::npos) {
        start = currentPos;
        end = found - currentPos;
      } else {
        start = currentPos;
        end = std::string::npos;
      }

      output.emplace_back(static_cast<std::string>(lineContent.substr(start, end)));

      if (lineContent[found] == ',' && found + 1 < lineContent.size())
        found++;
      currentPos = found;

    } while (end != std::string::npos);

    if (output.size() != columnSize)
      return tl::make_unexpected("Column size not correct");

    return output;
  };


  template<typename T>
  T parse(const std::string &value)
  {
    std::cout << value << "T\n";
    return {};
  }

  template<>
  int parse<int>(const std::string &value)
  {
    std::cout << value << "int\n";
    return {};
    // ...implementation details when T is int
  }

  template<>
  unsigned int parse<unsigned int>(const std::string &value)
  {
    std::cout << value << "u_int\n";
    return {};
    // ...implementation details when T is int
  }


}// namespace MISC

class Parser
{

  std::string fileContent;
  Row header;

  std::unordered_map<std::string, std::string> any;

  size_t columSize;

public:
  Parser(std::string argContent, size_t argColumnSize) : fileContent{ std::move(argContent) }, columSize(argColumnSize)
  {
  }


  tl::expected<bool, Error> validateHeader()
  {
    /* TODO: Read from file only  the first line
    std::string firsLine {reader->readFirstLine()}*/
    std::string firsLine{ fileContent };

    auto output = MISC::tokenizer(firsLine, columSize);

    if (output)
      header = std::move(output.value());
    else
      return tl::make_unexpected("Not able to parse the header");

    return true;
  }

  Row getHeader() const
  {
    return header;
  }

  size_t getColumnSize() const
  {
    return columSize;
  }

  std::string getNextLine() const
  {


    return {};
  }

  template<typename Type>
  Type get(std::string key) const
  {
    /*auto search = any.find(key);
    if (search == any.end())
    {
      return {};
    }*/

    return MISC::parse<Type>(key);
  }
};

class AnyType
{
  std::unordered_map<std::string, std::any> any;

public:
  template<typename Type>
  tl::expected<Type, Error> getValue(const std::string &key) const
  {
    auto it = any.find(key);
    if (it == any.end()) {
      return tl::make_unexpected("Not able to find Key");
    }

    return std::any_cast<Type>(it->second);
  }
  template<typename Type>
  void setValue(const std::string &key, Type value)
  {
    any[key] = value;
  }
};


}// namespace CSV
#endif
