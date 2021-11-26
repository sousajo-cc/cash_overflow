#ifndef CASH_OVERFLOW_TEXT_HPP
#define CASH_OVERFLOW_TEXT_HPP
#include <imgui.h>
#include <string>
#include "colors.hpp"


namespace cash_overflow::gui {

class Text
{
  using Color=cash_overflow::colors::Color;

public:
  Text(char const *text_) : text{ text_ } {}
  Text(std::string text_) : text{ std::move(text_) } {}
  Text(char const *text_, Color color_) : text{ text_ }, color{ color_ } {}
  Text(std::string text_, Color color_) : text{ std::move(text_) }, color{ color_ } {}
  std::string get_text() const
  {
    return text;
  }
  std::optional<Color> get_color() const
  {
    return color;
  }
  void write() const
  {
    if (color) {
      ImGui::TextColored(color.value().getColor(), "%s", text.c_str());
    } else {
      ImGui::Text("%s", text.c_str());
    }
  }

private:
  std::string text{};
  std::optional<Color> color{};
};
}// namespace cash_overflow::gui
#endif
