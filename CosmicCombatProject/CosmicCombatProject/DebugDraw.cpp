/* Copyright 2013 Brandon Edgren */

#include <string>

#include "./DebugDraw.h"

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                            const b2Color& color) {
  sf::ConvexShape convex;
  convex.setPointCount(vertexCount);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  convex.setOutlineColor(c);
  convex.setOutlineThickness(0.1f);
  convex.setFillColor(sf::Color::Transparent);

  for (int32 i = 0; i < vertexCount; ++i)
    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));

  window_->draw(convex);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                 const b2Color& color) {
  sf::ConvexShape convex;
  convex.setPointCount(vertexCount);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  convex.setFillColor(c);

  for (int32 i = 0; i < vertexCount; ++i)
    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));

  window_->draw(convex);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius,
                           const b2Color& color) {
  sf::CircleShape circle;
  circle.setRadius(radius);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  circle.setOutlineColor(c);
  circle.setFillColor(sf::Color::Transparent);
  circle.setPointCount(100);

  circle.setPosition(center.x - radius, center.y - radius);

  window_->draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius,
                                const b2Vec2& axis, const b2Color& color) {
  sf::CircleShape circle;
  circle.setRadius(radius);

  sf::Color c(color.r*255, color.g*255, color.b*255);
  circle.setFillColor(c);
  circle.setPointCount(100);

  circle.setPosition(center.x - radius, center.y - radius);

  window_->draw(circle);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
                            const b2Color& color) {
  sf::Color c(color.r*255, color.g*255, color.b*255);

  sf::Vertex line[] = {
    sf::Vertex(sf::Vector2f(p1.x, p1.y), c),
    sf::Vertex(sf::Vector2f(p2.x, p2.y), c)
  };

  window_->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
  b2Vec2 p1 = xf.p, p2, p3;
  const float32 k_axisScale = 0.4f;
	
	sf::Color c(255, 0, 0);
	sf::Color c2(0, 255, 0);

  p2 = p1 + k_axisScale * xf.q.GetXAxis();
	p3 = p1 + k_axisScale * xf.q.GetYAxis();

  sf::Vertex lines[] = {
    sf::Vertex(sf::Vector2f(p1.x, p1.y), c),
    sf::Vertex(sf::Vector2f(p2.x, p2.y), c),
    sf::Vertex(sf::Vector2f(p1.x, p1.y), c2),
    sf::Vertex(sf::Vector2f(p3.x, p3.y), c2)
  };

  window_->draw(lines, 4, sf::Lines);
}