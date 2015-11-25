#include "Unite.h"

namespace Game {

	Unite::Unite(bool col, const Position& position, int id, int value, std::string name) : Piece(col, id, value, name, position) {}

	void Unite::move(const Position& newPosition) {
		this->position = newPosition;
	}

	std::vector<Position> Unite::moves(const Board& board) const {
		std::vector<Position> possibleMoves = new std::vector<Position>();

		Position from = this->getPosition();
		// Scout case
		if(this->getValue()==SCOUT) {
			for(int i=1+from.x;i<10;i++) { // go right
				if(board.isCorrectMove(from, Position(i, from.y))) {
					possibleMoves.push_back(Position(i, from.y));
				}
				else {
					break;
				}
			}
			for(int i=from.x-1;i>=0;i--) { // go left
				if(board.isCorrectMove(from, Position(i, from.y))) {
					possibleMoves.push_back(Position(i, from.y));
				}
				else {
					break;
				}
			}
			for(int i=1+from.y;i<10;i++) { // go up
				if(board.isCorrectMove(from, Position(from.x, i))) {
					possibleMoves.push_back(Position(from.x, i));
				}
				else {
					break;
				}
			}
			for(int i=from.y-1;i>=0;i--) { // go down
				if(board.isCorrectMove(from, Position(from.x, i))) {
					possibleMoves.push_back(Position(from.x, i));
				}
				else {
					break;
				}
			}
		}
		else { // normal case
			Position toRight = Position(1+from.x, from.y);
			if(board.isCorrectMove(from, toRight)) {
				possibleMoves.push_back(toRight);
			}
			Position toLeft = Position(from.x-1, from.y);
			if(board.isCorrectMove(from, toLeft)) {
				possibleMoves.push_back(toLeft);
			}
			Position toUp = Position(from.x, 1+from.y);
			if(board.isCorrectMove(from, toUp)) {
				possibleMoves.push_back(toUp);
			}
			Position toDown = Position(from.x, from.y-1);
			if(board.isCorrectMove(from, toDown)) {
				possibleMoves.push_back(toDown);
			}
		}

		return possibleMoves;
	}

}
