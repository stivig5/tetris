#include "label.h"
#include "irender.h"

namespace GameEngine {
    Label::Label(const Point& point, const std::string str) : m_str(str), m_point(point) {}

    void Label::render(IRender& render)
    {
        for (int i = 0; i < m_str.size(); i++)
        {
            render.set_char(m_str[i], { m_point.x + i, m_point.y });
        }
    }
}