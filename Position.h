#ifndef POSITION_H
#define POSITION_H

namespace Game {
	// A position on the board.
	class Position {
		public:
			int x;
			int y;

			// Create new position (x, y)
			Position();
			Position(int x, int y);

			// Check if position is within bounds.
			bool isValid() const;
	};

	// Overloaded == for Position.
	bool operator==(const Position& lhs, const Position& rhs);

	// Overloaded != for Position.
	bool operator!=(const Position& lhs, const Position& rhs);
}

#endif
