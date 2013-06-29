/* Copyright 2013 Brandon Edgren */

#include <vector>

#include "./CharacterController.h"

void CharacterController::AddCharacter(Character *chr) {
  characters_.push_back(chr);
}

void CharacterController::RemoveCharacter(Character *chr) {
  std::vector<Character*>::iterator it;
  for (; it != characters_.end(); it++)
    if (*it = chr) break;

  if (*it = chr)
    characters_.erase(it);
}
