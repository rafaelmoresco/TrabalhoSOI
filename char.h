#ifndef char_h
#define char_h

#include "enum.h"

class Char{
    public:
        Char(CharName name);
        void setSpeed(float percentage);
        void setDirection(Direction direction);
        int getX();
        int getY();
        float getX_px();
        float getY_px();
        void setX(int x);
        void setY(int y);
        void setX_px(float x_px);
        void setY_px(float y_px);

    protected:
        CharName _name;
        int _x;
        int _y;
        float _b_x;
        float _b_y;
        int _x_px;
        int _y_px;
        Direction _direction;
        float _speed;
};

#endif
