#include "GUI.h"
#include "Board.h"

int main() {
	Game::Board board;
	board.fillBoard(RED);
	board.fillBoard(BLUE);

	GUI::GUI gui(600, 600, board);

	while (gui.isOpen()) {
		gui.update();
		gui.render();
	}

	return EXIT_SUCCESS;
}
