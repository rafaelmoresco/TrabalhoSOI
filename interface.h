#ifndef interface_h
#define interface_h

#include <iostream>
#include "enum.h"

class Interface
{
    public:
		Tile get_maze(int x, int y);
		int get_position(int x, int y);
		int get_position_px(int x, int y);
		Direction get_direction(int i);
		Mode get_mode(int name);
		int get_score();
		int get_high_score();
		bool get_eaten(int name);

		void set_maze(Tile tile, int x, int y);
		void set_position(int i, int x, int y);
		void set_position_px(int i, int x, int y);
		void set_direction(Direction direction, int i);
		void set_mode(int name, Mode mode);
		void set_eaten(bool eaten, int name);

		void add_points(int points);
		void lose_life();
		int get_lives();
		
		void reset_maze();
    private:
        static Tile _maze[31][28];
		static int _positions[5][2];
		static int _positions_px[5][2];
		static Direction _directions[5];
		static Mode _mode[5];
		static bool _eaten[5];
		static int _lives;
		static unsigned int _points;
        static unsigned int _high_score;
};

#endif
