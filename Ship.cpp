/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:37:59 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:22:00 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ship.hpp"

Ship::Ship() : 
	Piece("<-", 0, 0, 0, 0) 
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
	Piece(
		other._icon, 
		other._x, 
		other._y, 
		other._rtime, 
		other._rspeed
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
	this->_icon = other._icon;
	this->_rtime = other._rtime; 
	this->_rspeed = other._rspeed;
	return *this;
}

void Ship::shoot() {
	int     i;

	i = 0;
	while (i < MAX_BULLETS)
	{
		if (_bullets[i].isCrash())
		{
			_bullets[i].setxy(_x, _y + strlen(_icon));
			_bullets[i].setCrash(false);
			i = MAX_BULLETS;
		}
		else
			i++;
	}
}

void	Ship::draw() {
	attron(COLOR_PAIR(2));
	Piece::draw();
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
		_bullets[i].setCrash(crash); }
}
