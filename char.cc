#include "char.h"

Char::Char(CharName name){
	_name = name;
	_direction = LEFT;
	setSpeed(1);
	// _x = _tilemap.GetPosition((int)name,0);
	// _y = _tilemap.GetPosition((int)name,1);
	_b_x = 0.0;
	_b_y = 0.0;
	// _x_px = _tilemap.GetPosition_px((int)name,0);
	// _y_px = _tilemap.GetPosition_px((int)name,1);
}

void Char::setSpeed(float percentage){
	_speed = percentage * 30.0 / FPS;
}

int Char::getX(){
    return _x;
}

int Char::getY(){
    return _y;
}

float Char::getX_px(){
    return _x_px;
}

float Char::getY_px(){
    return _y_px;
}

void Char::setX(int x){
    _x = x;
}

void Char::setY(int y){
    _y = y;
}

void Char::setX_px(float x_px){
    _x_px = x_px;
}

void Char::setY_px(float y_px){
    _y_px = y_px;
}
