/* Copyright 2013 Brandon Edgren */

#include <string>

#include "./DebugDraw.h"
#include "./Settings.h"

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                            const b2Color& color) {
  sf::ConvexShape convex;
  convex.setPointCount(vertexCount);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  convex.setOutlineColor(c);
  convex.setOutlineThickness(1.0f);
  convex.setFillColor(sf::Color::Transparent);

  for (int32 i = 0; i < vertexCount; ++i)
    convex.setPoint(i, sf::Vector2f(vertices[i].x * kPixelsPerMeter,
                                    vertices[i].y * kPixelsPerMeter));

  window_->draw(convex);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                 const b2Color& color) {
  sf::ConvexShape convex;
  convex.setPointCount(vertexCount);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  convex.setFillColor(c);

  for (int32 i = 0; i < vertexCount; ++i)
    convex.setPoint(i, sf::Vector2f(vertices[i].x * kPixelsPerMeter,
                                    vertices[i].y * kPixelsPerMeter));

  window_->draw(convex);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius,
                           const b2Color& color) {
  sf::CircleShape circle;
  circle.setRadius(radius * kPixelsPerMeter);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  circle.setOutlineColor(c);
  circle.setOutlineThickness(1.0f);
  circle.setFillColor(sf::Color::Transparent);
  circle.setPointCount(100);

  circle.setPosition((center.x - radius) * kPixelsPerMeter,
                     (center.y - radius) * kPixelsPerMeter);

  window_->draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius,
                                const b2Vec2& axis, const b2Color& color) {
  sf::CircleShape circle;
  circle.setRadius(radius * kPixelsPerMeter);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  circle.setFillColor(c);
  circle.setPointCount(100);

  circle.setPosition((center.x - radius) * kPixelsPerMeter,
                     (center.y - radius) * kPixelsPerMeter);

  window_->draw(circle);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
                            const b2Color& color) {
  sf::Color c(color.r*255, color.g*255, color.b*255);

  sf::Vertex line[] = {
    sf::Vertex(sf::Vector2f(p1.x * kPixelsPerMeter, p1.y * kPixelsPerMeter), c),
    sf::Vertex(sf::Vector2f(p2.x * kPixelsPerMeter, p2.y * kPixelsPerMeter), c)
  };

  window_->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
  b2Vec2 p1 = xf.p, p2, p3;
  const float32 k_axisScale = 0.1f * kPixelsPerMeter;

  sf::Color c(255, 0, 0);
  sf::Color c2(0, 255, 0);

  p2 = p1 + k_axisScale * xf.q.GetXAxis();
  p3 = p1 + k_axisScale * xf.q.GetYAxis();

  sf::Vertex lines[] = {
    sf::Vertex(sf::Vector2f(p1.x * kPixelsPerMeter, p1.y * kPixelsPerMeter), c),
    sf::Vertex(sf::Vector2f(p2.x * kPixelsPerMeter, p2.y * kPixelsPerMeter), c),
    sf::Vertex(sf::Vector2f(p1.x * kPixelsPerMeter, p1.y * kPixelsPerMeter), c2),
    sf::Vertex(sf::Vector2f(p3.x * kPixelsPerMeter, p3.y * kPixelsPerMeter), c2)
  };

  window_->draw(lines, 4, sf::Lines);
}
