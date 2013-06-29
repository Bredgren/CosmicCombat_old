/* Copyright 2013 Brandon Edgren */

#include "./Util.h"

uint8_t CodeToChar(sf::Keyboard::Key code) {
  switch (code) {
  case sf::Keyboard::A:
    return 'a';
  case sf::Keyboard::B:
    return 'b';
  case sf::Keyboard::C:
    return 'c';
  default:
    break;
  }
}
