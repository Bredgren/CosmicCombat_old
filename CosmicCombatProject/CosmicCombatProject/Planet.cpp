/* Copyright 2013 Brandon Edgren */

#include <math.h>

#include <vector>

#include "./Planet.h"

using std::vector;

Planet::Planet(b2World *world, b2Vec2 position, float radius)
    : world_(world), position_(position), radius_(radius) {
  b2BodyDef boundary_def;
  boundary_def.type = b2_staticBody;
  boundary_def.position.Set(position.x, position.y);
  b2Body *body = world_->CreateBody(&boundary_def);

  float circ = 2.0f * radius * 3.14f;
  const int kVertexCount = 100;
  float angle_diff = (360.0f / kVertexCount) / 180.0f * 3.14f;

  b2Vec2 verticies[kVertexCount];
  float angle = 0.0f;
  for (int i = 0; i < kVertexCount; angle += angle_diff, ++i) {
    float x = cos(angle) * radius;
    float y = sin(angle) * radius;
    verticies[i].Set(x, y);
  }
  b2ChainShape chain;
  chain.CreateLoop(verticies, kVertexCount);
  body->CreateFixture(&chain, 0.0f);

  gravity_ = radius_;
  energy_ = Energy(100000 * radius_);
}

Planet::~Planet(void) {
}

void
Planet::PositionIs(const b2Vec2 &newPosition) {
  if (newPosition == position_) return;
  position_ = newPosition;
}
