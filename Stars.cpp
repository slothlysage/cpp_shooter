#include "Stars.hpp"

Stars::Stars( void ) {
  return ;
}

Stars::Stars( int nbStars, int renderSpeed, int x, int y ) :
  _nbStars(nbStars),
  _renderSpeed(renderSpeed),
  _renderTime(0),
  _x(x),
  _y(y)
{
  std::srand(std::time(0));
  _stars = new Piece*[nbStars];
  for (int i = 0; i < nbStars; i++) {
    _stars[i] = new Piece("*", 
												((std::rand() % (x - 4)) + 3), 
												std::rand() % y, 
												0, 
												0);
  }
  return ;
}

Stars::Stars( Stars const & src ) :
  _nbStars(src._nbStars),
  _renderSpeed(src._renderSpeed)
{
  *this = src;
  return ;
}

Stars	& Stars::operator=( Stars const & rhs ) {
  _deleteStars();
  _stars = new Piece*[rhs._nbStars];
  for (int i = 0; i < rhs._nbStars; i++) {
    _stars[i] = new Piece(*(rhs._stars[i]));
  }
  _nbStars = rhs._nbStars;
  _renderSpeed = rhs._renderSpeed;
  return *this;
}

Stars::~Stars( void ) {
  _deleteStars();
}

void Stars::_deleteStars( void ) {
  for (int i = 0; i < _nbStars; i++) {
    delete _stars[i];
  }
  if (_stars) {
    delete[] _stars;
  }
  _stars = NULL;
  _nbStars = 0;
  return ;
}

void Stars::setX( int x ) {
  _x = x;
  return ;
}

void Stars::setY( int y ) {
  _y = y;
  return ;
}

void Stars::move( void ) {
  if (_renderTime < _renderSpeed) {
    _renderTime++;
    if (_renderTime % 2) {
      _render(0);      
    } else {
      _render(0);
    }
  } else {
    _render(-1);
    _renderTime = 0;
  }
  return ;
}

void Stars::_render( int yChange ) {
	attron(COLOR_PAIR(4));
	for (int i = 0; i < _nbStars; i++) {
    _stars[i]->clear();
    _stars[i]->setY(_stars[i]->getY() + yChange);
    if (_stars[i]->getY() < 2) {
      _stars[i]->setY(_y - 2);
      _stars[i]->setX((std::rand() % (_x - 3)) + 2);
    }
    _stars[i]->draw();
  }
	attroff(COLOR_PAIR(4));
  return ;
}
