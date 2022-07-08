#include "game.h"

Game::Game(Pacman *_pacman, Ghost *_blinky, Ghost *_pinky, Ghost *_inky, Ghost *_clyde){
	_pacman = _pacman;
	_ghosts[0] = _blinky;
	_ghosts[1] = _pinky;
	_ghosts[2] = _inky;
	_ghosts[3] = _clyde;
}