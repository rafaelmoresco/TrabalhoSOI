#include "ghost.h"

Mode Ghost::_main_mode = SCATTER;

Ghost::Ghost(Name name) : Char(name)
{
	_mode = SCATTER;
	_crossroad[0] = -1;
	_crossroad[1] = -1;
	_ghost_house = false;
}

// Definicao do modo.
void Ghost::set_mode(Mode mode)
{
	if(!_eaten ){
		if(mode == FRIGHTENED)
			set_speed(0.5);
		else
			set_speed(0.75);
		if(_mode != FRIGHTENED && mode != _mode){ 
			reverse_direction();
			_crossroad[0] = -1;
			_crossroad[1] = -1;
		}
	}
	_mode = mode;
	_interface.set_mode((int)_name,_mode);
}

void Ghost::set_main_mode(Mode mode)
{
	_main_mode = mode;
}

Mode Ghost::get_mode()
{
    return _mode;
}

void Ghost::set_eaten(bool eaten)
{
    _eaten = eaten;
    if(_eaten == true)
        set_speed(1.4);
	_interface.set_eaten(_eaten,(int)_name);
}

void Ghost::set_ghost_house(bool ghost_house)
{
	_ghost_house = ghost_house;
}

bool Ghost::is_in_ghost_house()
{
	return _ghost_house;
}

// Saida da casa e definicao de direcao, modo e posicao.
void Ghost::exit_ghost_house()
{
	if(_y_px > 108)
		_y_px--;
	else if(_y_px < 108)
		_y_px++;
	else
		_x_px--;

	if(_x_px <= 11 * 8 + 4){
		_x = 11;
		_y = 13;
		_crossroad[0]= _x;
		_crossroad[1]=_y;
		_interface.set_position(_x, (int)_name, 0);
		_interface.set_position(_y, (int)_name, 1);
		_ghost_house = false;
		set_direction(LEFT);
		set_mode(_main_mode);
	}
	_interface.set_position_px(_x_px, (int)_name, 0);
	_interface.set_position_px(_y_px, (int)_name, 1);
}

// Verifica cruzamento.
bool Ghost::crossroad()
{
	if(_x != _crossroad[0] || _y != _crossroad[1]){
		if(_direction == UP || _direction == DOWN){
			if((is_direction_available(LEFT)|| is_direction_available(RIGHT)) && _x_px >= _x * 8 + 2 && _x_px <= _x * 8 + 6){
				_crossroad[0] = _x;
				_crossroad[1] = _y;
				return true;
			}
		}else if(_direction == LEFT || _direction == RIGHT){
			if((is_direction_available(UP)|| is_direction_available(DOWN)) && _y_px >= _y * 8 + 2 && _y_px <= _y * 8 + 6){
				_crossroad[0] = _x;
				_crossroad[1] = _y;
				return true;
			}
		}
	}
	return false;
}

// Tomada de decisao para cruzamento.
void Ghost::crossroad_decision()
{
	int i, directions_available = 0, direction;
	double distance[4], dist;
	bool available[4];
	
	for(i = 0; i < 4; i++)
		available[i] = is_direction_available((Direction)i);
	
	for(i = 0; i < 4; i++){
		if(available[i]){
			directions_available++;
			direction = i;
		}
	}
	if(directions_available > 1){
		if(_mode == FRIGHTENED && !_eaten){
			do{
				direction = rand() % 4;
			}while(!available[direction]);
		} else{
			if(_eaten){
				_target_tiles[0] = 14;
				_target_tiles[1] = 13;
			}else if(_mode == SCATTER)
				target_tiles_scatter();
			else if(_mode == CHASE)
				target_tiles_chase();
			dist = 5000;
			
			for(i = 0; i < 4; i++){
				distance[i] = distance_target_tiles((Direction)i);
				if(available[i] && distance[i] < dist){
					dist = distance[i];
					direction = i;
				}
			}
		}
	}
	char a;
	set_direction((Direction)direction); 
}

// Tiles de alvo para o modo scatter.
void Ghost::target_tiles_scatter()
{
	if(_name == BLINKY){
		_target_tiles[0] = -2;
		_target_tiles[1] = 24;
	}else if(_name == PINKY){
		_target_tiles[0] = -2;
		_target_tiles[1] = 3;
	}else if(_name == INKY){
		_target_tiles[0] = 31;
		_target_tiles[1] = 27;
	}else if(_name == CLYDE){
		_target_tiles[0] = 31;
		_target_tiles[1] = 0;
	}
}

// Tiles de alvo para o modo chase.
void Ghost::target_tiles_chase()
{
	Direction direction = _interface.get_direction((int) PACMAN);
	int x = _interface.get_position((int)PACMAN, 0);
	int y = _interface.get_position((int)PACMAN, 1);
	if(_name == BLINKY){
		_target_tiles[0] = x;
		_target_tiles[1] = y;
	}else if(_name == PINKY){
		if(direction == UP)
			x -= 4;
		else if(direction == LEFT)
			y -= 4;
		else if(direction == DOWN)
			x +=4;
		else if(direction == RIGHT)
			y += 4;
		_target_tiles[0] = x;
		_target_tiles[1] = y;
	}else if(_name == INKY){
		if(direction == UP)
			x -= 2;
		else if(direction == LEFT)
			y -= 2;
		else if(direction == DOWN)
			x += 2;
		else if(direction == RIGHT)
			y += 2;
		_target_tiles[0] = _interface.get_position((int)BLINKY, 0) + (x - _interface.get_position((int)BLINKY, 0)) * 2;
		_target_tiles[1] = _interface.get_position((int)BLINKY, 1) + (y - _interface.get_position((int)BLINKY, 1)) * 2;
	}else if(_name == CLYDE){
		if(distance_target_tiles(_x, _y, x, y) > 8){
			_target_tiles[0] = x;
			_target_tiles[1] = y;
		}else{
			_target_tiles[0] = 30;
			_target_tiles[1] = 0;
		}
	}
}

// Inverte direcao.
void Ghost::reverse_direction()
{
    int direction = (int)_direction;
		direction < 2 ? direction += 2 : direction -= 2;
    _direction = (Direction)direction;
}

// Verifica se a direcao esta disponivel.
bool Ghost::is_direction_available(Direction direction)
{
	bool crossroad_behavior = false;
	bool reverse_direction = (int)direction != (int)_direction + 2 && (int)direction != (int)_direction - 2;
	int i;
	int crossroad_position[4][2] = {{23,12}, {23,15}, {11,12}, {11,15}};

	if(_mode != FRIGHTENED && direction == UP){
		for(i = 0; i < 4; i++){
			if(_x == crossroad_position[i][0] && _y == crossroad_position[i][1]){
				crossroad_behavior = true;
			}
		}
	}

	return is_next_tile_available(direction) && reverse_direction && !crossroad_behavior;
}

// Encontra a distancia entre x e y da direcao.
double Ghost::distance_target_tiles(Direction direction)
{
	int x = _x, y = _y;
	if(direction == UP)
		x--;
	else if(direction == LEFT)
		y--;
	else if(direction == DOWN)
		x++;
	else if(direction == RIGHT)
		y++;

	return sqrt(pow(x - _target_tiles[0], 2) + pow(y - _target_tiles[1], 2));
}

// Encontra a distancia entre tiles
double Ghost::distance_target_tiles(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Reseta direcao, velocidade, posicao, modo e cruzamento.
void Ghost::reset()
{
	_direction = LEFT;
	set_speed(0.75);
	_x = _interface.get_position((int)_name, 0);
	_y = _interface.get_position((int)_name, 1);
	_b_x = 0.0;
	_b_y = 0.0;
	_x_px = _interface.get_position_px((int)_name, 0);
	_y_px = _interface.get_position_px((int)_name, 1);
	_eaten = false;
	_mode = SCATTER;
	_crossroad[0] = -1;
	_crossroad[1] = -1;
	_ghost_house = false;
}