#include <algorithm>

#include <glad/glad.h>

#include "rect.h"

Rectangle::Rectangle() {

}

Rectangle::Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {

}

Vec2<float> Rectangle::GetCenter() const {
    return Vec2<float>{ 0.0f, 0.0f };
}

BoundingRect Rectangle::GetBoundingRect() const {
    float ndcWidth = width * 2.0f;
    float ndcHeight = height * 2.0f;
    float left = x * 2.0f - 1.0f;
    float right = left + ndcWidth; 
    float top = -(y * 2.0f - 1.0f);
    float bottom = top - ndcHeight; 
    return BoundingRect{ left, right, top, bottom }; 
}

const BorderRadius& Rectangle::GetRadius() const {
    return radius; 
}

BorderRadius Rectangle::GetNormalizedRadius() const {
    float ndcWidth = width * 2.0f;
    float ndcHeight = height * 2.0f;
    float minorAxis = std::min(ndcWidth / 2.0f, ndcHeight / 2.0f); 
    float radiusTopLeft = std::min(std::max(radius.topLeft, 0.0f), minorAxis);
    float radiusTopRight = std::min(std::max(radius.topRight, 0.0f), minorAxis);
    float radiusBottomLeft = std::min(std::max(radius.bottomLeft, 0.0f), minorAxis);
    float radiusBottomRight = std::min(std::max(radius.bottomRight, 0.0f), minorAxis);
    return BorderRadius{ radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight };
}