#pragma once
#include <vector>
#include <string>
#include "irender.h"

namespace GameEngine 
{
	class SimpleRender : public IRender 
	{
	public:
		void set_char(const char ch, const Point& point) override;

		void clear() override;
		void render() override;
		void resize(const Size& size) override;
	private:
		std::vector<std::string> m_buffer;
	};
}


