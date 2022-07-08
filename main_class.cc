#include "main_class.h"

__BEGIN_API

Thread *Main::window_thread = 0;
Thread *Main::pacman_thread = 0;
Thread *Main::blinky_thread;
Thread *Main::pinky_thread;
Thread *Main::inky_thread;
Thread *Main::clyde_thread;
Thread *Main::game_thread;

Window *Main::window = 0;
Pacman *Main::pacman;
Ghost *Main::blinky;  
Ghost *Main::pinky;
Ghost *Main::inky;
Ghost *Main::clyde;
Game *Main::game;

__END_API