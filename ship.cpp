/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:37:59 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 17:41:16 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ship.hpp"

Ship::Ship() : Piece((char*)"<-", 0, 0, 0, 0) {
	for (int i = 0; i < MAX_BULLETS; i++){
		_bullets[i].setIcon((char *)"~");
		_bullets[i].setCrash(true);
	}
}

Ship::~Ship() {}

Ship::Ship(Ship const & other) {
	this->operator=(other);
}

Ship	&Ship::operator=(Ship const & other) {
	if (this == &other)
		return *this;
	this->_x = other._x;
	this->_y = other._y;
	this->_icon = other._icon;
	return *this;
}

void Ship::shoot() {
	int     i;

	i = 0;
	while (i < MAX_BULLETS)
	{
		if (_bullets[i].isCrash())
		{
			_bullets[i].setxy(_x + strlen(_icon), _y);
			_bullets[i].setCrash(false);
			i = MAX_BULLETS;
		}
		else
			i++;
	}
}
