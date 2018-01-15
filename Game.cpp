/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:54:07 by sjones            #+#    #+#             */
/*   Updated: 2018/01/14 19:00:33 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() :
	_time(clock()),
	_timer(0),
	_end(false)
{
	initscr();
	cbreak();
	noecho();
	timeout(0);
	curs_set(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, _rows, _cols);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	std::srand(std::time(0));

	_junkShips = new Ship*[MAX_ENEMIES];
	for (int i = 0; i < MAX_ENEMIES; i++) {
		_junkShips[i] = new Ship("..___/|__\n.\\______|(`>", 0, 0);
		_junkShips[i]->setCrash(true);
	}
	_stars = new Stars(MAX_STARS, 15, _rows, _cols);
	return ;
}

Game::~Game() {
	endwin();
	system("killall afplay");
	return ;
}

Game::Game(Game const & other) :
	_time(other._time),
	_rows(other._rows),
	_cols(other._cols),
	_end(other._end)
{
	return ;
}

Game	&Game::operator=(Game const & other) {
	if (this == &other) {
		return *this;
	}
	this->_rows = other._rows;
	this->_cols = other._cols;
	this->_time = other._time;
	this->_end = other._end;
	return *this;
}

void	Game::resetParams() {
	getmaxyx(stdscr, _rows, _cols);
}

void	Game::resetGame(Player *player) {
	player->reset();
	_time = clock();
	_timer = 0;
	_end = false;
	system("killall afplay");
	system("afplay sfx/over2.wav &");
}

void  Game::addTimer() {
	_timer++;
	if (_timer % 15 == 0)
		system("afplay sfx/music.mp3 &");
}

void	Game::drawBorder() {
	attron(COLOR_PAIR(3));
	resetParams();
	for (int i = 1; i < _cols - 1; i++) {
		mvaddch(0,i,ACS_HLINE);
		mvaddch(_rows - 1,i,ACS_HLINE); }
	for (int i = 1; i < _rows - 1; i++) {
		mvaddch(i,0,ACS_VLINE);
		mvaddch(i,_cols - 1,ACS_VLINE); }
	mvaddch(0,0,ACS_ULCORNER);
	mvaddch(0,_cols - 1,ACS_URCORNER);
	mvaddch(_rows - 1,0,ACS_LLCORNER);
	mvaddch(_rows - 1,_cols - 1,ACS_LRCORNER);
	attroff(COLOR_PAIR(3));
}

void	Game::loadScreen() {
	drawBorder();
}

bool	Game::menu() {
	attron(COLOR_PAIR(3));
	std::string greeting = "Prepare to Die";
	std::string choices = "Press S to play or Q to quit";
	int ch;

	clear();
	drawBorder();
	mvprintw(((_rows / 2) - 1), ((_cols / 2) - (greeting.length() / 2)),"%s",greeting.c_str());
	mvprintw(((_rows / 2)), ((_cols / 2) - (choices.length() / 2)),"%s",choices.c_str());
	while (1) {
		ch = getch();
		if (ch == 's' || ch == 'S')
			return true;
		if (ch == 'q' || ch == 'Q')
			return false;
	}
	attroff(COLOR_PAIR(3));
	return false;
}

void	Game::gameOver() {
	std::string dead = "You Died...";

	clear();
	drawBorder();
	mvprintw(((_rows / 2)), ((_cols / 2) - (dead.length() / 2)),"%s",dead.c_str());
}

void	Game::spawn() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (_junkShips[i]->isCrash()) {
			_junkShips[i]->setX((std::rand() % (_rows - (_junkShips[i]->getHeight() + 5))) + 3 + _junkShips[i]->getHeight());
			_junkShips[i]->setY(_cols - (_junkShips[i]->getWidth()));
			_junkShips[i]->setCrash(false);
			break;
		}
	}
}

void Game::alignPlayer(Player * player) {
	if (player->getX() > _rows) {
		player->clear();
		player->setX(_rows - 2);
		player->draw();
	}
}

void	Game::score(Player *player, int FPS)
{
	int w;

	resetParams();
	w = (_cols / 8) - 1;
	mvprintw(1,1,"%*s:%-*d ",w,"Lives",w,player->getLives());
	printw("%*s:%-*d ",w,"Score",w,player->getScore());
	printw("%*s:%-*d ",w,"Timer",w,_timer);
	printw("%*s:%-*d", w,"FPS",w,FPS);
	attron(COLOR_PAIR(3));
	for (int i = 1; i < _cols - 1; i++) {
		mvaddch(2,i,ACS_HLINE); }
	mvaddch(2,0,ACS_LTEE);
	mvaddch(2,_cols - 1,ACS_RTEE);
	mvaddch(1,_cols - 1,ACS_VLINE);
	mvaddch(0,2*w+2 ,ACS_TTEE);
	mvaddch(0,4*w+ 4,ACS_TTEE);
	mvaddch(0,6*w +6,ACS_TTEE);
	mvaddch(1,2*w+2 ,ACS_VLINE);
	mvaddch(1,4*w+ 4,ACS_VLINE);
	mvaddch(1,6*w +6,ACS_VLINE);
	mvaddch(2,2*w+2,ACS_BTEE);
	mvaddch(2,4*w+4,ACS_BTEE);
	mvaddch(2,6*w+6,ACS_BTEE);
	attroff(COLOR_PAIR(3));
}

void	Game::move(Player *player, int ch) {
	player->clear();
	if (ch == UP && player->getX() > 4) {
		player->move(-1, 0);
	}
	if (ch == DOWN && player->getX() < _rows - 2) {
		player->move(1, 0);
	}
	if (ch == LEFT && player->getY() > 4) {
		player->move(0, -1);
	}
	if (ch == RIGHT &&
			player->getY() < (int)(_cols - (player->getWidth() * 2) - 1))
	{
		player->move(0, 1);
	}
	if (ch == SPACE) {
		player->shoot();
	}
	_stars->move();
	_stars->setX(_rows);
	_stars->setY(_cols);
	_playerEnemyCollision(player);
	player->draw();
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!player->getBullet(i).isCrash()) {
			Piece bullet = player->getBullet(i);
			bullet.clear();
			if (_enemyCollision(bullet.getX(), bullet.getY() + 1)) {
					player->setScore(player->getScore() + 1);
					player->setBullet(i,0,0,true);
			} else if (bullet.getY() >= _cols - 2) {
					player->setBullet(i,0,0,true);
			} else {
				player->setBullet(i, player->getBullet(i).getX(), (player->getBullet(i).getY() + 1), false);
				player->getBullet(i).draw();
			}
		}
	}

	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!_junkShips[i]->isCrash()) {
			_junkShips[i]->clear();
			_junkShips[i]->move(0, -1);
			if (_junkShips[i]->getY() <= 2) {
				_junkShips[i]->setCrash(true);
			} else {
				_junkShips[i]->draw();
			}
		}
	}
}

bool Game::_playerEnemyCollision(Player * player) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (
			!_junkShips[i]->isCrash() &&
			player->isObjectCollision(*(_junkShips[i]))
		)
		{
			player->blink(11);
			player->setLives(player->getLives() - 1);
			_junkShips[i]->setCrash(true);
			_junkShips[i]->explode();
			return true;
		}
	}
	return true;
}

bool Game::_playerCollision(int x, int y, Player * player) {
	if (player->isCollision(x, y)) {
		player->blink(11);
		player->setLives(player->getLives() - 1);
		return true;
	} else {
		return false;
	}
}

bool Game::_enemyCollision(int x, int y) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!_junkShips[i]->isCrash()) {
			if (_junkShips[i]->isCollision(x, y)) {
				_junkShips[i]->setCrash(true);
				_junkShips[i]->explode();
				return true;
			}
		}
	}
	return false;
}

void	Game::checkEnd(Player *player) {
	if (player->getLives() == 0)
		_end = true;
}

int		Game::getRows() {
	return _rows;
}

int		Game::getCols() {
	return _cols;
}

bool	Game::isEnd() {
	return _end;
}
