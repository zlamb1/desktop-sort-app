#include <algorithm>

#include <glad/glad.h>

#include "rect.hpp"

namespace UI {

    Rectangle::Rectangle() {

    }

    const Radius& Rectangle::GetRadius() const {
        return radius; 
    }

}

