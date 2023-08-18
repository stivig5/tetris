#include "SimpleRender.h"
#include <iostream>
namespace GameEngine {
	void SimpleRender::set_char(const char ch, const Point& point)
	{
		if (point.y >= 0 && point.y < m_buffer.size() && point.x >= 0 && point.x < m_buffer[point.y].size()) {
			m_buffer[point.y][point.x] = ch;
		}
	}

	void SimpleRender::clear()
	{
		for (std::string& line : m_buffer) {
			for (char& ch : line) {
				ch = ' ';
			}
		}
	}

	void SimpleRender::render()
	{
		for (std::string& const line : m_buffer) {
			std::cout << line;
			std::cout << '\n';
		}
	}

	void SimpleRender::resize(const Size& size)
	{
		m_buffer.resize(size.height);
		for (std::string& line : m_buffer)
		{
			line.resize(size.width, ' ');
		}
	}
}

