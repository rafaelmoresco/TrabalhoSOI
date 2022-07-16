#include "keyevent.h"

KeyEvent::KeyEvent(Game *game)
{
	_game = game;
}

bool KeyEvent::handler()
{
	if(!_key.get_handled()){
		DirectionKey key = _key.get_key();
		if(key == UP_KEY)
			_game->set_direction((int)PACMAN, UP);
		else if(key == LEFT_KEY)
			_game->set_direction((int)PACMAN, LEFT);
		else if(key == DOWN_KEY)
			_game->set_direction((int)PACMAN, DOWN);
		else if(key == RIGHT_KEY)
			_game->set_direction((int)PACMAN, RIGHT);
		else if(key == P_PAUSE_KEY)
			_paused = !_paused && true;
		_key.set_handled(true);
	}
	return _paused;
}
