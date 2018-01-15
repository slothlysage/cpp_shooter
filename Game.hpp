/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:54:20 by sjones            #+#    #+#             */
/*   Updated: 2018/01/13 15:50:20 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP
# include <ncurses.h>
# include <ctime>
# include <string>
# include <cstdlib>
# include "Player.hpp"
# include "Stars.hpp"
# include "Ship.hpp"
# define MAX_ENEMIES 100
# define MAX_STARS 20

enum			keys {
	ESC = 27,
	SPACE = 32,
	UP = 259,
	DOWN = 258,
	LEFT = 260,
	RIGHT = 261
};

class				Game {

	public:

		Game();
		~Game();
		Game(Game const & other);
		Game	&operator=(Game const & other);
		void	resetParams();
		void	resetGame(Player *player);
		void  addTimer();
		void	drawBorder();
		void	loadScreen();
		bool	menu();
		void	gameOver();
		void	spawn();
		void	score(Player *player, int FPS);
		void	move(Player *player, int ch);
		void	checkEnd(Player *player);
		int		getRows();
		int		getCols();
		bool	isEnd();
		void alignPlayer(Player * player);

	private:

		Ship		**_junkShips;
		Stars		*_stars;
		bool 		_playerEnemyCollision(Player * player);
		bool 		_enemyCollision(int x, int y);
		bool 		_playerCollision(int x, int y, Player * player);
		clock_t	_time;
		int			_timer;
		int			_rows;
		int			_cols;
		bool		_end;

};

#endif
