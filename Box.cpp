#include "Box.h"

namespace Game {

	Box::Box(bool color) {
		this->color = color;
		this->pieces = new std::vector<Piece*>();
		int idPiece = 1;
		for(int i=0;i<QTE_FLAG;i++) {
			this->pieces->push_back(new Piece(color, idPiece, FLAG, "Flag"));
			idPiece++;
		}
		for(int i=0;i<QTE_BOMB;i++) {
			this->pieces->push_back(new Piece(color, idPiece, BOMB, "Bomb"));
			idPiece++;
		}
		for(int i=0;i<QTE_SPY;i++) {
			this->pieces->push_back(new Piece(color, idPiece, SPY, "Spy"));
			idPiece++;
		}
		for(int i=0;i<QTE_SCOUT;i++) {
			this->pieces->push_back(new Piece(color, idPiece, SCOUT, "Scout"));
			idPiece++;
		}
		for(int i=0;i<QTE_MINER;i++) {
			this->pieces->push_back(new Piece(color, idPiece, MINER, "Miner"));
			idPiece++;
		}
		for(int i=0;i<QTE_SERGEANT;i++) {
			this->pieces->push_back(new Piece(color, idPiece, SERGEANT, "Sergeant"));
			idPiece++;
		}
		for(int i=0;i<QTE_LIEUTENANT;i++) {
			this->pieces->push_back(new Piece(color, idPiece, LIEUTENANT, "Lieutenant"));
			idPiece++;
		}
		for(int i=0;i<QTE_CAPTAIN;i++) {
			this->pieces->push_back(new Piece(color, idPiece, CAPTAIN, "Captain"));
			idPiece++;
		}
		for(int i=0;i<QTE_MAJOR;i++) {
			this->pieces->push_back(new Piece(color, idPiece, MAJOR, "Major"));
			idPiece++;
		}
		for(int i=0;i<QTE_COLONEL;i++) {
			this->pieces->push_back(new Piece(color, idPiece, COLONEL, "Colonel"));
			idPiece++;
		}
		for(int i=0;i<QTE_GENERAL;i++) {
			this->pieces->push_back(new Piece(color, idPiece, GENERAL, "General"));
			idPiece++;
		}
		for(int i=0;i<QTE_MARSHAL;i++) {
			this->pieces->push_back(new Piece(color, idPiece, MARSHAL, "Marshal"));
			idPiece++;
		}

		// Set positions for the box
		int x = 0;
		int y = 0;
		if(!color) y = 9;
		for (int i=0;i<this->pieces->size();i++) {
			this->pieces->at(i)->setPosition(Position(x,y));
			// simulation of for x,y...
			x++;
			if(x==10) {
				x=0;
				if(!color) y--;
				else y++;
			}
		}
	}

	Box::~Box() {
		for (int i=0;i<this->pieces->size();i++) {
			delete this->pieces->at(i);
		}
		this->pieces->clear();
		delete this->pieces;
	}

	void Box::putInBox(Piece* p) {
		this->pieces->push_back(p);
	}

	Piece* Box::takeOutOfBox(int id) {
		if(!this->pieces->empty()) {
			for (int i=0;i<this->pieces->size();i++) {
				if(this->pieces->at(i)->getId() == id) {
					Piece* p = this->pieces->at(i);
					this->pieces->erase(this->pieces->begin()+i);
					return p;
				}
			}
		}
		return NULL;
	}

	std::vector<Piece*>* Box::getBox() {
		return this->pieces;
	}

}
