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
		int get_points();
		int get_high_score();
		bool get_eaten(int name);
		int get_lives();
		int get_level();

		void set_maze(Tile tile, int x, int y);
		void set_position(int i, int x, int y);
		void set_position_px(int i, int x, int y);
		void set_direction(Direction direction, int i);
		void set_mode(int name, Mode mode);
		void set_points(int points);
		void set_high_score(int high_score);
		void set_eaten(bool eaten, int name);

		void add_points(int points);
		void add_level();
		void lose_life();

		void reset_maze();
		void reset_pills();
		void reset_level();
		void reset_lives();
    private:
        static Tile _maze[31][28];
        static Tile _aux_maze[31][28];
		static int _positions[5][2];
		static int _positions_px[5][2];
		static Direction _directions[5];
		static Mode _mode[5];
		static bool _eaten[5];
		static int _lives;
        static int _level;
		static unsigned int _points;
        static unsigned int _high_score;
};

#endif
