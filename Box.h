#ifndef BOX_H
#define BOX_H

#include "Piece.h"

namespace Game {

	class Box {
		private:
			bool color;
			std::vector<Piece*>* pieces;
		public:
			Box(bool color);
			~Box();
			void putInBox(Piece* p); // Put a defeated piece into the box
			Piece* takeOutOfBox(int id); // Put a piece in the box on the field
			std::vector<Piece*>* getBox();
	};

}



#endif
