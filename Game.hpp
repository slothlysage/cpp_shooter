/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:54:20 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:38:39 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP
# include <ncurses.h>
# include <ctime>
# include <string>
# include <string.h>
# include "Player.hpp"
# define MAX_ENEMIES 100

enum			keys
{
	ESC = 27,
	SPACE = 32,
	UP = 259,
	DOWN = 258,
	LEFT = 260,
	RIGHT = 261
};

class			Game
{
	public:
		Game();
		~Game();
		Game(Game const & other);
		Game	&operator=(Game const & other);
		void	resetParams();
		void	resetGame(Player *player);
		void	drawBorder();
		void	loadScreen();
		bool	menu();
		void	gameOver();
		void	score(Player *player, int FPS);
		void	move(Player *player, int ch);
		void	checkEnd(Player *player);
		int		getRows();
		int		getCols();
		bool	isEnd();
	private:
//		Ship	*enemies[100];
		clock_t	_time;
		int		_rows;
		int		_cols;
		bool	_end;
};

#endif