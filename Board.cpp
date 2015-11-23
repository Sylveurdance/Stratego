#include "Board.h"

namespace Game {

	Board::Board() {
		this->state = GameState::REDPLAYS; // Reds begin
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				this->cases[j][i]=NULL;
			}
		}

	}

	Board::~Board() {
		for (int i=0;i<10;i++){
			for (int j=0;j<10;j++){
				delete this->cases[j][i];
			}
		}
		delete[] this->cases;
	}

	GameState Board::getState() const {
		return state;
	}

	Piece* Board::getPiece(const Position& position) const {
		return this->cases[position.x][position.y];
	}

	bool Board::isCaseFree(const Position& position) const {
		if(getPiece(position)==NULL) {
			return true;
		}
		return false;
	}

	bool Board::isCorrectMove(const Position& from, const Position& to) const {
		if(!to.isValid()) {
			return false; // Checks if the position is not forbidden
		}
		if(isCaseFree(to)) {
			return true; // Free case is always valid (if not forbidden)
		}
		else {
			if(getPiece(from)->getColor() != getPiece(to)->getColor()) {
				return true;
			}
			return false; // Case located by one of our own piece
		}
	}

	void Board::putPiece(Piece* p, const Position& position) {
		this->cases[position.x][position.y] = p;
		dynamic_cast<Unite*>(p)->move(position);
	}

	void Board::removePiece(const Position& position) {
		delete this->getPiece(position);
		this->cases[position.x][position.y] = NULL;
	}

	// Unit U attacks Piece P
	bool Board::battle(Unite* u, Piece* p) {
		bool win;
		if(p->getId()==0) { // Flag
			win = true;
			if(this->getState() == GameState::BLUEPLAYS) {
				this->state = GameState::BLUEWIN;
			}
			else if(this->getState() == GameState::REDPLAYS) {
				this->state = GameState::REDWIN;
			}
		}
		else if(p->getId()==11) { // Bomb
			if(u->getId()==3) {
				win = true;
			}
			else {
				win = false;
			}
		}
		else { // Another Unit
			if((u->getId()==1) && (p->getId()==10)) { // the spy attacks the marechal
				win = true;
			}
			else if(u->getId() > p->getId()) {
				win = true;
			}
			else if(u->getId() < p->getId()) {
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
				if(battle(dynamic_cast<Unite*>(this->getPiece(from)),this->getPiece(to))) {
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
			if(this->getState() == GameState::BLUEPLAYS) {
				this->state = GameState::REDPLAYS;
			}
			else if(this->getState() == GameState::REDPLAYS) {
				this->state = GameState::BLUEPLAYS;
			}
		}
	}

}
