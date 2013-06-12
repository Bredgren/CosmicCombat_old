/* Copyright 2013 Brandon Edgren */

#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

#include <cstdio>

#include "./DebugDraw.h"
#include "./Settings.h"
#include "./TournamentGame.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D test",
    sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
  window.setVerticalSyncEnabled(true);
  sf::View main_view(sf::Vector2f(0, 0), sf::Vector2f(800, 600));

  sf::Vector2i center(400, 300);

  TournamentGame game(100.0f, 100.0f);
  b2Body *player_body = game.player_body();

  DebugDraw debug_draw(&window);
  debug_draw.AppendFlags(b2Draw::e_shapeBit |
                         b2Draw::e_jointBit |
                         // b2Draw::e_aabbBit |
                         b2Draw::e_pairBit |
                         b2Draw::e_centerOfMassBit);
  game.world()->SetDebugDraw(&debug_draw);

  b2Vec2 target = player_body->GetPosition();

  bool drag = false;
  int32 prev_x = 0;
  int32 prev_y = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseWheelMoved:
        if (kDebugMode && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
          if (event.mouseWheel.delta > 0)
            main_view.zoom(0.9f);
          else if (event.mouseWheel.delta < 0)
            main_view.zoom(1.1f);
        break;
      case sf::Event::MouseButtonPressed:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          drag = true;
        }
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        //  sf::Vector2i mouse_pos(prev_x, prev_y);
        //  sf::Vector2i dir = mouse_pos - center;
        //  b2Vec2 impulse(dir.x / 10.0f, dir.y / 10.0f);
        //  if (impulse.y > 15.0f) {
        //    impulse.y = 15.0f;
        //  } else if (impulse.y < -15.0f) {
        //    impulse.y = -15.0f;
        //  }
        //  player_body->ApplyLinearImpulse(impulse, player_body->GetPosition());
        //}
        break;
      case sf::Event::MouseButtonReleased:
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
          drag = false;
        break;
      case sf::Event::MouseMoved:
        if (kDebugMode && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
            drag)
          main_view.move(prev_x - event.mouseMove.x,
                         prev_y - event.mouseMove.y);
        prev_x = event.mouseMove.x;
        prev_y = event.mouseMove.y;
        break;
      case sf::Event::KeyPressed:
        printf("%d\n", event.key.code);
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        } else if (event.key.code == sf::Keyboard::Tilde) {
          main_view.setCenter(sf::Vector2f(0, 0));
          main_view.setSize(sf::Vector2f(800, 600));
        } else if (event.key.code == sf::Keyboard::Space) {
          player_body->SetLinearVelocity(b2Vec2_zero);
          target = player_body->GetPosition();
        }
        break;
      default:
        break;
      }
    }

    if (drag) {
      sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
      sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, main_view);
      target.x = worldPos.x / kPixelsPerMeter;
      target.y = worldPos.y / kPixelsPerMeter;
    //  sf::Vector2i mouse_pos(prev_x, prev_y);
    //  sf::Vector2i dir = mouse_pos - center;
    //  b2Vec2 impulse(dir.x/100.0f, 0);
    //  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
    //    player_body->GetLinearVelocity().Length() < 20.0f ||
    //      ((player_body->GetLinearVelocity().x >= 0 && impulse.x <= 0) ||
    //       (player_body->GetLinearVelocity().x <= 0 && impulse.x >= 0))) {
    //    player_body->ApplyLinearImpulse(impulse, player_body->GetPosition());
    //  }
    }

    b2Vec2 dir = target - player_body->GetPosition();
    if (dir.Length() > 1.0f) {
      dir.Normalize();
      dir *= 50.0f;
      player_body->SetLinearVelocity(dir);
    } else {
      player_body->SetLinearVelocity(b2Vec2_zero);
      target = player_body->GetPosition();
    }

    //player_body->SetTransform(player_body->GetPosition(), 3.14/4);

    game.Step();
    game.world()->ClearForces();

    b2Vec2 player_loc = player_body->GetPosition();
    main_view.setCenter(player_loc.x*kPixelsPerMeter,
                        player_loc.y*kPixelsPerMeter);

    window.setView(main_view);
    window.clear();

    if (kDebugMode)
      game.world()->DrawDebugData();

    // window.setView(window.getDefaultView());
    // draw hud here

    window.display();
  }

  return 0;
}
