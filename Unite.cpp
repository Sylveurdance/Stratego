#include "Unite.h"

namespace Game {

	Unite::Unite(bool col, const Position& position, int id, std::string name) : Piece(col, position) {
		this->id = id;
		this->name = name;
	}

	void Unite::move(const Position& newPosition) {
		this->position = newPosition;
	}

	std::vector<Position> Unite::moves(const Board& board) const {
		std::vector<Position> possibleMoves = new std::vector<Position>();

		Position from = this->getPosition();
		// Eclaireur case
		if(this->getId()==2) {
			//TODO make a for loop
		}
		else { // normal case
			//TODO make a for loop
			Position to = Position(1+from.x, from.y);
			if(board.isCorrectMove(from, to)) {
				possibleMoves.push_back(to);
			}
		}

		return possibleMoves;
	}

}
