#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "window.h"
#include "pacman.h"
#include "ghost.h"
#include "game.h"
#include "keyevent.h"
#include "os/cpu.h"
#include "os/traits.h"
#include "os/thread.h"
#include "os/semaphore.h"
#include <unistd.h>

__BEGIN_API

class Main
{
public:
	Main() {}

	static void run(void * name)
	{
		tm_sem = new Semaphore();
		ghost_house_sem = new Semaphore();

		pacman = new Pacman(PACMAN);
		blinky = new Ghost(BLINKY);
		pinky = new Ghost(PINKY);
		inky = new Ghost(INKY);
		clyde = new Ghost(CLYDE);
		game = new Game(pacman,blinky,pinky,inky,clyde);
		event = new KeyEvent(game);

		window_thread = new Thread(screen);
		keyboard_thread = new Thread(key_event_input);
		game_thread = new Thread(run);
		blinky_thread = new Thread(ghost_blinky_behavior);
		pinky_thread = new Thread(ghost_pinky_behavior);
		inky_thread = new Thread(ghost_inky_behavior);
		clyde_thread = new Thread(ghost_clyde_behavior);
		pacman_thread = new Thread(pacman_behavior);

		window_thread->join();
		
		delete window_thread;
		delete keyboard_thread;
		delete blinky_thread;
		delete pinky_thread;
		delete inky_thread;
		delete clyde_thread;
		delete pacman_thread;
		delete game_thread;

		delete window;
		delete event;
		delete blinky;
		delete pinky;
		delete inky;
		delete clyde;
		delete pacman;
		delete game;
	}

	~Main() {}

private:
	static void screen()
	{
		_open = true;
		window = new Window();
		timer_start = 10000;
		while(timer_start > 0){
			window->start();
			timer_start--;
		}

		while(_open){
			window->KeyboardInput();
			if(!_paused){
				if(_win){
					game->next_level();
				}else if(_finish){
					timer_start = 10000;
					while(timer_start > 0)
						timer_start--;
					window->finish();
					_open = false;
				}else
					_open = window->run();
				tick();
			}
			Thread::yield();
		}
		window_thread->thread_exit(0);
	}

	static void key_event_input()
	{
		while(_open){
			if(!_paused)
				tm_sem->p();
			_paused = event->handler();
			if(!_paused)
				tm_sem->v();
			Thread::yield();
		}
		keyboard_thread->thread_exit(0);
	}

	static void run()
	{
		int i;
		while(_open){
			tm_sem->p();
			if(_dead){
				for(i = 0; i < 11; i++){
					timer_start = 600; 
					while(timer_start > 0){
						window->dead(i);
						timer_start--;
					}
				}
				game->dead();
				current_mode = 0;
				_dead = false;
			}
			if(game->update_dots())
				timer_frightened = 10000;
			i = game->update_ghosts();
			if(i >= 0 && timer_ghost_house[i] == -1)
				timer_ghost_house[i] = 0.5 * (rand() % 7 + 1) * 10000;

			game->update_fruits();
			_win = game->is_win();
			_finish = game->is_finish();

			if(!_finish)
				_dead = game->is_dead();

			tm_sem->v();
			Thread::yield();
		}
		game_thread->thread_exit(0);
	}

	static void ghost_blinky_behavior()
	{
		bool _leave = false;
		while(_open){
			if(blinky->is_in_ghost_house() && timer_ghost_house[(int)BLINKY - 1] == 0){
				if(!_leave){
					blinky->set_mode((Mode)(current_mode % 2));
					ghost_house_sem->p();
				}
				tm_sem->p();
				blinky->exit_ghost_house();
				tm_sem->v();
				_leave = blinky->is_in_ghost_house();
				if(!_leave){
					timer_ghost_house[(int)BLINKY-1] = -1;
					ghost_house_sem->v();
				}
			}else{
				tm_sem->p();
				if(timer_mode == 0 || timer_frightened == 0)
					blinky->set_mode((Mode)(current_mode % 2));
				blinky->move();
				if(blinky->crossroad())
					blinky->crossroad_decision();
				tm_sem->v();
			}
			Thread::yield();
		}
		blinky_thread->thread_exit(0);
	}

	static void ghost_pinky_behavior()
	{
		bool _leave = false;
		while(_open){
			if(pinky->is_in_ghost_house() && timer_ghost_house[(int)PINKY - 1] == 0){
				if(!_leave){
					pinky->set_mode((Mode)(current_mode % 2));
					ghost_house_sem->p();
				}
				tm_sem->p();
				pinky->exit_ghost_house();
				tm_sem->v();
				_leave = pinky->is_in_ghost_house();
				if(!_leave){
					timer_ghost_house[(int)PINKY-1] = -1;
					ghost_house_sem->v();
				}
			}else{
				tm_sem->p(); 
				if(timer_mode == 0 || timer_frightened == 0)
					pinky->set_mode((Mode)(current_mode % 2));
				pinky->move();
				if(pinky->crossroad())
					pinky->crossroad_decision();
				tm_sem->v();
			}
			Thread::yield();
		}
		pinky_thread->thread_exit(0);
	}

	static void ghost_inky_behavior()
	{
		bool _leave = false;
		while(_open){
			if(inky->is_in_ghost_house() && timer_ghost_house[(int)INKY - 1] == 0){
				if(!_leave){
					inky->set_mode((Mode)(current_mode%2));
					ghost_house_sem->p();
				}
				tm_sem->p();
				inky->exit_ghost_house();
				tm_sem->v();
				_leave = inky->is_in_ghost_house();
				if(!_leave){
					timer_ghost_house[(int)INKY-1] = -1;
					ghost_house_sem->v();
				}
			}else{
				tm_sem->p();
				if(timer_mode == 0 || timer_frightened == 0)
					inky->set_mode((Mode)(current_mode % 2));
				inky->move();
				if(inky->crossroad())
					inky->crossroad_decision();
				tm_sem->v();
			}
			Thread::yield();
		}
		inky_thread->thread_exit(0);
	}

	static void ghost_clyde_behavior()
	{
		bool _leave = false;
		while(_open){
			if(clyde->is_in_ghost_house() && timer_ghost_house[(int)CLYDE - 1] == 0){
				if(!_leave){
					clyde->set_mode((Mode)(current_mode % 2));
					ghost_house_sem->p();
				}
				tm_sem->p();
				clyde->exit_ghost_house();
				tm_sem->v();
				_leave = clyde->is_in_ghost_house();
				if(!_leave){
					timer_ghost_house[(int)CLYDE-1] = -1;
					ghost_house_sem->v();
				}
			}else{
				tm_sem->p();
				if(timer_mode == 0 || timer_frightened == 0)
					clyde->set_mode((Mode)(current_mode % 2));
				clyde->move();
				if(clyde->crossroad())
					clyde->crossroad_decision();
				tm_sem->v();
			}
			Thread::yield();
		}
		clyde_thread->thread_exit(0);
	}

	static void pacman_behavior()
	{
		while(_open){
			tm_sem->p();
			pacman->move();
			tm_sem->v(); 
			Thread::yield();
		}
		pacman_thread->thread_exit(0);
	}

	static void tick()
	{
		int i;
		if(timer_frightened >= 0)
			timer_frightened--;
		else if(timer_mode >= 0)
			timer_mode--;

		if(timer_mode == -1){
			if(current_mode < 7){
				timer_mode = mode_periods[current_mode]*3000;
				current_mode++; 
			}
		}
		for(i = 0; i < 4; i++){
			if(timer_ghost_house[i] > 0)
				timer_ghost_house[i]--;
		}

		if(timer_start > 0)
			timer_start--;
		Thread::yield();
	}

	private:
		static Semaphore *tm_sem;
		static Semaphore *ghost_house_sem;

		static Window *window;
		static Game *game;
		static KeyEvent *event;
		static Ghost *blinky;  
		static Ghost *pinky;
		static Ghost *inky;
		static Ghost *clyde;
		static Pacman *pacman;

		static Thread *window_thread;
		static Thread *game_thread;
		static Thread *keyboard_thread;
		static Thread *blinky_thread;
		static Thread *pinky_thread;
		static Thread *inky_thread;
		static Thread *clyde_thread;
		static Thread *pacman_thread;

		static bool _open;
		static bool _exit;
		static bool _win;
		static bool _dead;
		static bool _paused;
		static bool _finish;
		static int mode_periods[7];
		static int timer_mode;
		static int timer_ghost_house[4];
		static int timer_frightened;
		static int timer_start;
		static int current_mode;
};

__END_API

#endif
