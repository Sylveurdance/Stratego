#ifndef PIECE_H
#define PIECE_H

#include "Position.h"

namespace Game {
	class Piece {

		private:
			bool color;

		protected:
			int id;
			int value;
			std::string name;
			Position position;

		public:
			Piece(bool color, int id, int value, std::string name);
			Piece(bool color, int id, int value, std::string name, const Position& position);
			virtual ~Piece();
			bool getColor() const;
			int getId() const;
			int getValue() const;
			std::string getName() const;
			Position getPosition() const;
			bool isUnit() const;
			void move(const Position& position); // only for Units

	};
}

#endif
