#ifndef CASH_OVERFLOW_QUERYBUILDER_HPP
#define CASH_OVERFLOW_QUERYBUILDER_HPP

#include <algorithm>
#include <optional>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

#include "util.hpp"


namespace cash_overflow::db {
// TODO: Return expected
struct QueryBuilder
{
  virtual ~QueryBuilder(){};
  QueryBuilder() = default;
  virtual std::string go() = 0;
};

class SelectQueryBuilder;
class InsertQueryBuilder;

class Query
{
public:
  friend class InsertQueryBuilder;
  friend class SelectQueryBuilder;
  static InsertQueryBuilder insert();
  static SelectQueryBuilder select();

private:
  Query() = default;
};


class InsertQueryBuilder : public QueryBuilder
{
public:
  InsertQueryBuilder &into(std::string name)
  {
    table = std::move(name);
    return *this;
  }
  InsertQueryBuilder &on_column(std::string const &name)
  {
    columns.push_back(name);
    return *this;
  }
  InsertQueryBuilder &with_value(std::string const &name)
  {
    values.push_back(name);
    return *this;
  }

  std::string go() override
  {
    std::ostringstream v;
    preparedQuery << "insert into ";
    preparedQuery << table;
    preparedQuery << "(";
    v << " values(";
    for (std::size_t i = 0; i < columns.size(); ++i) {
      if (i < columns.size() - 1) {
        preparedQuery << columns[i];
        preparedQuery << ", ";
        v << values[i];
        v << ", ";
      } else {
        preparedQuery << columns[i];
        preparedQuery << ")";
        v << values[i];
        v << ")";
      }
    }
    preparedQuery << v.str();
    return preparedQuery.str();
  }

private:
  std::string table{};
  std::vector<std::string> columns;
  std::vector<std::string> values;
  Query query;
  std::ostringstream preparedQuery{};
};

class SelectQueryBuilder : public QueryBuilder
{
  // select password from user where
public:
  SelectQueryBuilder &from(std::string name)
  {
    table = std::move(name);
    return *this;
  }
  SelectQueryBuilder &where(std::string const &c)
  {
    condition.push_back(c);
    return *this;
  }
  SelectQueryBuilder &fields(std::string const &column)
  {
    // TODO: for now only one field maybe we need to variadic here after but I'm tired
    columns.push_back(column);
    return *this;
  }

  std::string go() override
  {
    preparedQuery << "select ";
    // TODO: this we will then need a fold vec to string separated by ','
    preparedQuery << columns[0];
    preparedQuery << " from ";
    preparedQuery << table;
    preparedQuery << " where ";
    // TODO: this we will then need a fold vec to string separated by 'and's
    preparedQuery << condition[0];
    return preparedQuery.str();
  }

private:
  std::string table{};
  std::vector<std::string> condition;
  std::vector<std::string> columns;
  Query query;
  std::ostringstream preparedQuery{};
};

InsertQueryBuilder Query::insert()
{
  return InsertQueryBuilder();
}
SelectQueryBuilder Query::select()
{
  return SelectQueryBuilder();
}
}// namespace cash_overflow::db
#endif// CASH_OVERFLOW_QUERYBUILDER_HPP
