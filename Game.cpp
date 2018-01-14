/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:54:07 by sjones            #+#    #+#             */
/*   Updated: 2018/01/13 15:45:44 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : 
	_time(clock()), 
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
	for (int i = 0; i < MAX_ENEMIES; i++) {
		_enemies[i].setCrash(true);
	}
	return ;
}

Game::~Game() {
	endwin();
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
	_end = false;
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
		if (_enemies[i].isCrash()) {
			_enemies[i].setxy(((std::rand() % (_rows - 4)) + 3), (_cols - _enemies[i].getIcon().length() - 1));
			_enemies[i].setCrash(false);
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

	attron(COLOR_PAIR(3));
	resetParams();
	for (int i = 1; i < _cols - 1; i++) {
		mvaddch(2,i,ACS_HLINE); }
	w = (_cols / 8) - 1;
	mvprintw(1,1,"%*s:%-*d",w,"Lives",w,player->getLives());
	addch(ACS_VLINE);
	printw("%*s:%-*d",w,"Score",w,player->getScore());
	addch(ACS_VLINE);
	printw("%*s:%-*d",w,"Timer",w,(clock() - _time) / CLOCKS_PER_SEC);
	addch(ACS_VLINE);
	printw("%*s:%-*d",w,"FPS",w,FPS);
	mvaddch(2,0,ACS_LTEE);
	mvaddch(2,_cols - 1,ACS_RTEE);
	mvaddch(0,2*w+2,ACS_TTEE);
	mvaddch(0,4*w+4,ACS_TTEE);
	mvaddch(0,6*w+6,ACS_TTEE);
	mvaddch(2,2*w+2,ACS_BTEE);
	mvaddch(2,4*w+4,ACS_BTEE);
	mvaddch(2,6*w+6,ACS_BTEE);
	attroff(COLOR_PAIR(3));
}

void	Game::move(Player *player, int ch) {
	player->clear();
	if (ch == UP && player->getX() > 3) {
		player->setxy(player->getX() - 1, player->getY());
	}
	if (ch == DOWN && player->getX() < _rows - 2) {
		player->setxy(player->getX() + 1, player->getY());
	}
	if (ch == LEFT && player->getY() > 1) {
		player->setxy(player->getX(), player->getY() - 1);
	}
	if (ch == RIGHT && 
			player->getY() < (int)(_cols - player->getIcon().length() - 1))
	{
		player->setxy(player->getX(), player->getY() + 1);
	}
	if (ch == SPACE) {
		player->shoot();
	}
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
		if (!_enemies[i].isCrash()) {
			_enemies[i].clear();
			_enemies[i].setY(_enemies[i].getY() - 1);
			if (_enemies[i].getY() <= 2) {
				_enemies[i].setCrash(true);
			} else {
				_enemies[i].draw();
			}
		}
	}
}

bool Game::_playerEnemyCollision(Player * player) {
	for (int i; i < MAX_ENEMIES; i++) {
		if (
			!_enemies[i].isCrash() &&
			_playerCollision(
				_enemies[i].getX(), 
				_enemies[i].getY(), 
				player
			)
		) 
		{
			_enemies[i].setCrash(true);
			_enemies[i].explode();
			return true;
		}
	}
	return true;
}

bool Game::_playerCollision(int x, int y, Player * player) {
	if (
		(player->getX() - x == 0) && 
		((y - player->getY() <= 4) &&
		 (y - player->getY() >= 0))
	) {
		player->blink(11);
		player->setLives(player->getLives() - 1);
		return true;
	} else {
		return false;
	}
}

bool Game::_enemyCollision(int x, int y) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!_enemies[i].isCrash()) {
			if (_enemies[i].getX() == x && (_enemies[i].getY() - y <= 1)) {
				_enemies[i].setCrash(true);
				_enemies[i].explode();
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
