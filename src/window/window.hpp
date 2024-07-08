#pragma once

#include "vml/vml.hpp"

class WindowWrapper 
{
    public:
        void SetFramebufferSize(VML::Vec2i framebufferSize) { m_FramebufferSize = framebufferSize; }
        const VML::Vec2i& GetFramebufferSize() const { return m_FramebufferSize; }

        virtual bool IsRunning() = 0; 
        virtual void OnFrame() = 0; 

        bool m_FramebufferSizeDirty = false; 

    protected:
        VML::Vec2i m_FramebufferSize{}; 

};