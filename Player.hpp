/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:43:32 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:39:07 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "Ship.hpp"

class Player : virtual public Ship {
	
	public:

		Player();
		~Player();
		Player(Player const & other);
		Player	&operator=(Player const & other);
		void	reset();
		void	draw();
		int		getLife() const;
		int		getScore() const;
		void	setScore(int score);
	
	private:
	
		int		_lives;
		int		_score;

};

#endif
