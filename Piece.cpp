/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:33:54 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 20:52:39 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Piece.hpp"

Piece::Piece() {
	char icon[] = "*";
	Piece(icon, 0, 0, 0, 0);
}

Piece::Piece(std::string icon, int x, int y, int rtime, int rspeed) :
	_icon(icon), 
	_x(x), 
	_y(y), 
	_crash(false), 
	_rtime(rtime), 
	_rspeed(rspeed)
{
	return ;
}

Piece::~Piece() {}

Piece::Piece(Piece const & other) {
	this->_icon = other._icon;
	this->_x = other._x;
	this->_y = other._y;
	this->_crash = other._crash;
	this->_rtime = other._rtime;
	this->_rspeed = other._rspeed;
	return ;
}

Piece	&Piece::operator=(Piece const & other) {
	if (this == &other) {
		return *this;
	}
	this->_icon = other._icon;
	this->_x = other._x;
	this->_y = other._y;
	this->_crash = other._crash;
	this->_rtime = other._rtime;
	this->_rspeed = other._rspeed;
	return *this;
}

void	Piece::draw() {
	mvprintw(_x, _y, "%s", _icon.c_str());
}

void 	Piece::drawxy(int x, int y) {
	mvprintw(x, y, "%s", _icon.c_str());
}

void	Piece::clear() {
	for (int i = 0; i < (int)_icon.length(); i++) {
		mvaddch(_x,_y + i,' ');
	}
}

void	Piece::setIcon(std::string icon) {
	_icon = icon;
}

void	Piece::setxy(int x, int y) {
	_x = x;
	_y = y;
}

void	Piece::setX(int x) {
	_x = x;
}

void	Piece::setY(int y) {
	_y = y;
}

void	Piece::setCrash(bool crash) {
	_crash = crash;
}

void	Piece::setRtime(int rtime) {
	_rtime = rtime;
}

void	Piece::setRspeed(int rspeed) {
	_rspeed = rspeed;
}

std::string Piece::getIcon() {
	return _icon;
}

int		Piece::getX() {
	return _x;
}

int		Piece::getY() {
	return _y;
}

bool	Piece::isCrash() {
	return _crash;
}

int		Piece::getRtime() {
	return _rtime;
}

int		Piece::getRspeed() {
	return _rspeed;
}
