#pragma once

#include <vector>

#include "ref.h"
#include "style.h"

#include "aabb.h"

namespace UI {
    
    class UIElement {

    public:
        const std::vector<Ref<UIElement>>& GetChildren() const {
            return m_Children; 
        }

        void AddChild(Ref<UIElement> child, bool doCascade = true) {
            if (doCascade) child->SetStyle(CascadeStyles(child->GetStyle(), m_Style));
            m_Children.emplace_back(child); 
        }

        bool RemoveChild(Ref<UIElement> child) {
            // linear search
            int index = -1; 
            for (int i = 0; i < m_Children.size(); i++) {
                if (m_Children[i] == child) {
                    index = i; 
                    break; 
                }
            }

            if (index > -1) {
                m_Children.erase(m_Children.begin() + index, m_Children.begin() + index + 1); 
                return true;
            } 

            return false; 
        }

        void ClearChildren() {
            m_Children.clear(); 
        }

        const Style& GetStyle() const { return m_Style; }
        const void SetStyle(Style style) { m_Style = style; }

        const AABB2D& GetBoundingBox() const { return m_BoundingBox; }
        void SetBoundingBox(AABB2D bbox) { m_BoundingBox = bbox; }

        /* Virtual Methods */

        virtual void DrawElement() = 0;

    protected:
        AABB2D m_BoundingBox{}; 
        std::vector<Ref<UIElement>> m_Children{}; 
        Style m_Style{
            .backgroundColor = optional<Color>({ 0.0f, 0.0f, 0.0f, 0.0f }),
            .textColor = optional<Color>({ 0.0f, 0.0f, 0.0f, 1.0f })
        }; 

    };

}
