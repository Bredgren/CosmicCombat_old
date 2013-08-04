/* Copyright 2013 - Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CAMERA_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CAMERA_H_

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Camera : public sf::View {
 public:
  Camera();
  Camera(const sf::Vector2f &center, const sf::Vector2f &size);
  virtual ~Camera();

  b2Body *Target() const { return target_; }
  void TargetIs(b2Body *target);

  void Update(const b2Vec2 &base, const b2Vec2 &mouse);

  void move(float offsetX, float offsetY);

 private:
  b2Body * target_;

  Camera(const Camera&);
  Camera &operator=(const Camera &);
  Camera &operator==(const Camera &);
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_CAMERA_H_
