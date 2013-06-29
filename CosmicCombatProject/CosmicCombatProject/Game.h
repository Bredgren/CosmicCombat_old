/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_

#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

#include <cstdio>

#include "./DebugDraw.h"
#include "./FSM.h"
#include "./Settings.h"
#include "./StandardPlayerController.h"
#include "./TournamentRound.h"

/// Manages the flow of the game.
/**
    Controls navigation through the games menus and determines what is
    currently being displayed.
 */
class Game {
 public:
  /** Initializes a new game. */
  Game(void);
  virtual ~Game(void);

  /// Starts the game.
  /**
      Once this function is called it will not return until the player quits
      the game.
   */
  void Run();

  /// Sets up the display window.
  /**
      @param resolution_width the width of the display area in pixels.
      @param resolution_height the height of the display area in pixels.
      @param fullscreen whether or not the display should be fullscreen.
   */
  void InitializeWindow(sf::Uint32 resolution_width,
                        sf::Uint32 resolution_height,
                        bool fullscreen = false);

 private:
  sf::RenderWindow window_;
  sf::View main_view_;

  DebugDraw debug_draw_;

  FSM game_state_;

  StandardPlayerController player_controler_;

  // tempororay:
  Character p1;
  Character p2;
  TournamentRound round_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_
