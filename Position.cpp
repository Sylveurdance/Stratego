#include "Position.h"

namespace Game {

	Position::Position() {
		this->x = 0;
		this->y = 0;
	}

	// Creates new position (x, y)
	Position::Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	// Checks if position is within bounds
	bool Position::isValid() const {

		if (!(x >= 0 && x < 10 && y >= 0 && y < 10)) { // Checks if Position in the zone
			return false;
		}
		if(((y==4) || (y==5)) && ((x==2) || (x==3) || (x==6) || (x==7))) { // Checks if the position is not forbidden
			return false;
		}
		return true;
	}

	// Checks if the position is correct to start
	bool Position::isStartValid(bool color) const {

		if(!this->isValid()) {
			return false;
		}
		if((y>3) && (color)) {
			return false;
		}
		if((y<6) && (!color)) {
			return false;
		}

		return true;
	}

	// Overloaded == for Position
	bool operator==(const Position& lhs, const Position& rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	// Overloaded != for Position
	bool operator!=(const Position& lhs, const Position& rhs) {
		return !(lhs == rhs);
	}
}
