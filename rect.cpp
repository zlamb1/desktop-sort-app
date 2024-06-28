#include <algorithm>

#include <glad/glad.h>

#include "rect.h"

Rectangle::Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {

}

void Rectangle::BufferData() {
    float screenSpaceX = std::min(std::max(x, 0.0f), 1.0f) * 2.0f - 1.0f;
    float screenSpaceY = std::min(std::max(y, 0.0f), 1.0f) * 2.0f - 1.0f;

    const float data[] = {
        screenSpaceX, -screenSpaceY, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        screenSpaceX, -screenSpaceY - height * 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        screenSpaceX + width * 2.0f, -screenSpaceY - height * 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        screenSpaceX + width * 2.0f, -screenSpaceY - height * 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        screenSpaceX + width * 2.0f, -screenSpaceY, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        screenSpaceX, -screenSpaceY, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
}

