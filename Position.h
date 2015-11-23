#ifndef POSITION.H
#define POSITION.H

namespace Game {
	// A position on the board.
	class Position {
		public:
			int x;
			int y;

			// Create new position at 0, 0.
			Position();

			// Create new position (x, y)
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
