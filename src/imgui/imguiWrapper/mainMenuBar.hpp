#ifndef CASH_OVERFLOW_MAINMENUBAR_HPP
#define CASH_OVERFLOW_MAINMENUBAR_HPP

namespace cash_overflow::gui {

class [[nodiscard]] MainMenuBar {
public:
  explicit MainMenuBar() : selected {ImGui::BeginMainMenuBar()} {}
  MainMenuBar(MainMenuBar const&) = delete;
  MainMenuBar &operator=(MainMenuBar const&) = delete;
  MainMenuBar(MainMenuBar &&) = delete;
  MainMenuBar &operator=(MainMenuBar &&) = delete;
  ~MainMenuBar(){
    if(selected) {
      ImGui::EndMainMenuBar();
    }
  }

  explicit operator bool()&{
    return selected;
  }

private:
  bool selected{};
};

}
#endif// CASH_OVERFLOW_MAINMENUBAR_HPP

