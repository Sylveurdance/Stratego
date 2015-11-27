#include "Position.h"

namespace Game {

	Position::Position() {
		this->x = 0;
		this->y = 0;
	}

	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool Position::isValid() const {

		if (!(x >= 0 && x < 10 && y >= 0 && y < 10)) { // Checks if Position in the zone
			return false;
		}
		else {
			if(((y==4) || (y==5)) && ((x==2) || (x==3) || (x==6) || (x==7))) { // Checks if the position is not forbidden
				return false;
			}
		}
		return true;
	}

	bool operator==(const Position& lhs, const Position& rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	bool operator!=(const Position& lhs, const Position& rhs) {
		return !(lhs == rhs);
	}
}
