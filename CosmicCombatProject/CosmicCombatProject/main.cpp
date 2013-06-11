/* Copyright 2013 Brandon Edgren */

#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

#include <cstdio>

#include "./DebugDraw.h"
#include "./Settings.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D test",
    sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  sf::View main_view(sf::Vector2f(0, 0), sf::Vector2f(800, 600));
  main_view.zoom(0.1f);

  b2Vec2 gravity(0.0f, 10.0f);
  b2World world(gravity);

  DebugDraw debug_draw(&window);
  if (kDrawDebugData) {
    debug_draw.AppendFlags(b2Draw::e_shapeBit |
                           b2Draw::e_jointBit |
                           b2Draw::e_aabbBit |
                           b2Draw::e_pairBit |
                           b2Draw::e_centerOfMassBit);
    world.SetDebugDraw(&debug_draw);
  }

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, 10.0f);
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, -4.0f);
  bodyDef.angle = 314/350.0f;
  b2Body* body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  body->CreateFixture(&fixtureDef);
  b2BodyDef bodyDef2;
  bodyDef2.type = b2_dynamicBody;
  bodyDef2.position.Set(0.0f, -7.0f);
  b2Body* body2 = world.CreateBody(&bodyDef2);
  b2PolygonShape dynamicBox2;
  dynamicBox2.SetAsBox(1.0f, 1.0f);
  b2FixtureDef fixtureDef2;
  fixtureDef2.shape = &dynamicBox2;
  fixtureDef2.density = 1.0f;
  fixtureDef2.friction = 0.3f;
  body2->CreateFixture(&fixtureDef2);
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    world.Step(timeStep, velocityIterations, positionIterations);

    window.setView(main_view);
    window.clear();

    if (kDrawDebugData)
      world.DrawDebugData();

    window.display();
  }

  return 0;
}
