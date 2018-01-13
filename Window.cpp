/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 23:00:30 by sjones            #+#    #+#             */
/*   Updated: 2018/01/11 00:05:06 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

Window::Window() {
	int x;
	int y;

	getmaxyx(stdscr,x,y);
	Window(x,y,0,0);
}

Window::~Window() {}

Window::Window(int height, int width, int startx, int starty) :
	_win(NULL), _height(height), _width(width), _startx(startx), _starty(starty) {}

Window	Window::operator=(Window const & other) {
	_win = NULL;
	_height = other._height;
	_width = other._width;
	_startx = other._startx;
	_starty = other._starty;
	return *this;
}

Window::Window(Window const & other) {
	Window(other._height, other._width, other._startx, other._starty);
}

void	Window::create() {
	if (!_win)
		_win = newwin(_height, _width, _startx, _starty);
}

void	Window::refresh() {
	if (_win)
		wrefresh(_win);
}

void	Window::destroy() {
	if (_win) {
		delwin(_win);
		_win = NULL;
	}
}

void	Window::setStart(int startx, int starty) {
	_startx = startx;
	_starty = starty;
}

WINDOW	*Window::getWindow() {
	return _win;
}
