#ifndef MYPROJECT_COLORS_H
#define MYPROJECT_COLORS_H

#include <imgui.h>

class Color
{
public:
  Color() : color{ 0.0f, 0.0f, 0.0f, 0.0f } {};
  Color(float r, float g, float b, float o) : color{ r, g, b, o } {};
  ImVec4 toImVec4() const
  {
    return color;
  }

private:
  ImVec4 color{};
};

namespace colors {
const Color Black{ .0F, .0F, .0F, 1.0F };
const Color White{ 1.0F, 1.0F, 1.0F, 1.0F };
const Color Red{ 1.0F, .0F, .0F, 1.0F };
const Color Lime{ .0F, 1.0F, .0F, 1.0F };
const Color Blue{ .0F, .0F, 1.0F, 1.0F };
const Color Yellow{ 1.0F, 1.0F, .0F, 1.0F };
const Color Cyan{ .1F, 1.0F, 1.0F, 1.0F };
const Color Magenta{ 1.0F, .0F, 1.0F, 1.0F };
const Color Silver{ .75F, .75F, .75F, 1.0F };
const Color Gray{ .5F, .5F, .5F, 1.0F };
const Color Maroon{ .5F, .0F, .0F, 1.0F };
const Color Olive{ .5F, .5F, .0F, 1.0F };
const Color Green{ .0F, .5F, .0F, 1.0F };
const Color Purple{ .5F, .0F, .5F, 1.0F };
const Color Teal{ .0F, .5F, .5F, 1.0F };
const Color Navy{ .0F, .0F, .5F, 1.0F };
}// namespace colors



#endif// MYPROJECT_COLORS_H
