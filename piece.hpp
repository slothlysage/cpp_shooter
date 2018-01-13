/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:20:53 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 20:52:49 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIECE_HPP
# define PIECE_HPP
# include <ncurses.h>
# include <string.h>

class			Piece
{
	public:
		Piece();
		Piece(char *icon, int x, int y, int rtime, int rspeed);
		~Piece();
		Piece(Piece const & other);
		Piece	&operator=(Piece const & other);
		void	draw();
		void	clear();
		void	setIcon(char *icon);
		void	setxy(int x, int y);
		void	setX(int x);
		void	setY(int y);
		void	setCrash(bool crash);
		void	setRtime(int rtime);
		void	setRspeed(int rspeed);
		char	*getIcon();
		int		getX();
		int		getY();
		bool	isCrash();
		int		getRtime();
		int		getRspeed();
	protected:
		char	*_icon;
		int		_x;
		int		_y;
		bool	_crash;
		int		_rtime;
		int		_rspeed;
};

#endif
