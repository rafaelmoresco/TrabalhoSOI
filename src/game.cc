#include "game.h"

Game::Game(Pacman *_pac, Ghost *_blinky, Ghost *_pinky, Ghost *_inky, Ghost *_clyde)
{
	_pacman = _pac;
	_ghosts[0] = _blinky;
	_ghosts[1] = _pinky;
	_ghosts[2] = _inky;
	_ghosts[3] = _clyde;
}

// Define diracao do char de acordo com o nome.
void Game::set_direction(int name, Direction direction)
{
	if(name == 0)
		_pacman->set_direction(direction);
	else
		_ghosts[name - 1]->set_direction(direction);
}

// Invoca atualizacao de pontos, fantasmas e frutas.
void Game::update_interface()
{
	update_dots();
	update_ghosts();
	update_fruits();
}

// Controle de atualizacao dos pontos.
bool Game::update_dots()
{
    int pacman_x = _pacman->get_x();
    int pacman_y = _pacman->get_y();
	int i;
	bool up_ghost = false;

    if(_interface.get_maze(pacman_x, pacman_y) == o){
        _interface.set_maze(u, pacman_x, pacman_y);
        counter++;
        _interface.add_points(10);
    }else if(_interface.get_maze(pacman_x, pacman_y) == O){
        _interface.set_maze(u, pacman_x, pacman_y);
		for(i = 0; i < 4; i++){
			_ghosts[i]->set_mode(FRIGHTENED);
			up_ghost = true;
		}
        counter++;
        _interface.add_points(50);
    }
	return up_ghost;
}

// Controle de atualizacao dos fantasmas e seus respectivos modos.
int Game::update_ghosts()
{
	int pacman_x, pacman_y, ghost_x[4], ghost_y[4], i, up_ghost = -1;
	pacman_x = _pacman->get_x();
	pacman_y = _pacman->get_y();
	for(i = 0; i < 4; i++){
		ghost_x[i] = _ghosts[i]->get_x();
		ghost_y[i] = _ghosts[i]->get_y();
	}
	for(i = 0; i < 4; i++){
		if((ghost_x[i] >= 13 && ghost_x[i] <= 15) && (ghost_y[i] >= 11 && ghost_y[i] <= 16) && !_ghosts[i]->is_in_ghost_house()){
			_ghosts[i]->set_ghost_house(true);
			_ghosts[i]->set_eaten(false);
			up_ghost = i;
			break;
		}
	}
	for(i = 0; i < 4; i++){
		if(pacman_x == ghost_x[i] && pacman_y == ghost_y[i]){
			if(_ghosts[i]->get_mode() == FRIGHTENED){
				if(!_ghosts[i]->get_eaten()){
					_ghosts[i]->set_eaten(true);
					_interface.add_points(200);
				}
			}else if(!_ghosts[i]->get_eaten())
				_pacman->set_eaten(true);
		}
	}
	return up_ghost;
}

// Controle de atualizacao das frutas. Adicionando pontos quando o pacman come F.
void Game::update_fruits()
{
	int pacman_x = _pacman->get_x();
	int pacman_y = _pacman->get_y();

	if(counter == 70 || counter == 170)
		_interface.set_maze(F, 17, 13);
	if(_interface.get_maze(pacman_x, pacman_y) == F){
		_interface.set_maze(u, 17, 13);
		_interface.add_points(100);
	}
}

// Verfica se a contagem de pontos eh 244, isso significa que o pacman comeu todos os pontos do nivel.
bool Game::is_win()
{
	if(counter == 244)
		return true;
	return false;
}

// Verifica se pacman morreu.
bool Game::is_dead()
{
	if(_pacman->get_eaten())
		return true;
	return false;
}

// Verifica se pacman não possui mais vidas.
bool Game::is_finish()
{
	if(_interface.get_lives() == 0)
		return true;
	return false;
}

void Game::reset_counter()
{
	counter = 0;
}

// Quando passar de nivel eh necessario resetar o labirinto, e posicoes dos fantasmas e pacman.
void Game::next_level()
{
	_interface.add_level();
	reset_counter();
	_interface.reset_maze();
	_interface.reset_pills();
	_pacman->reset();
	_ghosts[0]->reset();
	_ghosts[1]->reset();
	_ghosts[2]->reset();
	_ghosts[3]->reset();
}

// Quando solicitado a reinicializacao eh necessario resetar os pontos, o labirinto, as vidas, e posicoes dos fantasmas e pacman.
void Game::restart()
{
	_interface.set_points(0);
	_interface.reset_maze();
	_interface.reset_pills();
	_interface.reset_lives();
	_pacman->reset();
	_ghosts[0]->reset();
	_ghosts[1]->reset();
	_ghosts[2]->reset();
	_ghosts[3]->reset();
}

// Quando pacman morreu eh necessario resetar o labirinto, decrementar vidas, e posicoes dos fantasmas e pacman.
void Game::dead()
{
	_interface.lose_life();
	_interface.reset_maze();
	_pacman->reset();
	_ghosts[0]->reset();
	_ghosts[1]->reset();
	_ghosts[2]->reset();
	_ghosts[3]->reset();
}
