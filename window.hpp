/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 22:54:57 by sjones            #+#    #+#             */
/*   Updated: 2018/01/11 22:02:36 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP
# include <ncurses.h>

class			Window
{
	public:
		Window();
		~Window();
		Window(int height, int width, int startx, int starty);
		Window	operator=(Window const & other);
		Window(Window const & other);
		void	create();
		void	refresh();
		void	destroy();
		void	setStart(int startx, int starty);
		WINDOW	*getWindow();
	protected:
		WINDOW	*_win;
		int		_height;
		int		_width;
		int		_startx;
		int		_starty;
};

#endif
