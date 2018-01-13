/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:46:12 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:40:12 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player() : 
	Piece(">==-", 5, 2, 0, 0), 
	_lives(5), 
	_score(0) 
{
	return ;
}

Player::~Player() {
	return ;
}

Player::Player(Player const & other) : 
	Piece(
		other._icon, 
		other._x, 
		other._y, 
		other._rtime, 
		other._rspeed
	),
	_lives(other._lives),
	_score(other._score)
{
	return ;
}

Player	&Player::operator=(Player const & other) {
	if (this == &other) {
		return *this;
	}
	this->_lives = other._lives;
	this->_score = other._score;
	this->_icon = other._icon;
	this->_x = other._x;
	this->_y = other._y;
	this->_rtime = other._rtime;
	this->_rspeed = other._rspeed;

	return *this;
}

void	Player::reset() {
	setxy(5,2);
	_lives = 5;
	_score = 0;
}

void	Player::draw() {
	attron(COLOR_PAIR(1));
	Piece::draw();
	attroff(COLOR_PAIR(1));
}

int		Player::getLife() {
	return _lives;
}

int		Player::getScore() {
	return _score;
}
