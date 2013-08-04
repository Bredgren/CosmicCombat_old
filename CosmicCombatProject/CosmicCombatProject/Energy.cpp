/* Copyright 2013 - Brandon Edgren */

#include <sstream>
#include <stdexcept>
#include <string>

#include "./Energy.h"
#include "./Util.h"

Energy::~Energy(void) {
}

float Energy::max() const {
  return max_;
}

void Energy::maxIs(const float amount) {
  max_ = amount;
  if (max_ < available_)
    available_ = max_;
    if (max_ < strength_)
      strength_ = max_;
}

void Energy::maxInc(const float amount) {
  max_ += amount;
}

float Energy::available() const {
  return available_;
}

float Energy::availableAsPercentOfMax() const {
  return available_ / max_;
}

void Energy::availableIs(const float amount) {
  available_ = amount;
  if (available_ > max_)
    max_ = available_;
  else if (available_ < strength_)
    strength_ = available_;
}

void Energy::availableInc(const float amount) {
  float new_available = available_ + amount;
  if (new_available > max_)
    available_ = max_;
  else
    available_ = new_available;
}

void Energy::availableDec(const float amount) {
  if (amount >= available_)
    available_ = 0.0f;
  else
    available_ -= amount;

  if (available_ < strength_)
    strength_ = available_;
}

float Energy::strength() const {
  return strength_;
}

float Energy::strengthAsPercentOfMax() const {
  return strength_ / max_;
}

void Energy::strengthIs(const float amount) {
  strength_ = amount;
  if (strength_ > available_)
    available_ = strength_;
    if (strength_ > max_)
      max_ = strength_;
}

void Energy::strengthInc(const float amount) {
  float new_strength = strength_ + amount;
  if (new_strength > available_)
    strength_ = available_;
  else
    strength_ = new_strength;
}

void Energy::strengthDec(const float amount) {
  if (amount >= strength_)
    strength_ = 0.0f;
  else
    strength_ -= amount;
}

//void Energy::Recover(float amount, float percent) {
//  //if (available_ == max_) return;
//
//  //float new_available(available_ + amount);
//  //float new_max(max_ + amount * float(percent.value()));
//  //if (new_available <= new_max) {
//  //  available_ = new_available;
//  //  max_ = new_max;
//  //} else {
//  //  // In the case of available energy going over max energy we need to find
//  //  // the amount that pushes it exactly to max.
//  //  float new_amount((max_ - available_) / float(1 - percent.value()));
//  //  available_ += new_amount;
//  //  max_ = available_;
//  //}
//
//  //if (isInf(max_.value())) available_ = max_;
//}

std::string Energy::String(uint32_t len) {
  std::stringstream ss;
  ss << strength_ << "|" << available_ << "|"
     << max_ << " : ";
  if (len > 0) {
    uint32_t strength_len =
      (uint32_t) (strengthAsPercentOfMax() * len);
    uint32_t available_len =
      (uint32_t) (availableAsPercentOfMax() * len);
    for (uint32_t i = 0; i <= len; i++) {
      if (i <= strength_len || isInf(strength_))
        ss << "1";
      else if (i <= available_len)
        ss << "2";
      else
        ss << "3";
    }
  }
  return ss.str();
  return "energy...";
}
