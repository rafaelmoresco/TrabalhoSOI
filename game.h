#ifndef game_h
#define game_h

#include <iostream>
#include "enum.h"
#include "interface.h"
#include "char.h"
#include "pacman.h"
#include "ghost.h"

class Game
{
		public:
				Game(Pacman *_pac, Ghost *blinky, Ghost *pinky, Ghost *inky, Ghost *clyde);
        void update_interface();
        bool update_dots();
        int update_ghosts();
        void update_fruits();
				bool is_win();
				bool is_dead();
				bool is_finish();
				void set_direction(int name, Direction direction);
				void dead();

    private:
        Interface _interface;
        unsigned int _dot_counter;
        Pacman *_pacman;
        Ghost *_ghosts[4];
};


#endif
