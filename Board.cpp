#include "Board.h"

namespace Game {

	Board::Board() {
		this->state = REDPLAYS; // Reds begin
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				this->cases[j][i]=NULL;
			}
		}
		this->redBox = new Box(RED);
		this->blueBox = new Box(BLUE);
	}

	Board::~Board() {
		for (int i=0;i<10;i++){
			for (int j=0;j<10;j++){
				delete this->cases[j][i];
			}
		}
		delete this->redBox;
		delete this->blueBox;
	}

	GameState Board::getState() const {
		return state;
	}

	Piece* Board::getPiece(const Position& position) const {
		return this->cases[position.x][position.y];
	}

	bool Board::isCaseFree(const Position& position) const {
		if(!this->getPiece(position)) {
			return true;
		}
		return false;
	}

	bool Board::isCorrectMove(const Position& from, const Position& to) const {
		if(!this->getPiece(from)) {
			return false; // error case
		}
		if((!from.isValid()) || (!to.isValid())) {
			return false; // Checks if the positions are not forbidden
		}
		if(!this->getPiece(from)->isUnit()) {
			return false; // If the piece in from position is not a unit, the move is not correct
		}
		if(this->isCaseFree(to)) {
			return true; // Free case is always valid (if not forbidden)
		}
		else {
			if(this->getPiece(from)->getColor() != this->getPiece(to)->getColor()) {
				return true;
			}
			return false; // Case located by one of our own piece
		}
	}

	void Board::putPiece(Piece* p, const Position& position) {
		if(!p) { return; } // protect from errors
		if(p->getColor()) { // Red
			this->redBox->takeOutOfBox(p->getId());
		}
		else { // Blue
			this->blueBox->takeOutOfBox(p->getId());
		}

		this->cases[position.x][position.y] = p;
		p->move(position);
	}

	void Board::removePiece(const Position& position) {
		if(this->getPiece(position)) { return; } // protect from errors
		if(this->getPiece(position)->getColor()) { // Red piece
			this->redBox->putInBox(this->getPiece(position));
		}
		else { // Blue piece
			this->blueBox->putInBox(this->getPiece(position));
		}

		delete this->getPiece(position);
		this->cases[position.x][position.y] = NULL;
	}

	// Unit U attacks Piece P
	bool Board::battle(Piece* u, Piece* p) {
		if((!p) || (!p) || (!u->isUnit())) {
			return NULL; // Pieces NULL value or U not a Unit...
		}

		bool win;
		if(p->getValue()==FLAG) {
			win = true;
			if(this->getState() == BLUEPLAYS) {
				this->state = BLUEWIN;
			}
			else if(this->getState() == REDPLAYS) {
				this->state = REDWIN;
			}
		}
		else if(p->getValue()==BOMB) {
			if(u->getValue()==MINER) {
				win = true;
			}
			else {
				win = false;
			}
		}
		else { // Another Unit
			if((u->getValue()==SPY) && (p->getValue()==MARSHAL)) { // the spy attacks the marshal
				win = true;
			}
			else if(u->getValue() > p->getValue()) {
				win = true;
			}
			else if(u->getValue() < p->getValue()) {
				win = false;
			}
			else { // draw (both units are destroyed)
				win = false;
				this->removePiece(p->getPosition());
			}
		}
		return win;
	}

	void Board::movePiece(const Position& from, const Position& to) {
		if(isCorrectMove(from, to)) {
			if(isCaseFree(to)) {
				Piece* tmp = this->getPiece(from);
				this->removePiece(from);
				this->putPiece(tmp, to);
			}
			else { // battle
				bool battleRes = battle(this->getPiece(from),this->getPiece(to));
				if(battleRes) {
					Piece* tmp = this->getPiece(from);
					this->removePiece(from);
					this->removePiece(to);
					this->putPiece(tmp, to);
				}
				else {
					this->removePiece(from);
				}
			}
			// Change turn
			if(this->getState() == BLUEPLAYS) {
				this->state = REDPLAYS;
			}
			else if(this->getState() == REDPLAYS) {
				this->state = BLUEPLAYS;
			}
		}
	}

	std::vector<Position> Board::moves(const Position& position) const {
		std::vector<Position> possibleMoves;

		Piece* p = this->getPiece(position);
		if ((!p) || (!p->isUnit())) {
			return possibleMoves; // case empty or not a Unit (cannot move)
		}

		Position from = p->getPosition();

		// Scout case
		if(p->getValue()==SCOUT) {
			for(int i=1+from.x;i<10;i++) { // go right
				if(this->isCorrectMove(from, Position(i, from.y))) {
					possibleMoves.push_back(Position(i, from.y));
				}
				else {
					break;
				}
			}
			for(int i=from.x-1;i>=0;i--) { // go left
				if(this->isCorrectMove(from, Position(i, from.y))) {
					possibleMoves.push_back(Position(i, from.y));
				}
				else {
					break;
				}
			}
			for(int i=1+from.y;i<10;i++) { // go up
				if(this->isCorrectMove(from, Position(from.x, i))) {
					possibleMoves.push_back(Position(from.x, i));
				}
				else {
					break;
				}
			}
			for(int i=from.y-1;i>=0;i--) { // go down
				if(this->isCorrectMove(from, Position(from.x, i))) {
					possibleMoves.push_back(Position(from.x, i));
				}
				else {
					break;
				}
			}
		}
		else { // normal case
			Position toRight = Position(1+from.x, from.y);
			if(this->isCorrectMove(from, toRight)) {
				possibleMoves.push_back(toRight);
			}
			Position toLeft = Position(from.x-1, from.y);
			if(this->isCorrectMove(from, toLeft)) {
				possibleMoves.push_back(toLeft);
			}
			Position toUp = Position(from.x, 1+from.y);
			if(this->isCorrectMove(from, toUp)) {
				possibleMoves.push_back(toUp);
			}
			Position toDown = Position(from.x, from.y-1);
			if(this->isCorrectMove(from, toDown)) {
				possibleMoves.push_back(toDown);
			}
		}

		return possibleMoves;
	}

	bool Board::canPlayerPlay() {

		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				Piece* p = this->getPiece(Position(i,j));
				if(!this->isCaseFree(Position(i,j))) { // prevent null values
					if(p->isUnit()) { // Unit
						if((p->getColor()) && (this->getState() == REDPLAYS)) { // Reds turn and Red unit
							if(!this->moves(Position(i,j)).empty()) {
								return true;
							}
						}
						else if((!p->getColor()) && (this->getState() == BLUEPLAYS)) { // Blues turn and blue unit
							if(!this->moves(Position(i,j)).empty()) {
								return true;
							}
						}
					}
				}
			}
		}

		if(this->getState() == REDPLAYS) {
			this->state = BLUEWIN; // Reds can't make a moove => Blues win
		}
		else if(this->getState() == BLUEPLAYS) {
			this->state = REDWIN; // Blues can't make a moove => Reds win
		}

		return false;
	}

	void Board::fillBoard(bool color) {

		int yy;
		for(int y=0;y<5;y++){
			if(!color) { yy = 9-y; }
			for(int x=0;x<10;x++){
				if(!color) {
					if((!this->blueBox->getBox()->empty()) && (this->blueBox->getBox()->size()>0)){
						this->putPiece(this->blueBox->getBox()->at(0), Position(x,yy));
					}
				}
				else {
					if((!this->redBox->getBox()->empty()) && (this->redBox->getBox()->size()>0)){
						this->putPiece(this->redBox->getBox()->at(0), Position(x,y));
					}
				}
			}
		}
	}

}
