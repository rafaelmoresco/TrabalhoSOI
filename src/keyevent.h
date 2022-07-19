#ifndef keyhandler_h
#define keyhandler_h

#include <iostream>
#include "enum.h"
#include "keyinput.h"
#include "game.h"

class KeyEvent
{
	public:
		KeyEvent(Game *game);
		bool handler();
	private:
		Game *_game;
		KeyInput _key;
		bool _paused;
};

#endif
