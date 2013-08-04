/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_UTIL_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_UTIL_H_

#include <stdint.h>

#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

uint8_t CodeToChar(sf::Keyboard::Key code);

bool isInf(float x);

float AngleOf(b2Vec2 vec);
float RadiansOf(b2Vec2 vec);

float RadToDeg(float rad);
float DegToRad(float deg);

b2Vec2 RotatedVector(const b2Vec2 &vec, float rad);

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_UTIL_H_
