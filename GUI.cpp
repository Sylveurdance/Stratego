#include "GUI.h"

using namespace sf;
using namespace Game;

namespace GUI {

	GUI::GUI(int width, int height, Board& board) : board(board) {
		this->width = width;
		this->height = height;
		this->board = board;
		this->selected = false;
		this->mousePressed = false;

		window = new RenderWindow(VideoMode(width, height), "Stratego Game");
		window->setVerticalSyncEnabled(true);

		// Text used to display messages (draw, win)
		messageFont.loadFromFile("polices/angelina.ttf");
		messageText.setFont(messageFont);
		messageText.setCharacterSize(height / 4);
		messageText.setColor(Color::White);

		// Field
		if(fieldT.loadFromFile("./img/plateau.png")) {
			field.setTexture(fieldT);
		}

		// Pieces Red and blues
		if(piece_rougeT.loadFromFile("./img/piece.png")) piece_rouge.setTexture(piece_rougeT);
		if(piece_bleuT.loadFromFile("./img/piece2.png")) piece_bleu.setTexture(piece_bleuT);

		// Pieces images
		for(int i=0;i<12;i++) {
			Texture tmpT;
			Sprite tmpSprite;
			std::stringstream sstm;
			std::string fileName;
			sstm << "./img/" << i << ".png";
			fileName = sstm.str();

			if(tmpT.loadFromFile(fileName)) {
				piecesTexture.push_back(tmpT);
				tmpSprite.setTexture(piecesTexture.at(i));
				piecesSprite.push_back(tmpSprite);
			}
			else {
				i--; // will retry ! (possibly infinite loop!!!!)
			}
		}
	}

	GUI::~GUI() {
		delete window;
	}

	bool GUI::isOpen() const {
		return window->isOpen();
	}

	void GUI::update() {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();
		}

		if ((board.getState() == REDPLAYS || board.getState() == BLUEPLAYS)) {
			updateGame();
		}
	}

	void GUI::updateGame(){
		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed) {
			Vector2i mousePos = Mouse::getPosition(*window);
			Position tempPos(mousePos.x * 10 / width, mousePos.y * 10 / height);
			tempPos.y = 9 - tempPos.y; // SFML reverse repere in Y
			Piece* tempPiece = board.getPiece(tempPos);
			if (selected) { // If we have already selected a piece, and click on the board again, the piece should move.
				Piece* selectedPiece = board.getPiece(selection);
				if(board.isCorrectMove(selection, tempPos)) {
					board.movePiece(selection, tempPos);
					selected = false;
				}
				else if (tempPiece) { // Prevent selecting of opponent pieces.
					if (!tempPiece->getColor() && (board.getState() == REDPLAYS))
						return;
					else if (tempPiece->getColor() && (board.getState() == BLUEPLAYS))
						return;
					selection = tempPos;
					selected = true;
					highlights = board.moves(tempPos);
				}
			}
			else if (tempPiece) { // If we haven't already selected a piece, then we should select it.
				if (!tempPiece->getColor() && (board.getState() == REDPLAYS))
					return;
				else if (tempPiece->getColor() && (board.getState() == BLUEPLAYS))
					return;
				selection = tempPos;
				selected = true;
				highlights = board.moves(tempPos);
			}
		}

		mousePressed = pressed;
	}

	void GUI::drawMessage(){
		messageText.setPosition(Vector2f(width/3.0f,height/3.0f));
		messageText.setCharacterSize(25);
		board.canPlayerPlay();
		if (board.getState() == REDWIN)
			messageText.setString("Red wins!");
		else if (board.getState() == BLUEWIN)
			messageText.setString("Blue wins!");
		window->draw(messageText);
	}

	void GUI::render() {
		window->clear();
		//drawMessage();
		if ((board.getState() == REDPLAYS || board.getState() == BLUEPLAYS)) {
			drawBoard();
			drawPieces();
		}
		window->display();
	}

	void GUI::drawBoard() {

		window->draw(field);

		RectangleShape square(Vector2f(width / 10.f, height / 10.f));
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				square.setPosition(x * width / 10.f, y * height / 10.f);

				if (selected && selection == Position(x, 9-y))
					square.setFillColor(Color::Yellow);
				else if (selected && highlighted(Position(x, 9-y)))
					square.setFillColor(Color::Green);

				window->draw(square);
			}
		}
	}

	void GUI::drawPieces() {
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				Piece* piece = board.getPiece(Position(x,9-y));
				if (piece) {
					piecesSprite.at(piece->getValue()).setPosition(Vector2f(x*width/10.f,(y-0.2f)*width/10.f));
					if(piece->getColor()) {
						piece_rouge.setPosition(Vector2f(x*width/10.f,(y-0.2f)*width/10.f));
						window->draw(piece_rouge);
					}
					else {
						piece_bleu.setPosition(Vector2f(x*width/10.f,(y-0.2f)*width/10.f));
						window->draw(piece_bleu);
					}

					window->draw(piecesSprite.at(piece->getValue()));
				}
			}
		}
	}

	bool GUI::highlighted(const Position& position) {
		for(int i=0; i<highlights.size();i++) {
			if (highlights.at(i) == position)
				return true;
		}

		return false;
	}
}
