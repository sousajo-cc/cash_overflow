#ifndef CASH_OVERFLOW_QUERYBUILDER_HPP
#define CASH_OVERFLOW_QUERYBUILDER_HPP

#include <algorithm>
#include <optional>
#include <string>
#include <memory>
#include <vector>

#include "util.hpp"


namespace cash_overflow::db {
// Query::createQueryOfType("insert").into("user").with_value("jorge").on_column("username")
//                                                .with_value("jndaiskjndad").on_column("password").go();
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
    std::string v;
    preparedQuery.append("insert into ");
    preparedQuery.append(table);
    preparedQuery.append("(");
    v.append(" values(");
    for (std::size_t i = 0; i < columns.size(); ++i) {
      if (i < columns.size() - 1) {
        preparedQuery.append(columns[i]);
        preparedQuery.append(", ");
        v.append(values[i]);
        v.append(", ");
      } else {
        preparedQuery.append(columns[i]);
        preparedQuery.append(")");
        v.append(values[i]);
        v.append(")");
      }
    }
    preparedQuery.append(v);
    return preparedQuery;
  }

  operator Query()
  {
    return query;
  }

private:
  std::string table{};
  std::vector<std::string> columns;
  std::vector<std::string> values;
  Query query;
  std::string preparedQuery{};
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
    preparedQuery.append("select ");
    // TODO: this we will then need a fold vec to string separated by ','
    preparedQuery.append(columns[0]);
    preparedQuery.append(" from ");
    preparedQuery.append(table);
    preparedQuery.append(" where ");
    // TODO: this we will then need a fold vec to string separated by 'and's
    preparedQuery.append(condition[0]);
    return preparedQuery;
  }

  operator Query()
  {
    return query;
  }

private:
  std::string table{};
  std::vector<std::string> condition;
  std::vector<std::string> columns;
  Query query;
  std::string preparedQuery{};
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
