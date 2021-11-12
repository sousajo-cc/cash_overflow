#ifndef CASH_OVERFLOW_TABBAR_HPP
#define CASH_OVERFLOW_TABBAR_HPP

#include <imgui.h>
#include <string>

namespace cash_overflow::gui {
class [[nodiscard]] TabBar
{
public:
  explicit TabBar(std::string const &id) : selected{ ImGui::BeginTabBar(id.c_str()) } {}
  TabBar(TabBar const &) = delete;
  TabBar &operator=(TabBar const &) = delete;
  TabBar(TabBar &&) = delete;
  TabBar &operator=(TabBar &&) = delete;
  ~TabBar()
  {
    if (selected) {
      ImGui::EndTabBar();
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
