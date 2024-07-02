#pragma once

#include <vector>

#include "ref.h"
#include "style.h"

class UIElement {

public:
    virtual void DrawElement() = 0; 

private:
    std::vector<Ref<UIElement>> m_Children{}; 
    Style m_Style{
        .backgroundColor = Vec4<float>{ 0.0f, 0.0f, 0.0f, 0.0f },
        .textColor = Vec4<float>{ 0.0f, 0.0f, 0.0f, 1.0f }
    }; 

};