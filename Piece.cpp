#include "Piece.h"

namespace Game {

	Piece::Piece(bool color, int id, int value, std::string name) {
		this->color = color;
		this->id = id;
		this->value = value;
		this->name = name;
		this->position = Position(0,0);
	}

	Piece::Piece(bool color, int id, int value, std::string name, const Position& position) {
		this->color = color;
		this->position = position;
		this->id = id;
		this->value = value;
		this->name = name;
	}

	Piece::~Piece() {}

	// Gets the piece color
	bool Piece::getColor() const {
		return this->color;
	}

	// Gets the piece ID
	int Piece::getId() const {
		return this->id;
	}

	// Gets the piece value
	int Piece::getValue() const {
		return this->value;
	}

	// Gets the piece name
	std::string Piece::getName() const {
		return this->name;
	}

	// Gets the current piece position on the field
	Position Piece::getPosition() const {
			return this->position;
	}

	// Checks if the piece is a Unit or not
	bool Piece::isUnit() const {
		if((this->value != FLAG) && (this->value!=BOMB)) {
			return true;
		}
		return false;
	}

	// Moves a piece (Unit) to another position
	void Piece::move(const Position& newPosition) {
		if(this->isUnit()) {
			this->position = newPosition;
		}
	}

}
