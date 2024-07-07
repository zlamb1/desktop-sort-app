#pragma once

#include "math/math.hpp"

class WindowWrapper 
{
    public:
        void SetFramebufferSize(Vec2i framebufferSize) { m_FramebufferSize = framebufferSize; }
        const Vec2i& GetFramebufferSize() const { return m_FramebufferSize; }

        virtual bool IsRunning() = 0; 
        virtual void OnFrame() = 0; 

        bool m_FramebufferSizeDirty = false; 

    protected:
        Vec2i m_FramebufferSize{}; 

};