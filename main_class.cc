#include "main_class.h"

__BEGIN_API

Semaphore *Main::tm_sem = 0;
Semaphore *Main::ghost_house_sem = 0;

Window *Main::window;
Game *Main::game;
KeyEvent *Main::event;
Ghost *Main::blinky;  
Ghost *Main::pinky;
Ghost *Main::inky;
Ghost *Main::clyde;
Pacman *Main::pacman;

Thread *Main::window_thread = 0;
Thread *Main::game_thread = 0;
Thread *Main::keyboard_thread = 0;
Thread *Main::blinky_thread = 0;
Thread *Main::pinky_thread = 0;
Thread *Main::inky_thread = 0;
Thread *Main::clyde_thread = 0;
Thread *Main::pacman_thread = 0;

bool Main::_open = false;
bool Main::_exit = false;
bool Main::_win = false;
bool Main::_dead = false;
bool Main::_paused = false;
bool Main::_finish = false;
int Main::mode_periods[7] = {7, 20, 7, 20, 5, 20, 5};
int Main::timer_mode = 0;
int Main::timer_ghost_house[4] = {-1, -1, -1, -1};
int Main::timer_frightened = 0;
int Main::timer_start = 3;
int Main::current_mode = 0;

__END_API 