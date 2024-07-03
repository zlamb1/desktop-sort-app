#pragma once

#include <optional>

#include "math.h"

/**
 * Most attributes that are null-defined are automatically inherited.
 * The style object will cascade most of it's properties to children UI elements with a few notable exceptions:
 * - backgroundColor
 */

template<typename T>
using optional = std::optional<T>;

namespace UI {

    struct Color {
        float r, g, b, a; 

        Color() : r(0), g(0), b(0), a(1) {}
        Color(Vec3<float> rgb) : r(rgb.x), g(rgb.y), b(rgb.z), a(1) {}
        Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
        Color(Vec4<float> rgba) : r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {} 
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    };

    struct Style {
        optional<Color> backgroundColor; 
        optional<Color> textColor; 
    };

    static Style CascadeStyles(const Style& child, const Style& parent) {
        Style copy = child; 
        if (parent.textColor) copy.textColor = parent.textColor; 
        return copy; 
    }

}

