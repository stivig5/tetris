#include "figure.h"
#include "irender.h"
#include "GameBoard.h"
namespace GameEngine {
    Figure::Figure(const std::vector<Point>& body)
        : m_body(body)
        , m_pos({ 0, 0 }) {
    }

    bool Figure:: hit_test(const int x, const int y)
    {
        for (size_t i = 0; i < m_body.size(); i++)
        {
            if (m_body[i].x + m_pos.x == x && m_body[i].y + m_pos.y == y) {
                return true;
            }
        }
        return false;
    }

    bool Figure::inside(const Point tl, const Point br)
    {
        for (size_t i = 0; i < m_body.size(); i++)
        {
            const int x = m_body[i].x + m_pos.x;
            const int y = m_body[i].y + m_pos.y;
            if (x < tl.x || y < tl.y || x >= br.x || y >= br.y) {
                return false;
            }
        }
        return true;
    }

    void Figure::set_to(Point pos)
    {
        m_pos = pos;
    }

    void Figure::move(const int x, const int y) {
        m_pos.x += x;
        m_pos.y += y;
    }

    void Figure::rotate() {
        for (size_t i = 0; i < m_body.size(); i++) {
            int temp = m_body[i].x;
            m_body[i].x = -m_body[i].y;
            m_body[i].y = temp;
        }
    }

    void Figure::render(IRender& render) {
        for (const Point& point : m_body)
        {
            render.set_char('[', m_pos.add({ point.x * 2, point.y }));
            render.set_char(']', m_pos.add({point.x * 2 + 1, point.y}));
        }
    }

    bool Figure::has_collision(GameBoard& board)
    {
        for (const Point& point : m_body)
        {
            if (board.has(point.add(m_pos)))
            {
                return true;
            }
        }
        return false;
    }
}