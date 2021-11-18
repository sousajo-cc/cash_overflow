#ifndef CASH_OVERFLOW_RAII_WRAPPER_H
#define CASH_OVERFLOW_RAII_WRAPPER_H

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <tl/expected.hpp>
#include <imgui.h>

#include "../error.hpp"
#include "../util.hpp"
#include "window.hpp"
#include "tabBar.hpp"
#include "tabItem.hpp"
#include "text.hpp"

namespace cash_overflow::gui {
class Table
{
public:
  using Row = std::vector<Text>;
  class Builder
  {
  private:
    using Error = cash_overflow::error::Error;

  public:
    Builder &with_id(std::string name)
    {
      id = std::move(name);
      return *this;
    }
    Builder &with_number_of_columns(std::size_t n)
    {
      number_of_columns = n;
      return *this;
    }
    Builder &with_headers(Row row)
    {
      headers = std::move(row);
      return *this;
    }
    Builder &add_row(Row row)
    {
      values.push_back(std::move(row));
      return *this;
    }
    tl::expected<Table, Error> build()
    {
      if (headers.size() != number_of_columns) {
        return tl::make_unexpected(number_of_headers_error());
      }
      for (auto const &row : values) {
        if (row.size() != number_of_columns) {
          return tl::make_unexpected(number_of_row_values_error(row));
        }
      }
      return tl::expected<Table, Error>(
        tl::in_place,
        id,
        static_cast<int>(number_of_columns),
        headers,
        values);
    }

  private:
    [[nodiscard]] std::string number_of_columns_error(Row const &row, const char *msg) const
    {
      using cash_overflow::utils::map;
      auto text_to_string = [](Text const &text) {
        return text.get_text();
      };
      // using vformat instead of format to skip compile-time checks
      return fmt::vformat(
        msg,
        fmt::make_format_args(
          row.size() > number_of_columns ? "many" : "few",
          number_of_columns,
          row.size(),
          map(row, text_to_string)));
    }
    [[nodiscard]] std::string number_of_headers_error() const
    {
      return number_of_columns_error(headers,
        "Too {} headers!\n"
        "Table has {} columns but has {} headers.\n"
        "Headers: {}");
    }
    [[nodiscard]] std::string number_of_row_values_error(Row const &row) const
    {
      return number_of_columns_error(row,
        "Too {} values in row!\n"
        "Table has {} columns but row has {} values.\n"
        "Row: {}");
    }

    std::string id{};
    std::size_t number_of_columns{};
    Row headers{};
    std::vector<Row> values{};
  };

  explicit Table(std::string const &id, int number_of_columns, Row const &headers, std::vector<Row> const &values) : selected{ ImGui::BeginTable(id.c_str(), number_of_columns) }
  {
    create_headers(headers);
    for (auto const &row : values) {
      create_row(row);
    }
  }
  Table(Table const &) = delete;
  Table &operator=(Table const &) = delete;
  Table(Table &&) = delete;
  Table &operator=(Table &&) = delete;
  ~Table()
  {
    ImGui::EndTable();
  }
  explicit operator bool() &
  {
    return selected;
  }

private:
  static void create_headers(Row const &labels)
  {
    for (auto const &label : labels) {
      ImGui::TableSetupColumn(label.get_text().c_str());
    }
    ImGui::TableHeadersRow();
  }
  static void create_row(Row const &row)
  {
    for (auto const &value : row) {
      ImGui::TableNextColumn();
      value.write();
    }
  }

  bool selected{};
};

}// namespace cash_overflow::gui

#endif// CASH_OVERFLOW_RAII_WRAPPER_H
