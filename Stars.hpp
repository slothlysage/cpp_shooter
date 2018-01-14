#ifndef STARS_HPP
# define STARS_HPP
# include "Piece.hpp"
# include <ctime>
# include <cstdlib>

class Stars {

  public:

    Stars( int nbStars, int rspeed, int x, int y );
		~Stars();
		Stars(Stars const & src);
		Stars	& operator=(Stars const & rhs);
    void move( void );
    void setX( int x );
    void setY( int y );

  private:

    Stars( void );
    void _deleteStars( void );
    void _render( int yChange );
    Piece **_stars;
    int _nbStars;
    int _renderSpeed;
    int _renderTime;
    int _x;
    int _y;
};

#endif