#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

namespace Game {

	class Board {
		private:
			GameState state; // Gives the game status (someone turn, or end of game?)
			Piece* cases[10][10]; // Represents the field
		public:
			Board();
			~Board();
			GameState getState() const;
			Piece* getPiece(const Position& position) const; // Gets the piece which is currently on the position given
			bool isCaseFree(const Position& position) const; // Checks if a case is empty or not
			bool isCorrectMove(const Position& from, const Position& to) const; // Checks if the move is correct
			void putPiece(Piece* p, const Position& position); // Put a Piece in a specific position on the field
			void removePiece(const Position& position); // Removes a piece from the game
			bool battle(Unite* u, Piece* p); // Battle between Unit U and the enemy piece
			void movePiece(const Position& from, const Position& to); // Moves a piece from a position to another and handles battle results eventually

	};

}

#endif
