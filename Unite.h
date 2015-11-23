#ifndef UNITE_H
#define UNITE_H

namespace Game {

	class Unite : public Piece {
		public:
			Unite(bool color, const Position& position, int id, std::string name);
			void move(const Position& position);
			std::vector<Position> moves(const Board& board) const;
	};

}

#endif
