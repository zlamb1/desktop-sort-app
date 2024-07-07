#pragma once

#include "frame.hpp"

namespace UI 
{

    class UIRenderer 
    {
        public:
            virtual void DrawElements() = 0; 
            virtual void FlowLayout(const Vec2i& framebufferSize) = 0; 

        private:
            Frame m_Root{};
    };

}