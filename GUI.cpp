#include "GUI.h"

using namespace sf;
using namespace Game;

namespace GUI {

	GUI::GUI(int width, int height, Board& board) {
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

		Texture fieldT;
		fieldT.loadFromFile("./img/plateau.png");
		field.setTexture(fieldT);
		field.setColor(Color(255, 255, 255, 128));

		piece_rouge.setTexture(Texture("./img/piece.png"));
		piece_bleu.setTexture(Texture("./img/piece2.png"));

		piecesTexture = new std::vector<Texture>();
		piecesTexture.push_back(Texture("./img/drapeau.png"));
		piecesTexture.push_back(Texture("./img/1-espion.png"));
		piecesTexture.push_back(Texture("./img/2-eclaireur.png"));
		piecesTexture.push_back(Texture("./img/3-demineur.png"));
		piecesTexture.push_back(Texture("./img/4-sergent.png"));
		piecesTexture.push_back(Texture("./img/5-lieutenant.png"));
		piecesTexture.push_back(Texture("./img/6-capitaine.png"));
		piecesTexture.push_back(Texture("./img/7-commandant.png"));
		piecesTexture.push_back(Texture("./img/8-colonel.png"));
		piecesTexture.push_back(Texture("./img/9-general.png"));
		piecesTexture.push_back(Texture("./img/10-marechal.png"));
		piecesTexture.push_back(Texture("./img/bombe.png"));

		piecesSprite = new std::vector<Sprite>();
		for(int i=0;piecesTexture.size();i++) {
			Sprite tmpSprite;
			tmpSprite.setTexture(piecesTexture.at(i));
			piecesSprite.push_back(tmpSprite);
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

		updateMessage();
		if ((board.getState() == GameState::REDPLAYS || board.getState() == GameState::BLUEPLAYS)) {
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
			if((tempPiece->getValue()!=FLAG) && (tempPiece->getValue()!=BOMB)) {
				Unite* tempUnit = dynamic_cast<Unite*>(tempPiece);
				if (selected) { // If we have already selected a piece, and click on the board again, the piece should move.
					Piece* selectedPiece = board.getPiece(selection);
					if((selectedPiece->getValue()!=FLAG) && (selectedPiece->getValue()!=BOMB)) { // Unit
						if(board.isCorrectMove(selection, tempPos)) {
							board.movePiece(selection, tempPos);
							selected = false;
						}
						else if (tempPiece != nullptr) { // Prevent selecting of opponent pieces.
							if (!tempPiece->getColor() && (board.getState() == GameState::REDPLAYS))
								return;
							else if (tempPiece->getColor() && (board.getState() == GameState::BLUEPLAYS))
								return;
							selection = tempPos;
							selected = true;
							highlights = tempUnit->moves(board);
						}
					}
				}
				else if (tempPiece != nullptr) { // If we haven't already selected a piece, then we should select it.
					if (!tempPiece->getColor() && (board.getState() == GameState::REDPLAYS))
						return;
					else if (tempPiece->getColor() && (board.getState() == GameState::BLUEPLAYS))
						return;
					selection = tempPos;
					selected = true;
					highlights = tempUnit->moves(board);
				}
			}
		}

		mousePressed = pressed;
	}

	void GUI::drawMessage(){
		messageText.setPosition(Vector2f(width/3.0f,height/3.0f));
		messageText.setCharacterSize(25);
		board.canPlayerPlay();
		if (board.getState() == GameState::REDWIN)
			messageText.setString("Red wins!");
		else if (board.getState() == GameState::BLUEWIN)
			messageText.setString("Blue wins!");
		window->draw(messageText);
	}

	void GUI::updateMessage(){
		return;
	}

	void GUI::render() {
		window->clear();
		drawMessage();
		if ((board.getState() == GameState::REDPLAYS || board.getState() == GameState::BLUEPLAYS)) {
			drawBoard();
			drawPieces();
		}
		window->display();
	}

	void GUI::drawBoard() {

		window->draw(field);

		Color brightSquare(224, 217, 190);
		Color darkSquare(152, 145, 135);

		RectangleShape square(Vector2f(width / 10.f, height / 10.f));
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				square.setPosition(x * width / 10.f, y * height / 10.f);

				if (selected && selection == Position(x, 9-y))
					square.setFillColor(Color::Yellow);
				else if (selected && highlighted(Position(x, 9-y)))
					square.setFillColor(Color::Green);
				else if ((x+y)%2 == 0)
					square.setFillColor(brightSquare);
				else
					square.setFillColor(darkSquare);

				window->draw(square);
			}
		}
	}

	void GUI::drawPieces() {
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				Piece* piece = board.getPiece(Position(x,9-y));
				if (piece != nullptr) {
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
		for (Position move : highlights) {
			if (move == position)
				return true;
		}

		return false;
	}
}
