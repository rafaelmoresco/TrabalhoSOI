#ifndef ghost_h
#define ghost_h

#include <iostream>
#include <cstdlib>
#include "enum.h"
#include "char.h"
#include <cmath>

class Ghost : public Char
{
    public:
		Ghost(CharName name);
        void set_mode(Mode mode);
		static void set_main_mode(Mode mode);
        Mode get_mode();
        void set_eaten(bool eaten);
		void set_ghost_house(bool ghost_house);
		bool is_in_ghost_house();
		void exit_ghost_house();
        bool crossroad();
        void crossroad_decision();
        void target_tiles_scatter();
        void target_tiles_chase();
        void reverse_direction();
		bool is_direction_available(Direction direction);
		float distance_target_tiles(Direction direction);
		float distance_target_tiles(int x1, int y1, int x2, int y2);
		void reset();
    private:
		Mode _mode;
		static Mode _main_mode;
		int _target_tiles[2];
        bool _ghost_house; 
		int _crossroad[2];
};

#endif
