/* Copyright 2013 Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_

#include <SFML\Graphics.hpp>

#include <set>

#include "./Character.h"

class CharacterController {
 public:
  explicit CharacterController() {}
  virtual ~CharacterController() {}

  virtual void CharacterAdd(Character::Ptr chr);
  virtual void CharacterRmv(Character::Ptr chr);

  //virtual void ProcessEvent(sf::Event event) = 0;
  //virtual void Tick() = 0;

 protected:
  std::set<Character::Ptr> characters_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_
