#ifndef CONSTANTES_H
#define CONSTANTES_H

	// define game states
	enum GameState {REDPLAYS, BLUEPLAYS, REDWIN, BLUEWIN};

	// define quantities
	#define QTE_BOMB 6
	#define QTE_SPY 1
	#define QTE_SCOUT 8
	#define QTE_MINER 5
	#define QTE_SERGEANT 4
	#define QTE_LIEUTENANT 4
	#define QTE_CAPTAIN 4
	#define QTE_MAJOR 3
	#define QTE_COLONEL 2
	#define QTE_GENERAL 1
	#define QTE_MARSHAL 1
	#define QTE_FLAG 1

	// define values
	#define FLAG 0
	#define BOMB 11
	#define SPY 1
	#define SCOUT 2
	#define MINER 3
	#define SERGEANT 4
	#define LIEUTENANT 5
	#define CAPTAIN 6
	#define MAJOR 7
	#define COLONEL 8
	#define GENERAL 9
	#define MARSHAL 10

	// define colors
	#define RED true
	#define BLUE false

	#include <iostream>
	#include <string>
	#include <cstddef>
	#include <cstdlib>

#endif
