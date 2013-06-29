/* Copyright 2013 Brandon Edgren */

#include "./Game.h"

Game::Game(void)
  : p1("player 1", Character::kDefalut),
    p2("player 2", Character::kDefalut),
    round_(&p1, &p2, 100.0f, 100.0f),
    debug_draw_(&window_) {
  InitializeWindow(800, 600, false);
 
  debug_draw_.AppendFlags(b2Draw::e_shapeBit |
                         b2Draw::e_jointBit |
                         // b2Draw::e_aabbBit |
                         b2Draw::e_pairBit |
                         b2Draw::e_centerOfMassBit);
  round_.world()->SetDebugDraw(&debug_draw_);

  p1.set_world_(round_.world());
  p2.set_world_(round_.world());

  player_controler_.AddCharacter(&p1);
}

Game::~Game(void) {
}

void Game::Run() {
  int32 prev_x = 0;
  int32 prev_y = 0;
  bool drag = false;
  bool grounded = false;

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      player_controler_.ProcessEvent(event);
      switch (event.type) {
      case sf::Event::Closed:
        window_.close();
        break;
      case sf::Event::MouseWheelMoved:
        if (kDebugMode && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
          if (event.mouseWheel.delta > 0)
            main_view_.zoom(0.9f);
          else if (event.mouseWheel.delta < 0)
            main_view_.zoom(1.1f);
        break;
      case sf::Event::MouseButtonPressed:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          drag = true;
          sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
          sf::Vector2f worldPos = window_.mapPixelToCoords(pixelPos, main_view_);
          p1.SetTargetPosition(b2Vec2(worldPos.x / kPixelsPerMeter,
                                      worldPos.y / kPixelsPerMeter));
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
          b2Vec2 pixelPos(event.mouseButton.x, event.mouseButton.y);
          if (p1.flying())
            p1.StopFlying();
          else if (!grounded)
            p1.StartFlying();
        }
        break;
      case sf::Event::MouseButtonReleased:
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
          drag = false;
        break;
      case sf::Event::MouseMoved:
        if (kDebugMode && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left))
          main_view_.move(static_cast<float>(prev_x - event.mouseMove.x),
                          static_cast<float>(prev_y - event.mouseMove.y));
        prev_x = event.mouseMove.x;
        prev_y = event.mouseMove.y;
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) {
          window_.close();
        } else if (event.key.code == sf::Keyboard::Tilde) {
          main_view_.setCenter(sf::Vector2f(0, 0));
          main_view_.setSize(sf::Vector2f(window_.getSize().x,
                                          window_.getSize().y));
        } else if (event.key.code == sf::Keyboard::Space) {
          p1.body()->SetLinearVelocity(b2Vec2_zero);
          p1.SetTargetPosition(p1.body()->GetPosition());
        }
        break;
      default:
        break;
      }
    }

    if (drag) {
      sf::Vector2i pixelPos(prev_x, prev_y);
      sf::Vector2f worldPos = window_.mapPixelToCoords(pixelPos, main_view_);
       p1.SetTargetPosition(b2Vec2(worldPos.x / kPixelsPerMeter,
                                   worldPos.y / kPixelsPerMeter));
    }

    player_controler_.Tick();

    round_.Step();

    grounded = round_.IsCharacterOnGround(&p1);
    /*if (grounded)
      printf("on ground. flying: %d\n", p1.flying());
    else
      printf("off ground. flying: %d\n", p1.flying());*/

    /*
    if (!player_body->IsAwake()) {
      player_body->SetLinearVelocity(b2Vec2_zero);
      target = player_body->GetPosition();
    }
    */
    b2Vec2 player_loc = p1.body()->GetPosition();
    main_view_.setCenter(player_loc.x*kPixelsPerMeter,
                        player_loc.y*kPixelsPerMeter);

    window_.setView(main_view_);
    window_.clear();

    if (kDebugMode)
      round_.world()->DrawDebugData();

    // window_.setView(window_.getDefaultView());
    // draw hud here

    window_.display();
  }
}

void Game::InitializeWindow(sf::Uint32 resolution_width,
                            sf::Uint32 resolution_height,
                            bool fullscreen) {
  sf::VideoMode mode(resolution_width, resolution_height);
  sf::Uint32 style(sf::Style::Titlebar | sf::Style::Close);
  if (fullscreen)
    style += sf::Style::Fullscreen;
  window_.create(mode, "Cosmic Combat", style);
  window_.setVerticalSyncEnabled(true);
  window_.setKeyRepeatEnabled(false);

  sf::Vector2f view_size(static_cast<float>(resolution_width),
                         static_cast<float>(resolution_height));
  main_view_ = sf::View(sf::Vector2f(0, 0), view_size);
}
