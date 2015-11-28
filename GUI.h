#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Board.h"

namespace GUI {

	class GUI {

		private:
			Game::Board& board;
			sf::RenderWindow* window;
			sf::Font messageFont;
			sf::Text messageText;

			sf::View boxView;
			sf::View gameView;

			// Textures
			std::vector<sf::Texture*> piecesTexture;
			sf::Texture fieldT;
			sf::Texture piece_rougeT;
			sf::Texture piece_bleuT;
			// Sprites
			std::vector<sf::Sprite> piecesSprite;
			sf::Sprite field;
			sf::Sprite piece_rouge;
			sf::Sprite piece_bleu;

			Game::Position selection;
			bool selected;
			bool mousePressed;

			std::vector<Game::Position> highlights;

			void drawBoard();
			void drawPieces();
			void drawBox(bool color);
			void updateGame();
			void updateBox();
			void drawMessage();

		public:
			GUI(Game::Board& board);
			~GUI();
			bool isOpen() const;
			void update();
			void render();
	};
}

#endif
