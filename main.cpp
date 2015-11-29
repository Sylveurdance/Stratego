#include "GUI.h"
#include "Board.h"

using namespace std;
using namespace Game;

int main() {

	Board board = Board();
	//board.fillBoard(RED);
	//board.fillBoard(BLUE);

	GUI::GUI gui(board);

	while (gui.isOpen()) {
		gui.update();
		gui.render();
	}

	return EXIT_SUCCESS;
}
