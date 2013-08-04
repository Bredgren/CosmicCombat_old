
#include "./Camera.h"
#include "./Settings.h"
#include "./Util.h"

Camera::Camera() {
}

Camera::Camera(const sf::Vector2f &center, const sf::Vector2f &size)
  : sf::View(center, size) {
}

Camera::~Camera() {
}

void Camera::TargetIs(b2Body *target) {
  target_ = target;
}

void Camera::Update(const b2Vec2 &base, const b2Vec2 &mouse) {
  if (target_) {
    // Set camera to target position
    b2Vec2 targetPos = target_->GetPosition();
    setCenter(targetPos.x * kPixelsPerMeter, targetPos.y * kPixelsPerMeter);

    // Rotate camera so down is direction of base
    float angle = AngleOf(targetPos - base);
    if (targetPos.x < base.x)
      angle = -angle;
    setRotation(angle);

    // Rotate mouse vector and offset camera
    move(mouse.x, mouse.y);
  }
}

void Camera::move(float offsetX, float offsetY) {
  b2Vec2 rotated = RotatedVector(b2Vec2(offsetX, offsetY),
      DegToRad(getRotation()));
  sf::View::move(rotated.x, rotated.y);
}
