#pragma once

#include <vector>

template<typename T> 
struct Vec2 {
    T x, y; 
};

template<typename T>
struct Vec3 {
    T x, y, z; 
};

template<typename T>
struct Vec4 {
    T x, y, z, w;
};

struct BorderRadius {
    float topLeft, topRight, bottomLeft, bottomRight;

    BorderRadius(float radius) : topLeft(radius), topRight(radius), bottomLeft(radius), bottomRight(radius) {}
    BorderRadius(float topLeft, float topRight, float bottomLeft, float bottomRight) : 
        topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {}
};

struct BoundingRect {
    float left, right, top, bottom; 
};

class Rectangle {

public:
    Rectangle(); 
    Rectangle(float x, float y, float width, float height); 

    Vec2<float> GetCenter() const;
    BoundingRect GetBoundingRect() const;
    const BorderRadius& GetRadius() const;
    BorderRadius GetNormalizedRadius() const; 

private:
    float x, y, width, height;
    BorderRadius radius{ 1.0f };

};