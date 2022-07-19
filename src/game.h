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
				void set_direction(int name, Direction direction);
        void update_interface();
        bool update_dots();
        int update_ghosts();
        void update_fruits();
        void restart();
        void next_level();
				bool is_win();
				bool is_dead();
				bool is_finish();
				void reset_counter();
				void dead();

    private:
        Interface _interface;
        Pacman *_pacman;
        Ghost *_ghosts[4];
        unsigned int counter;
};


#endif
