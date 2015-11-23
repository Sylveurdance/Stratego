#ifndef PIECE_H
#define PIECE_H

#include <constantes.h>
#include <vector>

namespace Game {
	class Piece {

		private:
			bool color;

		protected:
			int id;
			std::string name;
			Position position;

		public:
			Piece(bool color, const Position& position);
			virtual ~Piece();
			bool getColor() const;
			int getId() const;
			std::string getName() const;
			Position getPosition() const;

	};
}

#endif
