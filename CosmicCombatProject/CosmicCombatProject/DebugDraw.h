/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_DEBUGDRAW_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_DEBUGDRAW_H_

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#include <string>

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class DebugDraw : public b2Draw {
 public:
  explicit DebugDraw(sf::RenderWindow *window)
    : b2Draw(), window_(window) {}

  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                   const b2Color& color);
  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                        const b2Color& color);
  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
  void DrawSolidCircle(const b2Vec2& center, float32 radius,
                       const b2Vec2& axis, const b2Color& color);
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
  void DrawTransform(const b2Transform& xf);
 private:
  sf::RenderWindow *window_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_DEBUGDRAW_H_
