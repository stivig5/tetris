#pragma once
#include "point.h"
#include <string>

namespace GameEngine {
    class IRender;

    class Label
    {
    public:
        Label(const Point& point, const std::string str);

        void render(IRender& render);

    private:
        std::string m_str;
        Point m_point;
    };
}