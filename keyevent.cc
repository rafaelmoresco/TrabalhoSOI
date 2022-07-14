#include "keyevent.h"

KeyEvent::KeyEvent(Game *game){
	_game = game;
}

bool KeyEvent::handler(){
	if(!_key.get_handled()){
		Key key = _key.get_key();
		if(key == U_KEY)
			_game->set_direction((int)PACMAN, UP);
		else if(key == L_KEY)
			_game->set_direction((int)PACMAN, LEFT);
		else if(key == D_KEY)
			_game->set_direction((int)PACMAN, DOWN);
		else if(key == R_KEY)
			_game->set_direction((int)PACMAN, RIGHT);
		else if(key == P_KEY)
			_paused = !_paused && true;
		_key.set_handled(true);
	}
	return _paused;
}
