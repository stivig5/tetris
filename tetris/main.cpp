#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <string>
#include "SimpleRender.h"
#include "label.h"
#include "figure.h"
#include "GameBoard.h"
/*
        []          | score: 10
      [][][]        | lvl: 9
                    |   []
                    | [][][]
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

enum class Figure_type {
    i_shape = 0,
    j_shape,
    l_shape,
    o_shape,
    z_shape,
    t_shape,
    s_shape,

    count
};

GameEngine::Figure make_figure(const Figure_type type)
{
    using GameEngine::Figure;
    switch (type) {
    case Figure_type::i_shape:
        return Figure({ {0,0}, {1,0}, {2, 0}, {3, 0} });
    case Figure_type::j_shape:
        return Figure({ {0,0}, {1,0}, {2, 0}, {2, 1} });
    case Figure_type::l_shape:
        return Figure({ {0,0}, {1,0}, {2, 0}, {0, 1} });
    case Figure_type::o_shape:
        return Figure({ {0,0}, {1,0}, {0, 1}, {1, 1} });
    case Figure_type::z_shape:
        return Figure({ {0,0}, {1,0}, {1, 1}, {2, 1} });
    case Figure_type::t_shape:
        return Figure({ {1,0}, {0,1}, {1, 1}, {2, 1} });
    case Figure_type::s_shape:
        return Figure({ {0,1}, {1,1}, {1, 0}, {2, 0} });
    default:
        return Figure({});
    }
}

GameEngine::Figure make_rand_figure() {
    const int figureType = rand() % static_cast<int>(Figure_type::count);
    return make_figure(static_cast<Figure_type>(figureType));
}


class Tetris {
public:
    Tetris()
        : m_board(board_height, board_width)
        , m_score(0)
        , m_lvl(1)
        , m_currentFigure(make_rand_figure())
        , m_nextFigure(make_rand_figure())
    {
		
        m_currentFigure.set_to({ board_width / 2 - 1, 0 });
		m_nextFigure.set_to({ board_width * 2 + 2, 3});
    }


    void draw() {
        GameEngine::SimpleRender render;
        render.resize({ board_width * 2 + 15, board_height + 1});
        
        m_board.render(render);

        GameEngine::Label score({ board_width * 2 + 2, 0}, "score: " + std::to_string(m_score));
        score.render(render);
		GameEngine::Label level({ board_width * 2 + 2, 1}, "level: " + std::to_string(m_lvl));
        level.render(render);
        
        m_currentFigure.render(render);
        m_nextFigure.render(render);

        render.render();
    }

    bool has_collision()
    {
        return m_currentFigure.has_collision(m_board) && !m_currentFigure.inside({ 0,0 }, { board_width , board_height});
    }

    void update() {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            m_currentFigure.move(-1, 0);
            if (has_collision()) {
                m_currentFigure.move(1, 0);
            }
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            m_currentFigure.move(1, 0);
            if (has_collision()) {
                m_currentFigure.move(-1, 0);
            }
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            m_currentFigure.move(0, 1);
            if (has_collision()) {
                m_currentFigure.move(0, -1);
            }
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            m_currentFigure.rotate();
            if (!has_collision()) {
                //undorotate
            }
        }

		m_currentFigure.move(0, 1);
        if (has_collision()) {
            m_currentFigure.move(0, -1);
            m_board.merge_board_and_figure(m_currentFigure);

            m_currentFigure = m_nextFigure;
			m_currentFigure.set_to({ board_width / 2 - 1, 0 });
            m_nextFigure = make_rand_figure();
			m_nextFigure.set_to({ board_width * 2 + 2, 3 });
		}
    }
private:
    GameEngine::GameBoard m_board;
	GameEngine::Figure m_currentFigure;
	GameEngine::Figure m_nextFigure;
    size_t m_score;
    size_t m_lvl;
};


int main() {
	srand(time(NULL));

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