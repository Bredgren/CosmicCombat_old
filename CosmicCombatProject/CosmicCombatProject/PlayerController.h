/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_

#include <string>
#include <set>

#include "./Character.h"
#include "./CharacterController.h"

class PlayerController : public CharacterController {
 public:
  static PlayerController &Instance() {
    static PlayerController inst;
    return inst;
  }

  void CharacterAdd(Character::Ptr chr);
  Character::Ptr Character() const { return *characters_.begin(); }

  void ProcessEvent(sf::Event event);

  void Tick(sf::Window *window);

 private:
   PlayerController() {}
   PlayerController(const PlayerController&);
   void operator=(PlayerController&);

   bool left_down_;
   bool right_down_;

   int32 mouse_x_;
   int32 mouse_y_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_
