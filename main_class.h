#ifndef main_class_h
#define main_class_h

#include "window.h"
#include "pacman.h"
#include "ghost.h"
#include "game.h"
#include "os/cpu.h"
#include "os/traits.h"
#include "os/thread.h"
#include "os/semaphore.h"

__BEGIN_API

class Main
{
public:
	Main() {
	}

	static void run(void * name){
		pacman = new Pacman(PACMAN);
		blinky = new Ghost(BLINKY);
		pinky = new Ghost(PINKY);
		inky = new Ghost(INKY);
		clyde = new Ghost(CLYDE);
		game = new Game(pacman, blinky, pinky, inky, clyde);

		window_thread = new Thread(printscreen);
		game_thread = new Thread(run_game);
		pacman_thread = new Thread(char_pacman);
		blinky_thread = new Thread(ghost_blinky);
		pinky_thread = new Thread(ghost_pinky);
		inky_thread = new Thread(ghost_inky);
		clyde_thread = new Thread(ghost_clyde);

		int wt;
		wt = window_thread->join();

		delete window_thread;
		delete pacman_thread;
		delete blinky_thread;
		delete pinky_thread;
		delete inky_thread;
		delete clyde_thread;
		delete game_thread;

		delete window;
		delete pacman;
		delete blinky;
		delete pinky;
		delete inky;
		delete clyde;
		delete game;
    }

    ~Main() {}

	static void char_pacman(){
		while(true){ //aberto
			tm_sem->p();
            // run
			tm_sem->v();
			Thread::yield();
		}
		pacman_thread->thread_exit(0);
	}

	private:
		static Thread *window_thread;
		static Thread *pacman_thread;
		static Thread *blinky_thread;
		static Thread *pinky_thread;
		static Thread *inky_thread;
		static Thread *clyde_thread;
		static Thread *game_thread;
		
		static Semaphore *tm_sem;
		static Semaphore *gh_sem;

		static Window *window;
		static Pacman *pacman;
		static Ghost *blinky;  
		static Ghost *pinky;
		static Ghost *inky;
		static Ghost *clyde;
		static Game *game;
};
__END_API

#endif