/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 20:34:45 by sjones            #+#    #+#             */
/*   Updated: 2018/01/13 15:13:10 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHIP_HPP
# define SHIP_HPP
# include "Piece.hpp"
# include "Object.hpp"
# define MAX_BULLETS 10

class Ship : public Object {

	public:
	
		Ship();
		Ship(std::string sprite, int x, int y);
		~Ship();
		Ship( Ship const & other );
		Ship	&operator=( Ship const & other );
		void	shoot();
		void	draw();
		void	explode();
		Piece	getBullet( int i );
		void	setBullet( int i, int x, int y, bool crash );
		void	setCrash( bool crash );
		bool	isCrash( void ) const;

	protected:

		bool _crash;
		Piece	_bullets[MAX_BULLETS];

};

#endif
