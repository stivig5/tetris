#pragma once
#include "point.h"
#include "size.h"
namespace GameEngine {
	class IRender {
	public:
		virtual ~IRender() = default;
		virtual void set_char(const char ch, const Point& point) = 0;

		virtual void clear() = 0;
		virtual void render() = 0;
		virtual void resize(const Size& size) = 0;
	};
}
