/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:46:12 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 20:34:48 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.hpp"

Player::Player() : Piece((char*)">==-",5,1,0,0), _lives(5), _score(0) {}

Player::~Player() {}

Player::Player(Player const & other) {
	this->operator=(other);
}

Player	&Player::operator=(Player const & other) {
	if (this == &other)
		return *this;
	this->_lives = other._lives;
	this->_score = other._score;
	this->_icon = other._icon;
	this->_x = other._x;
	this->_y = other._y;
	return *this;
}

void	Player::draw() {
	attron(COLOR_PAIR(1));
	mvprintw(_x, _y, "%s", _icon);
	attroff(COLOR_PAIR(1));
}

int		Player::getLife() {
	return _lives;
}

int		Player::getScore() {
	return _score;
}
