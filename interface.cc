#include "interface.h"

/**
 * Tile defined as an enum where each type is defined as:
 *      W: Wall
 *      G: Ghost Pen Gate
 *      P: Portal
 *      u: Empty path
 *      o: Pill
 *      O: Big Pill
 *		F: Fruit
 */
Tile Interface::_maze[31][28] = {
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,O,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,W,W,W,W,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,G,G,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{P,u,u,u,u,u,o,u,u,u,W,u,u,u,u,u,u,W,u,u,u,o,u,u,u,u,u,P},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,o,o,W,W,o,o,o,o,o,o,o,u,u,o,o,o,o,o,o,o,W,W,o,o,O,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
};

Tile Interface::_aux_maze[31][28] = {
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,O,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,W,W,W,W,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,G,G,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{P,u,u,u,u,u,o,u,u,u,W,u,u,u,u,u,u,W,u,u,u,o,u,u,u,u,u,P},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,o,o,W,W,o,o,o,o,o,o,o,u,u,o,o,o,o,o,o,o,W,W,o,o,O,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
};

int Interface::_positions[5][2] = {{23,13}, {11,13}, {14,11}, {14,13}, {14,15}};
int Interface::_positions_px[5][2] = {{188, 108}, {92, 108}, {116, 92}, {116, 108}, {116, 124}};

unsigned int Interface::_points = 0;
unsigned int Interface::_high_score = 0;

Mode Interface::_mode[5] = {CHASE, CHASE, CHASE, CHASE, CHASE};
Direction Interface::_directions[5] = {LEFT, LEFT, LEFT, LEFT, LEFT};

int Interface::_lives = 3;
int Interface::_level = 0;
bool Interface::_eaten[5] = {false, false, false, false, false};

void Interface::set_mode(int name,Mode mode)
{
	_mode[name] = mode;
}

Mode Interface::get_mode(int name)
{
	return _mode[name];
}

int Interface::get_lives()
{
	return _lives;
}
void Interface::set_direction(Direction direction, int i)
{
	_directions[i] = direction;
}

void Interface::set_position(int i, int x, int y)
{
	_positions[x][y] = i;
}

void Interface::set_position_px(int i, int x, int y)
{
	_positions_px[x][y] = i;
}

Direction Interface::get_direction(int i)
{
	return _directions[i];
}

int Interface::get_position(int x, int y)
{
	return _positions[x][y];
}

int Interface::get_position_px(int x, int y)
{
	return _positions_px[x][y];
}

Tile Interface::get_maze(int x, int y)
{
    return _maze[x][y];
}

void Interface::set_maze(Tile tile, int x, int y)
{
    _maze[x][y] = tile;
}

void Interface::add_points(int points)
{
	_points += points;
	if(_high_score < _points)
		_high_score = _points;
}

int Interface::get_points()
{
	return _points;
}

void Interface::set_points(int points)
{
	_points = points;
}

int Interface::get_high_score()
{
	return _high_score;
}

void Interface::set_high_score(int high_score)
{
	_high_score = high_score;
}

void Interface::set_eaten(bool eaten,int name)
{
	_eaten[name] = eaten;
}

bool Interface::get_eaten(int name)
{
	return _eaten[name];
}

int Interface::get_level()
{
	return _level;
}

void Interface::add_level()
{
	_level++;
}

void Interface::reset_maze()
{
	int positions[5][2] = {{23, 13}, {11, 13}, {14, 11}, {14, 13}, {14, 15}}, i, j;

	for(i = 0; i < 5; i++){
		for(j = 0; j < 2; j++){
			_mode[i] = SCATTER;
			_positions[i][j] = positions[i][j];
			_positions_px[i][j] = _positions[i][j] * 8 + 4;
			_directions[i] = LEFT;
		}
	}
}

void Interface::reset_pills()
{
	for(int i = 0; i < 31; i++){
		for(int j = 0; j < 28; j++)
			_maze[i][j] = _aux_maze[i][j];
	}
}

void Interface::reset_lives()
{
	_lives = 3;
}

void Interface::reset_level()
{
	_level = 0;
}

void Interface::lose_life()
{
	_lives--;
}
