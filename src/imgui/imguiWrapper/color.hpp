#ifndef CASH_OVERFLOW_COLOR_H
#define CASH_OVERFLOW_COLOR_H

#include <imgui.h>

class Color
{
public:
  Color() : color{ 0.0f, 0.0f, 0.0f, 0.0f } {};
  Color(float r, float g, float b, float o) : color{ r, g, b, o } {};
  ImVec4 getColor() const
  {
    return color;
  }

private:
  ImVec4 color{};
};

#endif//CASH_OVERFLOW_COLORS_H
