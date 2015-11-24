#include "Piece.h"

namespace Game {

	Piece::Piece(bool color, int id, const Position& position) {
		this->color = color;
		this->position = position;
		this->id = id;
		this->value = -1;
		this->name = "";
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

}
