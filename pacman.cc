#include "pacman.h"

Pacman::Pacman(CharName name): Char(name){
	set_speed(0.8);
}
void Pacman::reset(){
	set_speed(0.8);
	_direction = _interface.get_direction((int)PACMAN);
	_x =_interface.get_position((int)_name, 0);
	_y =_interface.get_position((int)_name, 1);
	_x_px =_interface.get_position_px((int)_name, 0);
	_y_px =_interface.get_position_px((int)_name, 1);
	_eaten = false;
} 
