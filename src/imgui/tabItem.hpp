#ifndef CASH_OVERFLOW_TABITEM_HPP
#define CASH_OVERFLOW_TABITEM_HPP

#include <imgui.h>
#include <string>

namespace cash_overflow::gui {
class [[nodiscard]] TabItem
{
public:
  explicit TabItem(std::string const &id) : selected{ ImGui::BeginTabItem(id.c_str()) } {}
  TabItem(TabItem const &) = delete;
  TabItem &operator=(TabItem const &) = delete;
  TabItem(TabItem &&) = delete;
  TabItem &operator=(TabItem &&) = delete;
  ~TabItem()
  {
    if (selected) {
      ImGui::EndTabItem();
    }
  }
  explicit operator bool() &
  {
    return selected;
  }

private:
  bool selected{};
};
}// namespace cash_overflow::gui

#endif
