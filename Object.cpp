#include "Object.hpp"

Object::Object( std::string sprite, int x, int y) :
  _sprite(sprite),
  _nbPieces(0),
  _height(1),
  _width(0),
  _x(x),
  _y(y)
{
  _createPieces();
}

Object::Object( void ) :
  _sprite("<=-"),
  _nbPieces(0),
  _height(1),
  _width(0),
  _x(10),
  _y(10)
{
  _createPieces();
  return ;
}

Object::~Object( void ) {
  return ;
}

Object::Object(Object const & src) {
  *this = src;
  return ;
}

Object & Object::operator=(Object const & rhs) {
  (void)rhs;
  return *this;
}

void Object::move( int x, int y ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->setX(_pieces[i]->getX() + x);
    _pieces[i]->setY(_pieces[i]->getY() + y);
  }
  _x += x;
  _y += y;
  return ;
}

void Object::draw( void ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->draw();
  }
  return ;
}

void Object::clear( void ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->clear();
  }
  return ;
}

void Object::_createPieces( void ) {
  for (int i = 0; i < (int)_sprite.length(); i++) {
      _width++;
      if (_sprite[i] != '.' && _sprite[i] != '\n') {
        _nbPieces++;
      }
      if (_sprite[i] == '\n') {
        _width = 0;
        _height++;
      }
  }
  _width /= 2;
  _height /= 2;
  _pieces = new Piece*[_nbPieces];
  int xPos = 0;
  int yPos = 0;
  int j = 0;
  for (int i = 0; i < (int)_sprite.length(); i++) {
    if (_sprite[i] != '.' && _sprite[i] != '\n') {
        std::string sprite = "";
        sprite += _sprite[i];
        _pieces[j] = new Piece(sprite, 
        _x + (yPos - _height),
        _y + (xPos - _width), 0, 0);
        j++;
    }
    if (_sprite[i] == '\n') {
      yPos++;
      xPos = 0;
    } else {
      xPos++;
    }
  }
}

void Object::setX( int x ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->setX((_pieces[i]->getX() - _x) + x);
  }
  _x = x;
  return ;
}

void Object::setY( int y ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->setY((_pieces[i]->getY() - _y) + y);
  }
  _y = y;
  return ;
}

bool Object::isObjectCollision( Object const & object ) {
  for (int i = 0; i < object._nbPieces; i++) {
    if (isCollision(object._pieces[i]->getX(), object._pieces[i]->getY())) {
      return true;
    }
  }
  return false;
}

bool Object::isCollision( int x, int y ) {
  for (int i = 0; i < _nbPieces; i++) {
    if (
      _pieces[i]->getX() == x &&
      _pieces[i]->getY() == y
    ) 
    {
      return true;
    }
  }
  return false;
}

void Object::setxy( int x, int y ) {
  for (int i = 0; i < _nbPieces; i++) {
    _pieces[i]->setX((_pieces[i]->getX() - _x) + x);
    _pieces[i]->setY((_pieces[i]->getY() - _y) + y);
  }
  _x = x;
  _y = y;
  return ;
}

int Object::getX( void ) const {
  return _x;
}

int Object::getY( void ) const {
  return _y;
}

int Object::getHeight( void ) const {
  return _height;
}

int Object::getWidth( void ) const {
  return _width;
}