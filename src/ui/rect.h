#pragma once

#include <vector>

#include "math.h"
#include "ui/ui_element.h"

struct BorderRadius {
    float topLeft, topRight, bottomLeft, bottomRight;

    BorderRadius(float radius) : topLeft(radius), topRight(radius), bottomLeft(radius), bottomRight(radius) {}
    BorderRadius(float topLeft, float topRight, float bottomLeft, float bottomRight) : 
        topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {}
};

struct BoundingRect {
    float left, right, top, bottom; 
};

class Rectangle : public UIElement {

public:
    Rectangle(); 
    Rectangle(float x, float y, float width, float height); 

    Vec2<float> GetCenter() const;
    BoundingRect GetBoundingRect() const;
    const BorderRadius& GetRadius() const;
    BorderRadius GetNormalizedRadius() const; 

    virtual void DrawElement() override = 0;

private:
    float x, y, width, height;
    BorderRadius radius{ 0.1f };

};