#include "GUI.h"
#include <Board.h>

using namespace sf;

int main() {
	Game::Board board;
	GUI::GUI gui(600, 600, board);

	while (gui.isOpen()) {
		gui.update();
		gui.render();
	}

	return EXIT_SUCCESS;
}
