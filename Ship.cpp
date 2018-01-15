/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ship.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:37:59 by sjones            #+#    #+#             */
/*   Updated: 2018/01/14 18:52:31 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ship.hpp"


Ship::Ship() :
	Object("<-=", 10, 10)
{
	for (int i = 0; i < MAX_BULLETS; i++){
		_bullets[i].setIcon("~");
		_bullets[i].setCrash(true);
	}
}

Ship::Ship(std::string sprite, int x, int y) :
	Object(sprite, x, y)
{
	for (int i = 0; i < MAX_BULLETS; i++){
	_bullets[i].setIcon("~");
	_bullets[i].setCrash(true);
	}
}

Ship::~Ship() {
	return ;
}

Ship::Ship(Ship const & other) :

	Object(
		other._sprite,
		other._x,
		other._y
	)
{
	return ;
}

Ship	&Ship::operator=(Ship const & other) {
	if (this == &other) {
		return *this;
	}
	this->_x = other._x;
	this->_y = other._y;
	this->_sprite = other._sprite;
	return *this;
}

void Ship::shoot() {
	int     i;

	i = 0;
	while (i < MAX_BULLETS) {
		if (_bullets[i].isCrash()) {
			system("afplay sfx/laser.wav &");
			_bullets[i].setxy(_x, _y + 1);
			_bullets[i].setCrash(false);
			i = MAX_BULLETS;
		}
		else {
			i++;
		}
	}
}

void Ship::explode() {
	clear();
	system("afplay sfx/explode.wav &");
	attron(COLOR_PAIR(5));
	mvprintw(_x,_y, "*.*.*");
	mvprintw(_x + 1 ,_y + 1, "*.*");
	mvprintw(_x - 1 ,_y + 1, "*.*");
	attroff(COLOR_PAIR(5));
}

void	Ship::draw() {
	attron(COLOR_PAIR(2));
	Object::draw();
	attroff(COLOR_PAIR(2));
}

Piece	Ship::getBullet(int i) {
	if (i < MAX_BULLETS)
		return _bullets[i];
	return _bullets[0];
}

void	Ship::setBullet(int i, int x, int y, bool crash) {
	if (i < MAX_BULLETS) {
		_bullets[i].setxy(x, y);
		_bullets[i].setCrash(crash);
	}
}

void	Ship::setCrash( bool crash ) {
	_crash = crash;
	return ;
}

bool	Ship::isCrash( void ) const {
	return _crash;
}
