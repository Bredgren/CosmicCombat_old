/* Copyright 2013 Brandon Edgren */

#include "./Character.h"

Character::Character(string name, float start_energy)
  : energy_(start_energy) {
  name_ = name;
  //type_ = type;
  //flying_ = true;

  //md_.collideConnected = true;
  //md_.dampingRatio = 5.0f;
}

Character::~Character(void) {
}

void Character::BodyIs(b2Body *body) {
  body_ = body;
}

void Character::TargetPositionIs(b2Vec2 pos) {
  //if (flying_) {
  //  target_->SetTarget(pos);
  //} else {
  //  b2Vec2 dir = pos - body_->GetPosition();
  //  dir.Normalize();
  //  dir *= 2.0f;
  //  body_->ApplyLinearImpulse(dir, b2Vec2_zero);
  //}
}

Planet::Ptr Character::ClosestPlanet() {
  return closest_planet_;
}

void Character::ClosestPlanetIs(Planet::Ptr planet) {
  closest_planet_ = planet;
}

//void Character::StartFlying() {
//  flying_ = true;
//  body_->SetGravityScale(0.0f);
//  md_.target = md_.bodyB->GetPosition();
//  target_ = static_cast<b2MouseJoint*>(world_->CreateJoint(&md_));
//}
//
//void Character::StopFlying() {
//  flying_ = false;
//  body_->SetGravityScale(1.0f);
//  world_->DestroyJoint(target_);
//}

//void Character::set_body(b2Body *body, b2World *world) {
//  b2Body *dummy;
//  for (dummy = world->GetBodyList(); dummy; dummy = dummy->GetNext()) {
//    if (dummy != body)
//      break;
//  }
//  body_ = body;
//
//  md_.bodyA = dummy;
//  md_.bodyB = body_;
//  md_.maxForce = 200.0f * body_->GetMass();
//  md_.target = body_->GetPosition();
//  
//  target_ = static_cast<b2MouseJoint*>(world->CreateJoint(&md_));
//}