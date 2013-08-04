/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <cstdio>

#include "./Camera.h"
#include "./Character.h"
#include "./DebugDraw.h"
#include "./Planet.h"
#include "./PlayerController.h"
#include "./Settings.h"

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

  b2World World() const { return world_; }

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
  Camera main_camera_;

  DebugDraw debug_draw_;

  b2World world_;
  Planet::Ptr planets_[2];
  uint32_t num_planets_;
  Character::Ptr characters_[1];
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_GAME_H_
