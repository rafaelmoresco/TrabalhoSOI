#include "char.h"

Char::Char(CharName name)
{
	_name = name;
	_direction = LEFT;
	set_speed(0.75);
	_x = _interface.get_position((int)name, 0);
	_y = _interface.get_position((int)name, 1);
	_b_x = 0.0;
	_b_y = 0.0;
	_x_px = _interface.get_position_px((int)name,0);
	_y_px = _interface.get_position_px((int)name,1);
	_eaten = false;
}

int Char::move()
{
	if(_direction == UP){
		if(is_next_tile_available(UP))
			_b_x -= _speed;
		else if(!is_next_tile_available(UP) && _x_px + _b_x - _speed> _x * 8 + 4)
			_b_x -= _speed;
	}else if(_direction == LEFT){
		if( is_next_tile_available(LEFT))
			_b_y -= _speed;
		else if(!is_next_tile_available(LEFT) && _y_px + _b_y - _speed> _y*8 +4)
			_b_y -= _speed;
	}else if(_direction == DOWN){
		if ( is_next_tile_available(DOWN))
			_b_x += _speed;
		else if(!is_next_tile_available(DOWN) && _x_px + _b_x + _speed < _x*8 +4)
			_b_x += _speed;
	}else if(_direction == RIGHT){
		if(is_next_tile_available(RIGHT))
			_b_y += _speed;
		else if(!is_next_tile_available(RIGHT) && _y_px + _b_y + _speed < _y*8 +4)
			_b_y += _speed;
	}
	char a;

	update_position();
	return 1;
}

void Char::update_position()
{
	if(_x == 14 && _y_px < 6){
		_y = 27;
		_y_px = _y * 8 + 2;
	}else if(_x == 14 && _y_px > 27 * 8 + 2){
		_y = 0;
		_y_px = _y * 8 + 6;
	}
	_x_px += (int)_b_x;
	_y_px += (int)_b_y;
	_b_x -= (int)_b_x;
	_b_y -= (int)_b_y;
	
	_interface.set_position_px(_x_px, (int)_name, 0);
	_interface.set_position_px(_y_px, (int)_name, 1);

	int x = 0,  y = 0;
		x = (int)_x_px;
		x = x - x % 8;
		x = x / 8;
		if(x > 30){
			_x_px = 29 * 8;
			x = 29;
		}else if(x < 0){
			_x_px = 8;
			x = 1;
		}

		_x = x;
		y = (int)_y_px;
		y = y - y % 8;
		y = y / 8 ;

		if(y > 27)
			y = 27;
		else if(y < 0)
			y = 0;

		_y = y;
		_interface.set_position(_x,(int)_name,0);
		_interface.set_position(_y,(int)_name,1);
}

void Char::set_speed(float speed)
{
	_speed = speed *75.0 / FPS;
}

bool Char::is_next_tile_available(Direction direction)
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
	return _interface.get_maze(x, y) != W && (_interface.get_maze(x, y) != G || _eaten);
}

void Char::set_direction(Direction direction)
{
	if((direction == UP && is_next_tile_available(UP)) || (direction == DOWN && is_next_tile_available(DOWN))){
		if(_y_px >= _y * 8 + 2 &&  _y_px <= _y * 8 + 6){
			_b_y = 0.0;
			_y_px = _y * 8 + 4;
			_direction = direction;
			_interface.set_direction(direction, (int)_name);
		}
	}
	if((direction == LEFT && is_next_tile_available(LEFT)) || (direction == RIGHT && is_next_tile_available(RIGHT))){
		if(_x_px >= _x * 8 + 2 && _x_px <= _x * 8 + 6){
			_b_x = 0.0;
			_x_px = _x * 8 + 4;
			_direction = direction;
			_interface.set_direction(direction, (int)_name);
		}
	}
}

int Char::get_x()
{
    return _x;
}

int Char::get_y()
{
    return _y;
}

float Char::get_x_px()
{
    return _x_px;
}

float Char::get_y_px()
{
    return _y_px;
}

void Char::set_x(int x)
{
    _x = x;
}

void Char::set_y(int y)
{
    _y = y;
}

void Char::set_x_px(float x_px)
{
    _x_px = x_px;
}

void Char::set_y_px(float y_px)
{
    _y_px = y_px;
}

void Char::set_eaten(bool eaten)
{
    _eaten = eaten;
	_interface.set_eaten(_eaten, (int)_name);
}

bool Char::get_eaten()
{
    return _eaten;
}
