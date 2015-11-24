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
		if(p->getValue()==FLAG) {
			win = true;
			if(this->getState() == GameState::BLUEPLAYS) {
				this->state = GameState::BLUEWIN;
			}
			else if(this->getState() == GameState::REDPLAYS) {
				this->state = GameState::REDWIN;
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
			if((u->getValue()==SPY) && (p->getValue()==MARSCHAL)) { // the spy attacks the marschal
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

	bool Board::canPlayerPlay() const {

		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				Piece* p = this->getPiece(Position(i,j));
				if((p->getValue()!=FLAG) && (p->getValue()!=BOMB)) { // Unit
					Unite* u = dynamic_cast<Unite*>(p);
					if((u->getColor()) && (this->getState() == GameState::REDPLAYS)) { // Reds turn and Red unit
						if(!u->moves(*this).empty()) {
							return true;
						}
					}
					else if((!u->getColor()) && (this->getState() == GameState::BLUEPLAYS)) { // Blues turn and blue unit
						if(!u->moves(*this).empty()) {
							return true;
						}
					}
				}
			}
		}

		if(this->getState() == GameState::REDPLAYS) {
			this->state = GameState::BLUEWIN; // Reds can't make a moove => Blues win
		}
		else if(this->getState() == GameState::BLUEPLAYS) {
			this->state = GameState::REDWIN; // Blues can't make a moove => Reds win
		}

		return false;
	}

}
