#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "enum.h"
#include "keyinput.h"
#include "interface.h"
#include "game.h"
#include<unistd.h>

class Window
{
public:
    Window();
    void KeyboardInput();
		void draw_maze();
		void draw_pacman();
		void draw_ghost(Name name);
		void draw_scores();
		void set_game(Game *game);
    bool run(); 
    void draw_texture(unsigned int texture, int length, int height, double angle);
		void start();
		void dead(int i);
		void finish();

private:
    void load_and_bind_textures();

		Game *_game;
		Interface _interface;
		int pacman_sprite;
		int ghost_sprite;
    KeyInput _key;

		static sf::Event event;
		sf::RenderWindow _window;
		sf::View _view;

		sf::Sprite pacman[3][4];
    sf::Sprite eyes[4];
    sf::Sprite ghosts[4][2];
		sf::Sprite numbers[10];

    sf::Sprite frightened_b[2];
    sf::Sprite frightened_w[2];
    sf::Sprite dying[11];

		//TEXTURES

    // Maze Textures
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;
    sf::Texture pill_tex;
    sf::Sprite pill_sprite;
    sf::Texture bigPill_tex;
    sf::Sprite bigPill_sprite;

    // Pacman Textures
    sf::Texture pac_0_tex;
		sf::Texture pac_1_tex;
		sf::Texture pac_2_tex;

    sf::Texture dead_0_tex;
    sf::Texture dead_1_tex;
    sf::Texture dead_2_tex;
    sf::Texture dead_3_tex;
    sf::Texture dead_4_tex;
    sf::Texture dead_5_tex;
    sf::Texture dead_6_tex;
    sf::Texture dead_7_tex;
    sf::Texture dead_8_tex;
    sf::Texture dead_9_tex;
    sf::Texture dead_10_tex;

    // Ghost Textures
    sf::Texture ghost_r_0_tex;
    sf::Texture ghost_r_1_tex;
    sf::Texture ghost_p_0_tex;
    sf::Texture ghost_p_1_tex;
    sf::Texture ghost_b_0_tex;
    sf::Texture ghost_b_1_tex;
    sf::Texture ghost_y_0_tex;
    sf::Texture ghost_y_1_tex;

    sf::Texture ghost_scared_0_tex;
    sf::Texture ghost_scared_1_tex;
    sf::Texture ghost_scared_2_tex;
    sf::Texture ghost_scared_3_tex;

    // Eye Textures
    sf::Texture eye_up_tex;
    sf::Texture eye_right_tex;
    sf::Texture eye_down_tex;
    sf::Texture eye_left_tex;

    // UI Textures
    sf::Texture num_0_tex;
    sf::Texture num_1_tex;
    sf::Texture num_2_tex;
    sf::Texture num_3_tex;
    sf::Texture num_4_tex;
    sf::Texture num_5_tex;
    sf::Texture num_6_tex;
    sf::Texture num_7_tex;
    sf::Texture num_8_tex;
    sf::Texture num_9_tex;

    sf::Texture score_200_tex;
    sf::Sprite score_200_sprite;
    sf::Texture score_400_tex;
    sf::Sprite score_400_sprite;
    sf::Texture score_800_tex;
    sf::Sprite score_800_sprite;
    sf::Texture score_1600_tex;
    sf::Sprite score_1600_sprite;
    sf::Texture ready_tex;
    sf::Sprite ready_sprite;
    sf::Texture gameover_tex;
    sf::Sprite gameover_sprite;
    sf::Texture life_tex;
    sf::Sprite life_sprite;
    sf::Texture score_tex;
    sf::Sprite score_sprite;
    sf::Texture high_tex;
    sf::Sprite high_sprite;
    sf::Texture score_100_tex;
    sf::Sprite score_100_sprite;
    sf::Texture score_300_tex;
    sf::Sprite score_300_sprite;

    // Fruit Textures
    sf::Texture cherry_tex;
    sf::Sprite cherry_sprite;
    sf::Texture strawberry_tex;
    sf::Sprite strawberry_sprite;
};

#endif
