/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTGAME_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTGAME_H_

#include <Box2D\Box2D.h>

class TournamentGame {
 public:
  TournamentGame(const float32 width = 50, const float32 height = 50,
                 const float32 stage_width = 25,
                 const b2Vec2 gravity = b2Vec2(0.0f, 10.0f));
  virtual ~TournamentGame(void);

  b2World* world() const { return world_; }
  b2Body* player_body() const { return player_body_; }

  void Step();

 private:
  const float32 width_, height_, stage_width_;
  const b2Vec2 gravity_;
  b2World *world_;
  b2Body *player_body_;

  b2Body *boundry_body;

  void CreateBoundaries();
  b2Body* CreateBoundary(float32 x, float32 y, float32 width, float32 height);
  b2Body* CreateGround();
  b2Body* CreateStage();
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTGAME_H_
