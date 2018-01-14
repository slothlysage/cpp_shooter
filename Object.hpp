#ifndef OBJECT_HPP
# define OBJECT_HPP
# include "Piece.hpp"
# include <ctime>
# include <cstdlib>

class Object {

  public:

    Object( std::string sprite, int x, int y );
		~Object( void );
		Object(Object const & src);
		Object & operator=( Object const & rhs );
    bool isObjectCollision( Object const & object );
    bool isCollision( int x, int y );
    void move( int x, int y );
    void clear( void );
    void draw( void );
    void setY( int y );
    void setX( int x );
    void setxy( int x, int y);
    int getX( void ) const;
    int getY( void ) const;
    int getHeight( void ) const;
    int getWidth( void ) const;

  protected:

    Object( void );
    void _createPieces( void );
    Piece **_pieces;
    std::string _sprite;
    int _nbPieces;
    int _height;
    int _width;
    int _renderSpeed;
    int _renderTime;
    int _x;
    int _y;

};

#endif