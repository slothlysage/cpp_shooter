/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:34:45 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:21:08 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHIP_HPP
# define SHIP_HPP
# include "piece.hpp"
# define MAX_BULLETS 10

class Ship : virtual public Piece {

	public:
	
		Ship();
		~Ship();
		Ship(Ship const & other);
		Ship	&operator=(Ship const & other);
		void	shoot();
		void	draw();
		Piece	getBullet(int i);
		void	setBullet(int i, int x, int y, bool crash);

	protected:

		Piece	_bullets[MAX_BULLETS];

};

#endif
