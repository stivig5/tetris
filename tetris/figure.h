#pragma once
#include <vector>
#include "point.h"

namespace GameEngine {
    class IRender;
    class GameBoard;

    class Figure {
    public:
        Figure(const std::vector<Point>& body);

        bool hit_test(const int x, const int y);

        bool inside(const Point tl, const Point br);

        void set_to(Point pos);

        void move(const int x, const int y);

        void rotate();

        void render(IRender& render);

        bool has_collision(GameBoard& board);

    private:
        std::vector<Point> m_body;
        Point m_pos;
    };
}