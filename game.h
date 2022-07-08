#ifndef game_h
#define game_h

#include "enum.h"
#include "char.h"
#include "pacman.h"
#include "ghost.h"

class Game{
		public:
        Game(Pacman *_pacman, Ghost *_blinky, Ghost *_pinky, Ghost *_inky, Ghost *_clyde);
        int updateGhosts();
        void updateFruits();

    private:
        Pacman *_pacman;
        Ghost *_ghosts[4];
};


#endif