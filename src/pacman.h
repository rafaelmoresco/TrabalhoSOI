#ifndef pacman_h
#define pacman_h

#include <iostream>
#include "enum.h"
#include "char.h"

class Pacman : public Char
{
    public:
        Pacman(Name name);
        void reset();
};

#endif
