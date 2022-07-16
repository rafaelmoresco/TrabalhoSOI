#include "window.h"

sf::Event Window::event;

Window::Window()
{
    load_and_bind_textures();
    new (&_window) sf::RenderWindow(sf::VideoMode(448, 576), "Pacman");

    _window.setKeyRepeatEnabled(false);
		_view.reset(sf::FloatRect(0, 0, 224, 288));
		_window.setView(_view);
		pacsprite = 0;
		ghostsprite = 0;
		draw_maze();
		draw_scores();
}

void Window::KeyboardInput()
{
	while (_window.pollEvent(event)){
		switch (event.type) {
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						std::cout << "Keyboard esquerda!" << std::endl;
						_key.set_key(L_KEY);
						_key.set_handled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						std::cout << "Keyboard direita!" << std::endl;
						_key.set_key(R_KEY);
						_key.set_handled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						std::cout << "Keyboard para baixo!" << std::endl;
						_key.set_key(D_KEY);
						_key.set_handled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						std::cout << "Keyboard para cima!" << std::endl;
						_key.set_key(U_KEY);
						_key.set_handled(false);
				} else if(event.key.code == 15) {
						_key.set_key(P_KEY);
						_key.set_handled(false);
				} else if(event.key.code == 16) {
						_key.set_key(Q_KEY);
						_window.close();
				}
				break;
			}
	}
}

void Window::draw_scores()
{
	int i,num;
	int score_pos[2] = {48, 12};
	int highscore_pos[2] = {128, 12};
	int _points = _interface.get_score();
	int _high_score = _interface.get_high_score();

	for(i = 0; _high_score % (int)pow(10, i) != _high_score; i++){
		num = (_points % (int)pow(10, i + 1) - _points % (int)pow(10, i)) / pow(10, i);
		numbers[num].setPosition(score_pos[0], score_pos[1]);
		_window.draw(numbers[num]);
		score_pos[0] -= 8;
		num = (_high_score % (int)pow(10, i + 1) - _high_score % (int)pow(10, i)) / pow(10, i);
		numbers[num].setPosition(highscore_pos[0], highscore_pos[1]);
		_window.draw(numbers[num]);
		highscore_pos[0] -= 8;
	}
}

void Window::draw_maze()
{
	int i, j;
	Tile tile_aux;

	_window.clear();
	maze_sprite.setPosition(0, 24);
	_window.draw(maze_sprite);
	high_sprite.setPosition(75, 2);
	_window.draw(high_sprite);
	score_sprite.setPosition(112, 2);
	_window.draw(score_sprite);
	life_sprite.setPosition(16, 272);
	_window.draw(life_sprite);
	life_sprite.setPosition(32, 272);
	_window.draw(life_sprite);
	cherry_sprite.setPosition(192, 272);
	_window.draw(cherry_sprite);

	for(i = 0; i < 31; i++){
		for(j = 0; j < 28; j++){
			tile_aux = _interface.get_maze(i,j);
			if(tile_aux == o){
				pill_sprite.setPosition(8 * j, 24 + 8 * i);
				_window.draw(pill_sprite);
			}else if(tile_aux == O){
				bigPill_sprite.setPosition(8 * j, 8 * i + 24);
				_window.draw(bigPill_sprite);
			}else if(tile_aux == F){
				cherry_sprite.setPosition(8 * j - 3, 8 * i + 21);
				_window.draw(cherry_sprite);
			}
		}
	}
}

void Window::draw_pacman()
{
	sf::Sprite sprite;
	sprite = pacman[(int)(pacsprite / 4)][(int)_interface.get_direction((int)PACMAN)];
	pacsprite == 11 ? pacsprite = 0 : pacsprite++;
	sprite.setPosition(_interface.get_position_px((int)PACMAN, 1) - 7, 24 + _interface.get_position_px((int)PACMAN,0) - 7);
	_window.draw(sprite);
}

void Window::draw_ghost(CharName name)
{
	if(_interface.get_mode((int)name) == FRIGHTENED && !_interface.get_eaten((int)name)){
		frightened_b[(int)(ghostsprite / 4)].setPosition(_interface.get_position_px((int)name, 1) - 7, 24 + _interface.get_position_px((int)name,0) - 7);
		_window.draw(frightened_b[(int)(ghostsprite / 4)]);
	}else{
		if(!_interface.get_eaten((int)name)){
			ghosts[(int)name - 1][(int)(ghostsprite / 4)].setPosition(_interface.get_position_px((int)name,1) - 7, 24 + _interface.get_position_px((int)name,0) - 7);
			_window.draw(ghosts[(int)name - 1][0]);
		}

		eyes[(int)_interface.get_direction((int)name)].setPosition(_interface.get_position_px((int)name,1) - 7, 24 + _interface.get_position_px((int)name,0) - 7);
		_window.draw(eyes[(int)_interface.get_direction((int)name)]);
	}
	ghostsprite == 7 ? ghostsprite = 0 : ghostsprite++;
}

void Window::start()
{
		draw_ghost(BLINKY);
		draw_ghost(PINKY);
		draw_ghost(INKY);
		draw_ghost(CLYDE);
		draw_pacman();
		ready_sprite.setPosition(88, 160);
		_window.draw(ready_sprite);
		_window.display();
}

void Window::dead(int i)
{
	sf::Sprite sprite;
	draw_maze();	
	sprite = dying[i];
	sprite.setPosition(_interface.get_position_px((int)PACMAN,1) - 7, 24 + _interface.get_position_px((int)PACMAN,0) - 7);
	_window.draw(sprite);
	_window.display();
}

void Window::win()
{
	_window.close();
}

void Window::finish()
{
	_window.close();
}

bool Window::run()
{
	draw_maze();
	draw_scores();

	draw_pacman();
	draw_ghost(BLINKY);
	draw_ghost(PINKY);
	draw_ghost(INKY);
	draw_ghost(CLYDE);

	_window.display();
	return _window.isOpen();
}

void Window::load_and_bind_textures()
{
    maze_tex.loadFromFile("sprites/maze/maze.png");
    maze_sprite.setTexture(maze_tex);

    pill_tex.loadFromFile("sprites/maze/p-0.png");
    pill_sprite.setTexture(pill_tex);
    bigPill_tex.loadFromFile("sprites/maze/p-1.png");
    bigPill_sprite.setTexture(bigPill_tex);

    pac_0_tex.loadFromFile("sprites/pacman/0.png");
	pac_1_tex.loadFromFile("sprites/pacman/1.png");
	pac_2_tex.loadFromFile("sprites/pacman/2.png");

    // Bind Pacman textures
	pacman[0][0].setOrigin(pac_0_tex.getSize().x / 2, pac_0_tex.getSize().y / 2);
    pacman[0][0].setTexture(pac_0_tex);
	pacman[0][0].setRotation(90);
	pacman[0][1].setTexture(pac_0_tex);
	pacman[0][2].setOrigin(pac_0_tex.getSize().x / 2, pac_0_tex.getSize().y / 2);
	pacman[0][2].setTexture(pac_0_tex);
	pacman[0][2].rotate(270);
	pacman[0][3].setOrigin(pac_0_tex.getSize().x / 2, pac_0_tex.getSize().y / 2);
	pacman[0][3].setTexture(pac_0_tex);
	pacman[0][3].rotate(180);

	pacman[1][0].setOrigin(pac_1_tex.getSize().x / 2, pac_1_tex.getSize().y/ 2);
    pacman[1][0].setTexture(pac_1_tex);
	pacman[1][0].rotate(90);
	pacman[1][1].setTexture(pac_1_tex);
	pacman[1][2].setOrigin(pac_1_tex.getSize().x / 2, pac_1_tex.getSize().y / 2);
	pacman[1][2].setTexture(pac_1_tex);
	pacman[1][2].rotate(270);
	pacman[1][3].setOrigin(pac_1_tex.getSize().x / 2, pac_1_tex.getSize().y / 2);
	pacman[1][3].setTexture(pac_1_tex);
	pacman[1][3].rotate(180);

	pacman[2][0].setOrigin(pac_2_tex.getSize().x / 2, pac_2_tex.getSize().y / 2);
	pacman[2][0].setTexture(pac_2_tex);
	pacman[2][0].rotate(90);
	pacman[2][1].setTexture(pac_2_tex);
	pacman[2][2].setOrigin(pac_2_tex.getSize().x / 2, pac_2_tex.getSize().y / 2);
	pacman[2][2].setTexture(pac_2_tex);
	pacman[2][2].rotate(270);
	pacman[2][3].setOrigin(pac_2_tex.getSize().x / 2, pac_2_tex.getSize().y / 2);
	pacman[2][3].setTexture(pac_2_tex);
	pacman[2][3].rotate(180);

    dead_0_tex.loadFromFile("sprites/pacman/d-0.png");
	dead_1_tex.loadFromFile("sprites/pacman/d-1.png");
	dead_2_tex.loadFromFile("sprites/pacman/d-2.png");
	dead_3_tex.loadFromFile("sprites/pacman/d-3.png");
	dead_4_tex.loadFromFile("sprites/pacman/d-4.png");
	dead_5_tex.loadFromFile("sprites/pacman/d-5.png");
	dead_6_tex.loadFromFile("sprites/pacman/d-6.png");
	dead_7_tex.loadFromFile("sprites/pacman/d-7.png");
	dead_8_tex.loadFromFile("sprites/pacman/d-8.png");
	dead_9_tex.loadFromFile("sprites/pacman/d-9.png");
	dead_10_tex.loadFromFile("sprites/pacman/d-10.png");

    dying[0].setTexture(dead_0_tex);
    dying[1].setTexture(dead_1_tex);
    dying[2].setTexture(dead_2_tex);
    dying[3].setTexture(dead_3_tex);
    dying[4].setTexture(dead_4_tex);
    dying[5].setTexture(dead_5_tex);
    dying[6].setTexture(dead_6_tex);
    dying[7].setTexture(dead_7_tex);
    dying[8].setTexture(dead_8_tex);
    dying[9].setTexture(dead_9_tex);
    dying[10].setTexture(dead_10_tex);

    // Bind ghost textures
    ghost_r_0_tex.loadFromFile("sprites/ghosts/r-0.png");
    ghosts[0][0].setTexture(ghost_r_0_tex);
    ghost_r_1_tex.loadFromFile("sprites/ghosts/r-1.png");
    ghosts[0][1].setTexture(ghost_r_1_tex);
    ghost_p_0_tex.loadFromFile("sprites/ghosts/p-0.png");
    ghosts[1][0].setTexture(ghost_p_0_tex);
    ghost_p_1_tex.loadFromFile("sprites/ghosts/p-1.png");
    ghosts[1][1].setTexture(ghost_p_1_tex);
    ghost_b_0_tex.loadFromFile("sprites/ghosts/b-0.png");
    ghosts[2][0].setTexture(ghost_b_0_tex);
    ghost_b_1_tex.loadFromFile("sprites/ghosts/b-1.png");
    ghosts[2][1].setTexture(ghost_b_1_tex);
    ghost_y_0_tex.loadFromFile("sprites/ghosts/y-0.png");
    ghosts[3][0].setTexture(ghost_y_0_tex);
    ghost_y_1_tex.loadFromFile("sprites/ghosts/y-1.png");
    ghosts[3][1].setTexture(ghost_y_1_tex);
    ghost_scared_0_tex.loadFromFile("sprites/ghosts/s-0.png");
    frightened_b[0].setTexture(ghost_scared_0_tex);
    ghost_scared_1_tex.loadFromFile("sprites/ghosts/s-1.png");
    frightened_b[1].setTexture(ghost_scared_1_tex);
    ghost_scared_2_tex.loadFromFile("sprites/ghosts/s-2.png");
    frightened_w[0].setTexture(ghost_scared_2_tex);
    ghost_scared_3_tex.loadFromFile("sprites/ghosts/s-3.png");
    frightened_w[1].setTexture(ghost_scared_3_tex);

     // Bind ghost eye textures
    eye_up_tex.loadFromFile("sprites/eyes/up.png");
    eyes[0].setTexture(eye_up_tex);
    eye_left_tex.loadFromFile("sprites/eyes/left.png");
    eyes[1].setTexture(eye_left_tex);
    eye_down_tex.loadFromFile("sprites/eyes/down.png");
    eyes[2].setTexture(eye_down_tex);
    eye_right_tex.loadFromFile("sprites/eyes/right.png");
    eyes[3].setTexture(eye_right_tex);


    // Bind UI textures
    num_0_tex.loadFromFile("sprites/ui/0.png");
	numbers[0].setTexture(num_0_tex);
    num_1_tex.loadFromFile("sprites/ui/1.png");
    numbers[1].setTexture(num_1_tex);
    num_2_tex.loadFromFile("sprites/ui/2.png");
	numbers[2].setTexture(num_2_tex);
    num_3_tex.loadFromFile("sprites/ui/3.png");
	numbers[3].setTexture(num_3_tex);
    num_4_tex.loadFromFile("sprites/ui/4.png");
	numbers[4].setTexture(num_4_tex);
    num_5_tex.loadFromFile("sprites/ui/5.png");
	numbers[5].setTexture(num_5_tex);
    num_6_tex.loadFromFile("sprites/ui/6.png");
	numbers[6].setTexture(num_6_tex);
    num_7_tex.loadFromFile("sprites/ui/7.png");
	numbers[7].setTexture(num_7_tex);
    num_8_tex.loadFromFile("sprites/ui/8.png");
	numbers[8].setTexture(num_8_tex);
    num_9_tex.loadFromFile("sprites/ui/9.png");
    numbers[9].setTexture(num_9_tex);
    score_200_tex.loadFromFile("sprites/ui/200.png");
    score_200_sprite.setTexture(score_200_tex);
    score_400_tex.loadFromFile("sprites/ui/400.png");
    score_400_sprite.setTexture(score_400_tex);
    score_800_tex.loadFromFile("sprites/ui/800.png");
    score_800_sprite.setTexture(score_800_tex);
    score_1600_tex.loadFromFile("sprites/ui/1600.png");
    score_1600_sprite.setTexture(score_1600_tex);
    ready_tex.loadFromFile("sprites/ui/ready.png");
    ready_sprite.setTexture(ready_tex);
    gameover_tex.loadFromFile("sprites/ui/gameover.png");
    gameover_sprite.setTexture(gameover_tex);
    life_tex.loadFromFile("sprites/ui/life.png");
    life_sprite.setTexture(life_tex);
    score_tex.loadFromFile("sprites/ui/score_tex.png");
    score_sprite.setTexture(score_tex);
    high_tex.loadFromFile("sprites/ui/high.png");
    high_sprite.setTexture(high_tex);
    score_100_tex.loadFromFile("sprites/ui/100.png");
    score_100_sprite.setTexture(score_100_tex);
    score_300_tex.loadFromFile("sprites/ui/300.png");
    score_300_sprite.setTexture(score_300_tex);

    // Fruit textures
    cherry_tex.loadFromFile("sprites/fruits/cherry.png");
    cherry_sprite.setTexture(cherry_tex);
    cherry_sprite.scale(0.5f, 0.5f);
    strawberry_tex.loadFromFile("sprites/fruits/strawberry.png");
    strawberry_sprite.setTexture(strawberry_tex);
    strawberry_sprite.scale(0.5f, 0.5f);
}