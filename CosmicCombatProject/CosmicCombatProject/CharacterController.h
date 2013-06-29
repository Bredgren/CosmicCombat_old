/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_

#include <SFML\Graphics.hpp>

#include <vector>

#include "./Character.h"

class CharacterController {
 public:
  explicit CharacterController() {}
  virtual ~CharacterController(void) {}

  void AddCharacter(Character *chr);
  void RemoveCharacter(Character *chr);

  virtual void ProcessEvent(sf::Event event) = 0;
  virtual void Tick() = 0;

 private:
  std::vector<Character*> characters_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTERCONTROLLER_H_
