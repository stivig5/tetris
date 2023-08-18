#include "GameBoard.h"
#include "irender.h"
#include "figure.h"
namespace GameEngine {
	GameBoard::GameBoard(const size_t height, const size_t width) 
		: m_board(height, std::vector<bool>(width, false)) {

	}

	void GameBoard::render(IRender& render)
	{
		for (size_t i = 0; i < m_board.size(); i++)
		{
			for (size_t j = 0; j < m_board[i].size(); j++)
			{
				if (m_board[i][j]) {
					render.set_char('[', { static_cast<int>(j * 2), static_cast<int>(i) });
					render.set_char(']', { static_cast<int>(j * 2 + 1), static_cast<int>(i) });
				}
			}
		}

		for (size_t i = 0; i < m_board.size() + 1; i++)
		{
			render.set_char('|', { static_cast<int>(m_board[0].size() * 2) , static_cast<int>(i) });
		}

		for (size_t i = 0; i < m_board[0].size() * 2; i++)
		{
			render.set_char('-', { static_cast<int>(i), static_cast<int>(m_board.size()) });
		}

	}

	bool GameBoard::has(const Point& point)
	{
		return point.y >= 0 && point.y < m_board.size()
			&& point.x >= 0 && point.x < m_board[point.y].size()
			&& m_board[point.y][point.x];
	}

	void GameBoard::clear_full_rows() {
		for (int i = m_board.size() - 1; i >= 0; i--) {
			bool is_full_row = true;
			for (int j = 0; j < m_board[i].size(); j++) {
				if (!m_board[i][j]) {
					is_full_row = false;
					break;
				}
			}
			if (is_full_row) {
				m_board.erase(m_board.begin() + i);
				m_board.insert(m_board.begin(), std::vector<bool>(m_board.size(), false));
			}
		}
	}

	void GameBoard::merge_board_and_figure(Figure& m_currentFigure)
	{
		for (int i = 0; i < m_board.size(); i++)
		{
			for (int j = 0; j < m_board[i].size(); j++)
			{
				if (m_currentFigure.hit_test(j, i)) {
					m_board[i][j] = true;
				}
			}
		}
		clear_full_rows();
	}
}