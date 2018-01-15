/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:46:12 by sjones            #+#    #+#             */
/*   Updated: 2018/01/13 13:24:00 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player() :
	Ship("|\\____\n|@____)", 8, 8),
	_lives(5),
	_score(0),
	_blinkCount(0),
	_blinks(0)
{
	return ;
}

Player::~Player() {
	return ;
}

Player::Player(Player const & other) :
	Ship(
		other._sprite,
		other._x,
		other._y
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
	this->_sprite = other._sprite;
	this->_x = other._x;
	this->_y = other._y;
	this->_blinks = other._blinks;
	this->_blinkCount = other._blinkCount;

	return *this;
}

void	Player::reset() {
	setxy(5,2);
	_lives = 5;
	_score = 0;
	_blinks = 0;
	_blinkCount = 0;
}

void	Player::draw() {
	if (_lives > 0) {
		attron(COLOR_PAIR(1));
		if (_blinks > 0) {
			_blinkCount++;
			if (_blinkCount > 10) {
				_blinkCount = 0;
				_blinks--;
			}
		}
		if (!(_blinks % 2)) {
			Object::draw();
		}
		attroff(COLOR_PAIR(1));
	}
}

int		Player::getLives() const {
	return _lives;
}

void Player::setLives(int lives) {
		system("afplay sfx/life.wav &");
	_lives = lives;
	return ;
}

void	Player::setScore(int score) {
	_score = score;
	return ;
}

int		Player::getScore() const {
	return _score;
}

void	Player::blink(int times) {
	_blinks = times;
	return ;
}
