/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_

#include <Box2D\Box2D.h>

#include <string>

#include "./Energy.h"

using std::string;

/// Represents a game character.
/**
    Manages data and behavior common to all NPCs and player controlled
    characters.
 */
class Character {
 public:
  /// Types used to distinguish characters.
  enum Type {
    kDefalut
  };

  /// Creates a new character.
  /**
      @param name the name of the character.
      @param type the type of character.
      @param start_energy the character's starting maximum energy.
   */
  Character(string name, Type type, float start_energy = 100.0f);
  virtual ~Character(void);

  /// Sets the characters target position.
  /**
      @param pos the position to set the target to.
   */
  void SetTargetPosition(b2Vec2 pos);

  void set_world_(b2World *world) { world_ = world; }

  void StartFlying();
  void StopFlying();
  
  /** Sets the characters body */
  void set_body(b2Body *body, b2World *world);
  /** Get the characters body */
  b2Body *body() const { return body_; }

  bool flying() const { return flying_; }

 private:
  string name_;
  Type type_;
  Energy energy_;
  b2World *world_;

  b2Body *body_;
  b2MouseJoint *target_;

  b2MouseJointDef md_;

  bool flying_;

  // alignments
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CHARACTER_H_
