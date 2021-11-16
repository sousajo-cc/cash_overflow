#ifndef CASH_OVERFLOW_DROPDOWN_HPP
#define CASH_OVERFLOW_DROPDOWN_HPP

#include <vector>
#include <string>
#include <iostream>

namespace cash_overflow::gui {
class DropDown
{
public:
  DropDown(std::vector<std::string> options, std::string currentSelectedCategoryType) : options_(std::move(options)),
                                                                                        currentSelectedItem(std::move(currentSelectedCategoryType))
  {
  }
  std::string draw()
  {
    if (ImGui::BeginCombo("##combo", currentSelectedItem.c_str())) {
      for (auto const &option : options_) {
        bool isSelected = (currentSelectedItem == option);
        if (ImGui::Selectable(option.c_str(), isSelected)) {
          currentSelectedItem = option.c_str();
        }
        if (isSelected) {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
    return currentSelectedItem;
  }

private:
  std::vector<std::string> options_;
  std::string currentSelectedItem;
};
}// namespace cash_overflow::gui
#endif// CASH_OVERFLOW_DROPDOWN_HPP
