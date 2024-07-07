#pragma once

#include <vector>

#include "ui/ui_element.hpp"

namespace UI 
{
    
    struct Radius 
    {
        float topLeft, topRight, bottomLeft, bottomRight;

        Radius(float radius) : topLeft(radius), topRight(radius), bottomLeft(radius), bottomRight(radius) {}
        Radius(float topLeft, float topRight, float bottomLeft, float bottomRight) : 
            topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {}
    };

    class Rectangle : public UIElement 
    {

    public:
        Rectangle(); 

        const Radius& GetRadius() const;

        virtual void DrawElement() = 0;

    private:
        Radius radius{ 0.1f };

    };

}