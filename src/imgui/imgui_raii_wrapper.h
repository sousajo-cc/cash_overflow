#ifndef MYPROJECT_IMGUI_RAII_WRAPPER_H
#define MYPROJECT_IMGUI_RAII_WRAPPER_H

#include "util.h"

#include <optional>
#include <string>
#include <vector>

#include <imgui.h>

namespace irw {

class Windowzita {
public:
  [[nodiscard]] explicit Windowzita(std::string const& id) : selected{ImGui::Begin(id.c_str())} {}
  Windowzita(Windowzita const&) = delete;
  Windowzita& operator=(Windowzita const&) = delete;
  Windowzita(Windowzita&&) = delete;
  Windowzita& operator=(Windowzita&&) = delete;
  ~Windowzita() {
    ImGui::End();
  }
  explicit operator bool() & {
    return selected;
  }
private:
  bool selected{};
};

class TabBar {
public:
  [[nodiscard]] explicit TabBar(std::string const& id) : selected{ImGui::BeginTabBar(id.c_str())} {}
  TabBar(TabBar const&) = delete;
  TabBar& operator=(TabBar const&) = delete;
  TabBar(TabBar&&) = delete;
  TabBar& operator=(TabBar&&) = delete;
  ~TabBar() {
    ImGui::EndTabBar();
  }
  explicit operator bool() & {
    return selected;
  }
private:
  bool selected{};
};

class TabItem {
public:
  [[nodiscard]] explicit TabItem(std::string const& id) : selected{ImGui::BeginTabItem(id.c_str())} {}
  TabItem(TabItem const&) = delete;
  TabItem& operator=(TabItem const&) = delete;
  TabItem(TabItem&&) = delete;
  TabItem& operator=(TabItem&&) = delete;
  ~TabItem() {
    if (selected) {
      ImGui::EndTabItem();
    }
  }
  explicit operator bool() & {
    return selected;
  }
private:
  bool selected{};
};

class Text {
public:
  explicit Text(std::string text_) : text{std::move(text_)} {}
  Text(std::string text_, ImVec4 color_) : text{std::move(text_)}, color{color_} {}
  std::string get_text() const {
    return text;
  }
  std::optional<ImVec4> get_color() const {
    return color;
  }
  void write() const {
    if (color) {
      ImGui::TextColored(color.value(), "%s", text.c_str());
    } else {
      ImGui::Text("%s", text.c_str());
    }
  }
private:
  std::string text{};
  std::optional<ImVec4> color{};
};

class Table {
private:
  using Row = std::vector<Text>;
public:
  class Builder {
  public:
    Builder& with_id(std::string name) {
      id = std::move(name);
      return *this;
    }
    Builder& with_number_of_columns(std::size_t n) {
      number_of_columns = n;
      return *this;
    }
    template<typename... Args>
    Builder& with_headers(Args... args) {
      headers.reserve(number_of_columns);
      util::emplace_back_all<Row, Args...>(headers, args...);
      return *this;
    }
    template<typename... Args>
    Builder& add_row(Args... args) {
      Row row{};
      row.reserve(number_of_columns);
      util::emplace_back_all<Row, Args...>(row, args...);
      values.push_back(row);
      return *this;
    }
    Table build() {
      return Table{
        id,
        static_cast<int>(number_of_columns),
        headers,
        values
      };
    }
  private:
    std::string id{};
    std::size_t number_of_columns{};
    Row headers{};
    std::vector<Row> values{};
  };

  explicit Table(std::string const& id, int number_of_columns, Row const& headers, std::vector<Row> const& values) : selected{ImGui::BeginTable(id.c_str(), number_of_columns)} {
    create_headers(headers);
    for (auto const& row : values) {
      create_row(row);
    }
  }
  Table(Table const&) = delete;
  Table& operator=(Table const&) = delete;
  Table(Table&&) = delete;
  Table& operator=(Table&&) = delete;
  ~Table() {
    ImGui::EndTable();
  }
  explicit operator bool() & {
    return selected;
  }
private:
  static void create_headers(Row const& labels) {
    for (auto const& label : labels) {
      ImGui::TableSetupColumn(label.get_text().c_str());
    }
    ImGui::TableHeadersRow();
  }
  static void create_row(Row const& row) {
    for (auto const& value : row) {
      ImGui::TableNextColumn();
      value.write();
    }
  }

  bool selected{};
};

}

#endif//MYPROJECT_IMGUI_RAII_WRAPPER_H
