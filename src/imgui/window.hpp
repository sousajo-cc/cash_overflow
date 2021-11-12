#ifndef CASH_OVERFLOW_WINDOW_H
#define CASH_OVERFLOW_WINDOW_H

#include <imgui.h>
#include <string>

namespace cash_overflow::gui {
class [[nodiscard]] Window
{
public:
  explicit Window(std::string const &id) : selected{ ImGui::Begin(id.c_str()) } {}
  Window(Window const &) = delete;
  Window &operator=(Window const &) = delete;
  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;
  ~Window()
  {
    ImGui::End();
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
