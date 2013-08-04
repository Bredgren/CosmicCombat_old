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
  case sf::Keyboard::D:
    return 'd';
  case sf::Keyboard::E:
    return 'e';
  case sf::Keyboard::F:
    return 'f';
  case sf::Keyboard::G:
    return 'g';
  default:
    return code;
    break;
  }
}

bool isInf(float x) {
    return x > FLT_MAX || x < -FLT_MAX;
}

float AngleOf(b2Vec2 vec) {
  float angle_r = RadiansOf(vec);
  return 180.0f / 3.14f * angle_r;
}

float RadiansOf(b2Vec2 vec) {
  static b2Vec2 vertical(0, -1);
  float dot = (vertical.x * vec.x) + (vertical.y * vec.y);
  float angle_r = acos(dot / (vertical.Length() * vec.Length()));
  return angle_r;
}

float RadToDeg(float rad) {
  return rad * 180.0f / 3.14f;
}

float DegToRad(float deg) {
  return deg * 3.14f / 180.0f;
}

b2Vec2 RotatedVector(const b2Vec2 &vec, float rad) {
  float ca = cos(rad);
  float sa = sin(rad);
  float x = vec.x * ca - vec.y * sa;
  float y = vec.x * sa + vec.y * ca;
  return b2Vec2(x, y);
}