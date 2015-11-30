#ifndef POSITION_H
#define POSITION_H

#include "constantes.h"

namespace Game {
	// A position on the board.
	class Position {
		public:
			int x;
			int y;

			Position();
			Position(int x, int y);


			bool isValid() const;
			bool isStartValid(bool color) const;
	};


	bool operator==(const Position& lhs, const Position& rhs);
	bool operator!=(const Position& lhs, const Position& rhs);
}

#endif
