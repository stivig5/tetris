#pragma once
namespace GameEngine {
	struct Point {
		int x;
		int y;

		Point add(const Point& other) const {
			return { other.x + x, other.y + y };
		}
	};
}
