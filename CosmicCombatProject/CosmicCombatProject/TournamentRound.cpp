/* Copyright 2013 Brandon Edgren */

#include <random>
#include <vector>

#include "./Settings.h"
#include "./TournamentRound.h"

TournamentRound::TournamentRound(Character *player1,
                                 Character *player2,
                                 const float32 width, const float32 height,
                                 const float32 stage_width,
                                 const float32 gravity)
  : width_(width), height_(height), stage_width_(stage_width) {

  world_ = new b2World(b2Vec2(0.0f, gravity));

  CreateBoundaries();
  ground_body_ = CreateGround();
  stage_body_ = CreateStage();

  //player1_data_->type = kCharacter;
  //player1_data_->data = static_cast<void*>(player1);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, -4.0f);
  bodyDef.fixedRotation = true;
  bodyDef.linearDamping = 0.5f;
  bodyDef.gravityScale = 0.0f;
  //bodyDef.userData = static_cast<void*>(player1_data_);
  player1_body_ = world_->CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(0.5f, 0.5f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  player1_body_->CreateFixture(&fixtureDef);

  player1->set_body(player1_body_, world_);

   b2BodyDef bodyDef2;
   bodyDef2.type = b2_dynamicBody;
   bodyDef2.position.Set(0.0f, -7.0f);
   b2Body* body2 = world_->CreateBody(&bodyDef2);
   b2PolygonShape dynamicBox2;
   dynamicBox2.SetAsBox(0.5f, 0.5f);
   b2FixtureDef fixtureDef2;
   fixtureDef2.shape = &dynamicBox2;
   fixtureDef2.density = 1.0f;
   fixtureDef2.friction = 0.3f;
   body2->CreateFixture(&fixtureDef2);
}

TournamentRound::~TournamentRound(void) {
  delete world_;
}

bool TournamentRound::IsCharacterOnGround(Character *ch) {
  b2Body *char_body = ch->body();
  b2Body *bodyA, *bodyB;
  for (b2Contact *c = world_->GetContactList(); c; c = c->GetNext()) {
    bodyA = c->GetFixtureA()->GetBody();
    bodyB = c->GetFixtureB()->GetBody();
    if (bodyA == char_body && (bodyB == ground_body_ || bodyB == stage_body_))
      return true;
    else if (bodyB == char_body && (bodyA == ground_body_ || bodyA == stage_body_))
      return true;
  }
  return false;
}

void TournamentRound::Step() {
  for (int32 i = 0; i < 6; i++)
    world_->Step(kMinTimeStep, kVelocityIterations, kPositionIterations);
  // world_->ClearForces();
}

void TournamentRound::CreateBoundaries() {
  float32 boundary_size = 5;
  float32 top_width = width_ + boundary_size * 2;
  float32 top_distance = height_ + boundary_size / 2;
  float32 side_height = height_ + boundary_size * 2;
  float32 side_distance = (width_ + boundary_size) / 2;
  float32 side_extra = 20;

  CreateBoundary(-side_distance,
                 -side_height / 2 + boundary_size,
                 boundary_size,
                 side_height);

  CreateBoundary(0,
                 -top_distance,
                 top_width,
                 boundary_size);

  CreateBoundary(side_distance,
                 -side_height / 2 + boundary_size,
                 boundary_size,
                 side_height);
}

b2Body* TournamentRound::CreateBoundary(float32 x, float32 y,
                                       float32 width, float32 height) {
  b2BodyDef boundary_def;
  boundary_def.type = b2_staticBody;
  boundary_def.position.Set(x, y);
  b2Body *body = world_->CreateBody(&boundary_def);
  b2PolygonShape box;
  box.SetAsBox(width / 2.0f, height / 2.0f);
  body->CreateFixture(&box, 0.0f);

  return body;
}

b2Body* TournamentRound::CreateGround() {
  b2BodyDef ground_def;
  ground_def.type = b2_staticBody;
  ground_def.position.Set(0.0f, 0.0f);
  b2Body *body = world_->CreateBody(&ground_def);

  const int32 point_count = (static_cast<int32>(width_) / 2) + 1;
  const float32 edge_length = width_ / (point_count - 1);
  std::vector<b2Vec2> vs;
  std::random_device rd;
  for (int32 i = 0; i < point_count; i++) {
    float32 x = edge_length*i - width_ / 2;
    float32 y = 0;
    if (x < -stage_width_ / 2 - edge_length ||
        x > stage_width_ / 2 + edge_length)
      y = (rd() % 1000) / 1000.0f - 0.5f;
    vs.push_back(b2Vec2(x, y));
  }
  b2ChainShape chain;
  chain.CreateChain(&vs[0], point_count);

  body->CreateFixture(&chain, 0.0f);

  return body;
}

b2Body* TournamentRound::CreateStage() {
  return CreateBoundary(0.0f, -1.25f, stage_width_, 2.5f);
}
