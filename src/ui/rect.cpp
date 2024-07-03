#include <algorithm>

#include <glad/glad.h>

#include "rect.h"

namespace UI {

    Rectangle::Rectangle() {

    }

    const Radius& Rectangle::GetRadius() const {
        return radius; 
    }

}

