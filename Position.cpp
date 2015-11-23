#include "Position.h"

namespace Game {
	Position::Position() : Position(0, 0) {}

	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool Position::isValid() const {
		bool result = (x >= 0 && x < 10 && y >= 0 && y < 10);
		if (!result) {
			return false;
		}
		else {
			result = ((y == 4 || y == 5) && (x!=2 && x!=3 && x!=6 && x!=7));
		}
		return result;
	}

	bool operator==(const Position& lhs, const Position& rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	bool operator!=(const Position& lhs, const Position& rhs) {
		return !(lhs == rhs);
	}
}
