/* Copyright 2013 Brandon Edgren */

#include <vector>

#include "./CharacterController.h"

void CharacterController::CharacterAdd(Character::Ptr chr) {
  characters_.insert(chr);
}

void CharacterController::CharacterRmv(Character::Ptr chr) {
  characters_.erase(chr);
}
