#ifndef BOARD_H
#define BOARD_H

#include "Box.h"

namespace Game {

	class Board {
		private:
			GameState state; 		// Gives the game status (someone turn, or end of game?)
			Piece* cases[10][10]; 	// Represents the field
			Box* redBox;
			Box* blueBox;
		public:
			Board();
			~Board();
			GameState getState() const;
			Piece* getPiece(const Position& position) const;
			bool isCaseFree(const Position& position) const;
			bool isCorrectRelativeMove(const Position& from, const Position& to) const;
			bool isCorrectMove(const Position& from, const Position& to) const;
			void putPiece(Piece* p, const Position& position, bool outBox=false);
			void removePiece(const Position& position, bool inBox=false);
			bool battle(Piece* u, Piece* p);
			void movePiece(const Position& from, const Position& to);
			std::vector<Position> moves(const Position& position) const;
			bool canPlayerPlay();
			bool isInMoveset(std::vector<Position> possibleMoves, const Position& position) const;
			void fillBoard(bool color);

	};

}

#endif
