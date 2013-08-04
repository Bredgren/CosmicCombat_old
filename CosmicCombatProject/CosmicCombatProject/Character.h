/* Copyright 2013 Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_

#include <Box2D\Box2D.h>

#include <string>

#include "./Energy.h"
#include "./Planet.h"

class CharacterController;

using std::string;

/// Represents a game character.
/**
    Manages data and behavior common to all NPCs and player controlled
    characters.
 */
class Character {
 public:
  typedef Character* Ptr;
  /// Types used to distinguish characters.
  //enum Type {
  //  kDefalut
  //};

  /// Creates a new character.
  /**
      @param name the name of the character.
      @param type the type of character.
      @param start_energy the character's starting maximum energy.
   */
  Character(string name, float start_energy = 100.0f);
  virtual ~Character(void);

  //void ControllerIs(CharacterController *controller);

  //void TargetPosition() const { return targetPos_; }
  void TargetPositionIs(b2Vec2 pos);
  
  b2Body *Body() const { return body_; }
  void BodyIs(b2Body *body);

  Planet::Ptr ClosestPlanet();
  void ClosestPlanetIs(Planet::Ptr planet);

  //bool flying() const { return flying_; }

 private:
  string name_;
  //Type type_;
  Energy energy_;
  b2Body *body_;
  CharacterController *controller_;
  Planet::Ptr closest_planet_;
  //Attack attacks_[x];
  //ComboTracker combo_tracker_;

  //b2World *world_;

  //b2MouseJoint *target_;

  //b2MouseJointDef md_;

  //bool flying_;

  // alignments
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_
