#ifndef CONSTANTES_H
#define CONSTANTES_H

	// define game states
	enum class GameState {REDPLAYS, BLUEPLAYS, REDWIN, BLUEWIN, DRAW};

	// define quantities
	#define QTE_BOMBE 6
	#define QTE_ESPION 1
	#define QTE_ECLAIREUR 8
	#define QTE_DEMINEUR 5
	#define QTE_SERGENT 4
	#define QTE_LIEUTENANT 4
	#define QTE_CAPITAINE 4
	#define QTE_COMMANDANT 3
	#define QTE_COLONEL 2
	#define QTE_GENERAL 1
	#define QTE_MARECHAL 1
	#define QTE_DRAPEAU 1

	// define colors
	#define RED true
	#define BLUE false

	#define RED_VALUE "rouge"
	#define BLUE_VALUE "bleu"

	#include <iostream>
	#include <string>
	#include <cstddef>
	#include <cstdlib>

#endif
