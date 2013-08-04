/* Copyright 2013 Brandon Edgren */

#include "./Game.h"
#include "./Util.h"

Game::Game(void)
  : debug_draw_(&window_), world_(b2Vec2_zero) {
  InitializeWindow(800, 600, false);
 
  debug_draw_.AppendFlags(b2Draw::e_shapeBit |
                         b2Draw::e_jointBit |
                         // b2Draw::e_aabbBit |
                         b2Draw::e_pairBit |
                         b2Draw::e_centerOfMassBit);
  world_.SetDebugDraw(&debug_draw_);

  planets_[0] = new Planet(&world_, b2Vec2_zero, 100.0f);
  planets_[1] = new Planet(&world_, b2Vec2(300.0f, 0.0f), 50.0f);
  num_planets_ = 2;

  characters_[0] = new Character("player");
  b2BodyDef def;
  def.type = b2_dynamicBody;
  //def.angularDamping = 1.0f;
  def.position.Set(0.0f,-110.0f);
  def.fixedRotation = true;
  b2Body* body = world_.CreateBody(&def);
  b2PolygonShape box;
  box.SetAsBox(0.5f, 0.5f);
  b2FixtureDef fix;
  fix.shape = &box;
  fix.density = 5.0f;
  fix.friction = 1.0f;
  body->CreateFixture(&fix);
  characters_[0]->BodyIs(body);
  characters_[0]->ClosestPlanetIs(planets_[0]);

  PlayerController::Instance().CharacterAdd(characters_[0]);

  main_camera_.TargetIs(PlayerController::Instance().Character()->Body());
}

Game::~Game(void) {
  for (Planet::Ptr plt : planets_)
    delete plt;
  for (Character::Ptr chr : characters_)
    delete chr;
}

void Game::Run() {
  int32 prev_x = 0;
  int32 prev_y = 0;
  bool drag = false;
  bool right_drag = false;
  sf::Vector2f right_start(0.0f, 0.0f);

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window_.close();
        break;
      case sf::Event::MouseWheelMoved:
        if (kDebugMode)
          if (event.mouseWheel.delta > 0) {
            main_camera_.zoom(0.9f);
          } else if (event.mouseWheel.delta < 0) {
            main_camera_.zoom(1.1f);
          }
        break;
      case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f worldPos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
          drag = true;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
          right_drag = true;
          right_start = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
          right_start.x /= kPixelsPerMeter;
          right_start.y /= kPixelsPerMeter;
        }
        break;
      case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left) {
          drag = false;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
          right_drag = false;
        }
        break;
      case sf::Event::MouseMoved:
        if (kDebugMode && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          float dx = static_cast<float>(prev_x - event.mouseMove.x);
          float dy = static_cast<float>(prev_y - event.mouseMove.y);
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            main_camera_.rotate(dx);
          } else {
            main_camera_.move(dx, dy);
          }
        }
        prev_x = event.mouseMove.x;
        prev_y = event.mouseMove.y;
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Delete) {
          window_.close();
        } else if (event.key.code == sf::Keyboard::Tilde) {
          main_camera_.setCenter(sf::Vector2f(0, 0));
          main_camera_.setRotation(0);
          main_camera_.setSize(sf::Vector2f(window_.getSize().x,
                                            window_.getSize().y));
        } else if (event.key.code == sf::Keyboard::Escape) {
          if (main_camera_.Target()) {
            main_camera_.TargetIs(0);
          } else {
           main_camera_.TargetIs(
             PlayerController::Instance().Character()->Body());
          }
        }
        break;
      default:
        break;
      }
      PlayerController::Instance().ProcessEvent(event);
    }

    for (Character::Ptr chr : characters_) {
      b2Vec2 loc = chr->Body()->GetPosition();
      b2Vec2 dir = planets_[0]->Position() - loc;
      dir.Normalize();
      dir.x *= planets_[0]->Gravity() * kPixelsPerMeter;
      dir.y *= planets_[0]->Gravity() * kPixelsPerMeter;
      chr->Body()->ApplyForce(dir, loc);
    }

    PlayerController::Instance().Tick(&window_);

    world_.Step(1/60.0f, kVelocityIterations, kPositionIterations);
    
    b2Vec2 mouseVec(prev_x - window_.getSize().x / 2.0f,
                    prev_y - window_.getSize().y / 2.0f);
    main_camera_.Update(planets_[0]->Position(), mouseVec);

    window_.setView(main_camera_);
    window_.clear();

    if (kDebugMode)
      world_.DrawDebugData();

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
  main_camera_.setCenter(sf::Vector2f(0, 0));
  main_camera_.setSize(view_size);
}
