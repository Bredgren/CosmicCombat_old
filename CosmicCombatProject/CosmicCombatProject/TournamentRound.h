/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTROUND_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTROUND_H_

#include <Box2D\Box2D.h>

#include "./Character.h"
#include "./UserData.h"

/// Manages a round of a tournament.
/**
    A tournament round consists of two characters who start on a stage which
    is raised slightly above the ground. The round ends when either character
    lands on the ground outside the stage or runs out of energy.
 */
class TournamentRound {
 public:
  /// Sets up a new tournament round.
  /**
      @param width the width of the arena in meters.
      @param height the height of the arena in meters.
      @param stage_width the width of the stage in meters.
      @param gravity the gravity to use.
      @param player1 the character that defines the first player.
      @param player2 the character that defines the second player.
   */
  TournamentRound(Character *player1, Character *player2,
                  const float32 width = 50, const float32 height = 50,
                  const float32 stage_width = 25,
                  const float32 gravity = 10.0f);

  virtual ~TournamentRound(void);

  /// Ask if the round is over.
  /**
      Use this method to find out if the round is over and who the winner and
      loser is.
      @param winner the winner if the round is over, otherwise NULL.
      @param loser the loser of the round is over, otherwise NULL.
      @return true if either player ran out of energy or touched the ground.
   */
  bool IsOver(Character *winner, Character *loser);

  bool IsCharacterOnGround(Character *ch);

  b2World* world() const { return world_; }
  b2Body* player1_body() const { return player1_body_; }
  b2Body* player2_body() const { return player2_body_; }

  void Step();

 private:
  const float32 width_, height_, stage_width_;
  b2World *world_;
  b2Body *player1_body_;
  UserData player1_data_;
  b2Body *player2_body_;
  UserData player2_data_;

  b2Body *ground_body_, *stage_body_;

  void CreateBoundaries();
  b2Body* CreateBoundary(float32 x, float32 y, float32 width, float32 height);
  b2Body* CreateGround();
  b2Body* CreateStage();
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_TOURNAMENTROUND_H_
