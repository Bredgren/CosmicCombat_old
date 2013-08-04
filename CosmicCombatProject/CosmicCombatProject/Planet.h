/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_PLANET_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_PLANET_H_

#include <Box2D/Box2D.h>

#include "./Energy.h"

class Planet {
 public:
  typedef Planet* Ptr;

  Planet(b2World *world, b2Vec2 position, float radius);
  virtual ~Planet(void);

  b2Vec2 Position() const { return position_; }
  void PositionIs(const b2Vec2 &position);

  float Gravity() const { return gravity_; }

  const Energy &EnergyLevel() const { return energy_; }
  Energy &EnergyLevel() { return energy_; }

 protected:
  b2World *world_;
  b2Vec2 position_;
  float radius_;
  float gravity_;
  Energy energy_;

 private:
  Planet(const Planet &);
  Planet &operator=(const Planet &);
  Planet &operator==(const Planet &);
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_PLANET_H_
