#include "GUI.h"

using namespace sf;
using namespace Game;

namespace GUI {

	GUI::GUI(Board& board) : board(board) {
		this->board = board;
		this->selected = false;
		this->boxSelected = false;
		this->mousePressed = false;

		this->play = false; // play = true when playing, false when filling the board
		this->boxPiece = NULL; // boxPiece selected to be put in the field

		// Text used to display messages (draw, win)
		messageFont.loadFromFile("polices/angelina.ttf");
		messageText.setFont(messageFont);
		messageText.setColor(Color::White);

		// Field
		if(fieldT.loadFromFile("./img/plateau.png")) {
			field.setTexture(fieldT);
		}

		// Window init
		window = new RenderWindow(VideoMode(2*fieldT.getSize().x,fieldT.getSize().y), "Stratego Game");
		window->setVerticalSyncEnabled(true);

		// viewports
		this->boxView.reset(FloatRect(0, 0, window->getSize().x/2, window->getSize().y));
		this->gameView.reset(FloatRect(0, 0, window->getSize().x/2, window->getSize().y));
		this->boxView.setViewport(FloatRect(0, 0, 0.5f, 1));
		this->gameView.setViewport(FloatRect(0.5f, 0, 0.5f, 1));

		// Pieces Red and blues
		if(piece_rougeT.loadFromFile("./img/piece.png")) piece_rouge.setTexture(piece_rougeT);
		if(piece_bleuT.loadFromFile("./img/piece2.png")) piece_bleu.setTexture(piece_bleuT);

		// Pieces images
		for(int i=0;i<12;i++) {
			Texture* tmpT = new Texture();
			Sprite tmpSprite;
			std::stringstream sstm;
			std::string fileName;
			sstm << "./img/" << i << ".png";
			fileName = sstm.str();

			if(tmpT->loadFromFile(fileName)) {
				piecesTexture.push_back(tmpT);
				tmpSprite.setTexture(*piecesTexture.at(i));
				piecesSprite.push_back(tmpSprite);
			}
			else {
				i--; // will retry ! (possibly infinite loop!!!!)
			}
		}
	}

	GUI::~GUI() {
		for(int i=0;i<12;i++) {
			delete this->piecesTexture.at(i);
		}
		this->piecesTexture.clear();
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

		if(!play) updateBox();
		else if ((board.getState() == REDPLAYS || board.getState() == BLUEPLAYS)) {
			updateGame();
		}
	}

	// Updates the box
	void GUI::updateBox() {

		bool color = RED;
		if(board.getBoardBox(RED)->getBox()->empty()) {
			if(board.getBoardBox(BLUE)->getBox()->empty()) {
				play = true;
				mousePressed = false;
				board.setState(RED);
				return;
			}
			else {
				color = BLUE; // when RED player is finished, it's at blue player to fill its board
				board.setState(color);
			}
		}

		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed) {
			Vector2i mousePosFrom = Mouse::getPosition(*window);
			Vector2f mousePosTo = window->mapPixelToCoords(mousePosFrom);
			Position tempPosFrom(mousePosFrom.x * 10 / this->boxView.getSize().x, mousePosFrom.y * 10 / this->boxView.getSize().y);
			Position tempPosTo(mousePosTo.x * 10 / this->boxView.getSize().x, mousePosTo.y * 10 / this->boxView.getSize().y);
			tempPosFrom.y = 9 - tempPosFrom.y; // SFML reverse repere in Y
			tempPosTo.y = 9 - tempPosTo.y; // SFML reverse repere in Y

			if(boxSelected) {
				board.putPiece(boxPiece,tempPosTo,true);
				boxSelected = false;

			}
			else {
				for(int i=0;i<board.getBoardBox(color)->getBox()->size();i++) {
					if(board.getBoardBox(color)->getBox()->at(i)->getPosition() == tempPosFrom) {
						boxPiece = board.getBoardBox(color)->getBox()->at(i);
						boxSelected = true;
						break;
					}
				}
			}
		}

		mousePressed = pressed;
	}

	// Updates the game
	void GUI::updateGame(){
		bool pressed = Mouse::isButtonPressed(Mouse::Left);
		if (pressed && !mousePressed) {
			Vector2i mousePosi = Mouse::getPosition(*window);
			Vector2f mousePos = window->mapPixelToCoords(mousePosi);
			Position tempPos(mousePos.x * 10 / this->gameView.getSize().x, mousePos.y * 10 / this->gameView.getSize().y);
			tempPos.y = 9 - tempPos.y; // SFML reverse repere in Y
			Piece* tempPiece = board.getPiece(tempPos);
			if (selected) { // If we have already selected a piece, and click on the board again, the piece should move.
				Piece* selectedPiece = board.getPiece(selection);
				board.movePiece(selection, tempPos);
				selected = false;
			}
			else if (tempPiece) { // If we haven't already selected a piece, then we should select it.
				if (!tempPiece->getColor() && (board.getState() == REDPLAYS)) return;
				else if (tempPiece->getColor() && (board.getState() == BLUEPLAYS)) return;
				selection = tempPos;
				selected = true;
				highlights.clear();
				highlights = board.moves(tempPos);
			}
		}

		mousePressed = pressed;
	}

	void GUI::render() {
		window->clear();
		window->setView(window->getDefaultView());
		if(play) drawMessage();
		window->setView(boxView);
		if(!play) {
			drawBoxInBox(RED);
			drawBoxInBox(BLUE);
		}
		else if ((board.getState() == REDPLAYS || board.getState() == BLUEPLAYS)) {
			drawBoxInGame(RED);
			drawBoxInGame(BLUE);
		}
		window->setView(gameView);
		if ((board.getState() == REDPLAYS || board.getState() == BLUEPLAYS)) {
			drawBoard();
			drawPieces();
		}
		window->display();
	}

	// Draws a message (win, lose)
	void GUI::drawMessage(){
		messageText.setPosition(Vector2f(window->getSize().x/3.0f,window->getSize().y/3.0f));
		messageText.setCharacterSize(25);
		board.canPlayerPlay();
		if (board.getState() == REDWIN)
			messageText.setString("Red wins!");
		else if (board.getState() == BLUEWIN)
			messageText.setString("Blue wins!");
		window->draw(messageText);
	}

	// Draws the board
	void GUI::drawBoard() {

		window->draw(field);

		RectangleShape square(Vector2f(this->gameView.getSize().x / 10.f, this->gameView.getSize().y / 10.f));
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				square.setPosition(x * this->gameView.getSize().x / 10.f, y * this->gameView.getSize().y / 10.f);

				if(selected && selection == Position(x, 9-y))
					square.setFillColor(Color(178, 102, 255, 170));
				else if (selected && this->board.isInMoveset(highlights, Position(x, 9-y)))
					square.setFillColor(Color(255, 255, 0, 170));
				else
					square.setFillColor(Color(255, 255, 255, 50));

				window->draw(square);
			}
		}
	}

	// Draws the pieces on top of the board.
	void GUI::drawPieces() {
		for (int x=0;x<10;x++) {
			for (int y=0;y<10;y++) {
				Piece* piece = board.getPiece(Position(x,9-y));
				if (piece) {
					piecesSprite.at(piece->getValue()).setPosition(Vector2f(x*this->gameView.getSize().x/10.f,(y-0.2f)*this->gameView.getSize().y/10.f));
					if(piece->getColor()) { // red piece
						piece_rouge.setPosition(Vector2f(x*this->gameView.getSize().x/10.f,(y-0.2f)*this->gameView.getSize().y/10.f));
						window->draw(piece_rouge);
					}
					else { // blue piece
						piece_bleu.setPosition(Vector2f(x*this->gameView.getSize().x/10.f,(y-0.2f)*this->gameView.getSize().y/10.f));
						window->draw(piece_bleu);
					}
					// if red turns (and red piece) or blue piece discovered
					if(((piece->getColor()) && ((board.getState() == REDPLAYS))) || (board.isPieceDiscovered(piece, BLUE))) {
						window->draw(piecesSprite.at(piece->getValue()));
					}
					// if blue turn (and blue piece) or red piece discovered
					if(((!piece->getColor()) && ((board.getState() == BLUEPLAYS))) || (board.isPieceDiscovered(piece, RED))) {
						window->draw(piecesSprite.at(piece->getValue()));
					}
				}
			}
		}
	}

	// Draws the box before the game (use initial pieces positions)
	void GUI::drawBoxInBox(bool color) {
		for(int i=0;i<board.getBoardBox(color)->getBox()->size();i++) {
			Vector2f Position = Vector2f(board.getBoardBox(color)->getBox()->at(i)->getPosition().x*this->boxView.getSize().x/10.f,(9-board.getBoardBox(color)->getBox()->at(i)->getPosition().y-0.2f)*this->boxView.getSize().y/10.f);

			if(color) {
				piece_rouge.setPosition(Position);
				window->draw(piece_rouge);
			}
			else {
				piece_bleu.setPosition(Position);
				window->draw(piece_bleu);
			}
			piecesSprite.at(board.getBoardBox(color)->getBox()->at(i)->getValue()).setPosition(Position);
			window->draw(piecesSprite.at(board.getBoardBox(color)->getBox()->at(i)->getValue()));
		}
	}

	// Draws the box during the game (use x,y positions by iterate)
	void GUI::drawBoxInGame(bool color) {
		int x = 0;
		int y = 0;
		if(color) y = 9;

		for(int i=0;i<board.getBoardBox(color)->getBox()->size();i++) {
			if(color) {
				piece_rouge.setPosition(Vector2f(x*this->boxView.getSize().x/10.f,(y-0.2f)*this->boxView.getSize().y/10.f));
				window->draw(piece_rouge);
			}
			else {
				piece_bleu.setPosition(Vector2f(x*this->boxView.getSize().x/10.f,(y-0.2f)*this->boxView.getSize().y/10.f));
				window->draw(piece_bleu);
			}
			piecesSprite.at(board.getBoardBox(color)->getBox()->at(i)->getValue()).setPosition(Vector2f(x*this->boxView.getSize().x/10.f,(y-0.2f)*this->boxView.getSize().y/10.f));
			window->draw(piecesSprite.at(board.getBoardBox(color)->getBox()->at(i)->getValue()));

			// simulation of for x,y...
			x++;
			if(x==10) {
				x=0;
				if(color) y--;
				else y++;
			}
		}
	}
}
