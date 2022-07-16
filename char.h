#ifndef char_h
#define char_h

#include "enum.h"
#include "interface.h"
#include <cmath> 
#include <iostream>

class Char
{
    public:
        Char(CharName name);
        void run();
        int move();
        void update_position(); 
        void set_speed(float speed);
				void set_direction(Direction direction);
				bool is_next_tile_available(Direction direction);
        int get_x();
        int get_y();
        float get_x_px();
        float get_y_px();
				void set_x(int x);
        void set_y(int y);
        void set_x_px(float x_px);
        void set_y_px(float y_px);
        void set_eaten(bool eaten);
        bool get_eaten();
    protected:
        CharName _name;
        Interface _interface;
        int _x;
        int _y;
				float _b_x;
				float _b_y;
        int _x_px;
        int _y_px;
        Direction _direction;
        float _speed;
        bool _eaten;
};

#endif
