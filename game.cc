#include "game.h"

Game::Game(Pacman *_pac, Ghost *_blinky, Ghost *_pinky, Ghost *_inky, Ghost *_clyde){
	_pacman = _pac;
	_ghosts[0] = _blinky;
	_ghosts[1] = _pinky;
	_ghosts[2] = _inky;
	_ghosts[3] = _clyde;
}

void Game::update_interface(){
	update_dots();
	update_ghosts();
	update_fruits();
}

bool Game::update_dots(){
    int pacx = _pacman->get_x();
    int pacy = _pacman->get_y();
		int i;
		bool rtn = false;

    if(_interface.get_maze(pacx, pacy) == o){
        _interface.set_maze(u, pacx, pacy);
        _dot_counter++;
        _interface.add_points(10);
    }else if(_interface.get_maze(pacx,pacy) == O){
        _interface.set_maze(u,pacx,pacy);
		for(i = 0; i < 4; i++){
			_ghosts[i]->set_mode(FRIGHTENED);
			rtn = true;
		}
        _dot_counter++;
        _interface.add_points(50);
    }
	return rtn;
}

int Game::update_ghosts(){
	int pacx, pacy, gx[4], gy[4], i, rtn = -1;
	pacx = _pacman->get_x();
	pacy = _pacman->get_y();
	for(i = 0; i < 4; i++){
		gx[i] = _ghosts[i]->get_x();
		gy[i] = _ghosts[i]->get_y();
	}
	for(i = 0; i < 4; i++){
		if((gx[i] >= 13 && gx[i] <= 15) && (gy[i] >= 11 && gy[i] <= 16) && !_ghosts[i]->is_in_ghost_house()){
			_ghosts[i]->set_ghost_house(true);
			_ghosts[i]->set_eaten(false);
			rtn = i;
			break;
		}
	}
	for(i = 0; i < 4; i++){
		if(pacx == gx[i] && pacy == gy[i]){
			if(_ghosts[i]->get_mode() == FRIGHTENED){
				if(!_ghosts[i]->get_eaten()){
					_ghosts[i]->set_eaten(true);
					_interface.add_points(200);
				}
			}else if(!_ghosts[i]->get_eaten())
				_pacman->set_eaten(true);
		}
	}
	return rtn;
}

void Game::update_fruits(){
	int pacx = _pacman->get_x();
	int pacy = _pacman->get_y();

	if(_dot_counter == 70 || _dot_counter == 170)
		_interface.set_maze(F, 17, 13);
	if(_interface.get_maze(pacx,pacy) == F){
		_interface.set_maze(u, 17, 13);
		_interface.add_points(100);
	}
}

void Game::set_direction(int name,Direction direction){
	if(name == 0)
		_pacman->set_direction(direction);
	else
		_ghosts[name-1]->set_direction(direction);
}

bool Game::is_win(){
	if(_dot_counter == 244)
		return true;
	return false;
}

bool Game::is_dead(){
	if(_pacman->get_eaten())
		return true;
	return false;
}

bool Game::is_finish(){
	if(_interface.get_lives() == 0)
		return true;
	return false;
}

void Game::dead(){
	_interface.lose_life();
	_interface.reset_maze();
	_pacman->reset();
	_ghosts[0]->reset();
	_ghosts[1]->reset();
	_ghosts[2]->reset();
	_ghosts[3]->reset();
}
