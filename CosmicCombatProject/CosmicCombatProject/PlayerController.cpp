/* Copyright 2013 Brandon Edgren */

#include "./PlayerController.h"
#include "./Util.h"

void PlayerController::CharacterAdd(Character::Ptr chr) {
  characters_.clear();
  characters_.insert(chr);
}

void PlayerController::ProcessEvent(sf::Event event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left) {
        left_down_ = true;
      } else if (event.mouseButton.button == sf::Mouse::Right) {
        right_down_ = true;
      }
      break;
    case sf::Event::MouseButtonReleased:
      if (event.mouseButton.button == sf::Mouse::Left) {
        left_down_ = false;
      } else if (event.mouseButton.button == sf::Mouse::Right) {
        right_down_ = false;
      }
      break;
    case sf::Event::MouseMoved:
      mouse_x_ = event.mouseMove.x;
      mouse_y_ = event.mouseMove.y;
      break;
    case sf::Event::KeyPressed:
      printf("key down: %d / %c\n", event.key.code, CodeToChar(event.key.code));
      break;
    case sf::Event::KeyReleased:
      printf("key up: %d / %c\n", event.key.code, CodeToChar(event.key.code));
      break;
    default:
      break;
  }
}

void PlayerController::Tick(sf::Window *window) {
  b2Body *body = Character()->Body();
  b2Vec2 chrPos = body->GetPosition();
  b2Vec2 base = Character()->ClosestPlanet()->Position();
  float angle_r = RadiansOf(chrPos - base);
  if (chrPos.x < base.x)
    angle_r = -angle_r;
  Character()->Body()->SetTransform(chrPos, angle_r);
  if (left_down_) {
    b2Vec2 mouseVec(mouse_x_ - window->getSize().x / 2.0f,
                    mouse_y_ - window->getSize().y / 2.0f);
    b2Vec2 rotated = RotatedVector(mouseVec, angle_r);
    body->ApplyLinearImpulse(rotated, body->GetPosition());
  }
}
