#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <Board.h>
#include <Piece.h>
#include <map>
#include <ctype.h>

namespace GUI {

	class GUI {

		private:
			int width, height;
			Game::Board& board;
			sf::RenderWindow* window;
			sf::Font messageFont;
			sf::Text messageText;

			std::vector<sf::Texture> piecesTexture;
			std::vector<sf::Sprite> piecesSprite;

			sf::Sprite field;
			sf::Sprite piece_rouge;
			sf::Sprite piece_bleu;

			Game::Position selection;
			bool selected;
			bool mousePressed;

			std::vector<Game::Position> highlights;						//Contains all the positions that are highlighted

			void drawBoard();											//Draws the board
			void drawPieces();											//Draws the pieces on top of the board.
			void updateGame();											//Updates the game
			void drawMessage();											//Draws a message (win, lose)
			void updateMessage();										//Updates the message (Does nothing right now)
			bool highlighted(const Game::Position& position);			//Returns whether a position is highlighted

		public:
			GUI(int width, int height, Game::Board& board);
			~GUI();
			bool isOpen() const;
			void update();
			void render();
	};
}

#endif