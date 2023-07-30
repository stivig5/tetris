#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

/*
        []          | score: 10
      [][][]        | lvl: 9
                    |
                    |
                    |
[][][][][][][][][][]|
--------------------|
*/

const int board_width = 10;
const int board_height = 30;

struct Point {
    int x;
    int y;
};

class Figure {
public:
    Figure() 
        : m_body({ {1,0}, {0,1}, {1, 1}, {2, 1} })
        , m_pos({ board_width / 2 - 1, 0}) {
    }

    bool hit_test(const int x, const int y)
    {
        for (size_t i = 0; i < m_body.size(); i++)
        {
            if (m_body[i].x + m_pos.x == x && m_body[i].y + m_pos.y == y) {
                return true;
            }
        }
        return false;
    }

    bool inside(const Point tl, const Point br)
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

    void move(const int x, const int y) {
        m_pos.x += x;
        m_pos.y += y;
    }
private:
    std::vector<Point> m_body;
    Point m_pos;
};

class Tetris {
public:
    Tetris() 
        : m_board(board_height, std::vector<bool>(board_width, false))
        , m_score(0)
        , m_lvl(1) {
    }

    void draw() {
        for (size_t i = 0; i < m_board.size(); i++)
        {
            for (size_t j = 0; j < m_board[i].size(); j++)
            {
                if (m_board[i][j] || m_currentFigure.hit_test(j, i)) {
                    std::cout << "[]";
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << '|';
            if (i == 0) {
                std::cout << "score: " << m_score;
            }
            else if (i == 1) {
                std::cout << "level: " << m_lvl;
            }
            std::cout << '\n';
        }
		for (size_t j = 0; j < m_board[0].size(); j++)
        {
			std::cout << "--";
        }
        std::cout << '|';
    }

    bool has_collision()
    {
        for (size_t i = 0; i < m_board.size(); i++)
        {
            for (size_t j = 0; j < m_board[i].size(); j++)
            {
                if (m_currentFigure.hit_test(j, i) && m_board[i][j]) {
                    return true;
                }
            }
        }
        return !m_currentFigure.inside({ 0,0 }, { board_width , board_height});
    }
    
    void merge_board_and_figur()
    {
        for (size_t i = 0; i < m_board.size(); i++)
        {
            for (size_t j = 0; j < m_board[i].size(); j++)
            {
                if (m_currentFigure.hit_test(j, i)) {
                    m_board[i][j] = true;
                }
            }
        }
    }

    void update() {
        m_currentFigure.move(0, 1);
        if(has_collision())
        {
			m_currentFigure.move(0, -1);
			merge_board_and_figur();

            m_currentFigure = Figure();
        }
    }
private:
    std::vector<std::vector<bool>> m_board;
    Figure m_currentFigure;
    size_t m_score;
    size_t m_lvl;
};


int main() {
    Tetris tetris;
    while(true)
    {

        system("cls");
        tetris.draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
        tetris.update();
    }
	return 0;
}