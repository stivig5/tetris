#pragma once
#include <vector>
#include "point.h"

namespace GameEngine {
	class IRender;
	class Figure;
	class GameBoard
	{
	public:
		GameBoard(const size_t height, const size_t width);

		void render(IRender& render);

		bool has(const Point& point);

		void clear_full_rows();

		void merge_board_and_figure(Figure& m_currentFigure);
	private:
		std::vector<std::vector<bool>> m_board;
	};
}
