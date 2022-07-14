#ifndef keyhandler_h
#define keyhandler_h

#include <iostream>
#include "enum.h"
#include "keyinput.h"
#include "game.h"

class KeyEvent{
	public:
		KeyEvent(Game *game);
		bool handler();
	private:
		bool _paused;
		Game *_game;
		KeyInput _key;
};

#endif
