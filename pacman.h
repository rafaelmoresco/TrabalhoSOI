#ifndef pacman_h
#define pacman_h

#include "enum.h"
#include "char.h"

class Pacman : public Char{
    public:
        Pacman(CharName name);
        void Reset();
};

#endif
