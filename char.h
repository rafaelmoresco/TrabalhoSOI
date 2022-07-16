#ifndef char_h
#define char_h

#include "enum.h"
#include "interface.h"
#include <cmath> 
#include <iostream>

class Char
{
    public:
        Char(Name name);
        void run();
        int move();
        void update_position(); 
        void set_speed(double speed);
				void set_direction(Direction direction);
				bool is_next_tile_available(Direction direction);
        int get_x();
        int get_y();
        double get_x_px();
        double get_y_px();
				void set_x(int x);
        void set_y(int y);
        void set_x_px(double x_px);
        void set_y_px(double y_px);
        void set_eaten(bool eaten);
        bool get_eaten();
    protected:
        Name _name;
        Interface _interface;
        int _x;
        int _y;
				double _b_x;
				double _b_y;
        int _x_px;
        int _y_px;
        Direction _direction;
        double _speed;
        bool _eaten;
};

#endif
