#ifndef CASH_OVERFLOW_MENU_HPP
#define CASH_OVERFLOW_MENU_HPP

namespace cash_overflow::gui {

class [[nodiscard]] Menu
{
public:
  explicit Menu(std::string const &id) : selected{ ImGui::BeginMenu(id.c_str()) } {}
  Menu(Menu const &) = delete;
  Menu &operator=(Menu const &) = delete;
  Menu(Menu &&) = delete;
  Menu &operator=(Menu &&) = delete;
  ~Menu()
  {
    if (selected) {
      ImGui::EndMenu();
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
#endif// CASH_OVERFLOW_MENU_HPP
