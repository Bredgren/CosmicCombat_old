/* Copyright 2013 - Brandon Edgren */

#include "stdafx.h"
#include <sstream>
#include <stdexcept>
#include <string>

#include "./Energy.h"

namespace cc {

bool isInf(float x) {
    return x > FLT_MAX || x < -FLT_MAX;
}

Energy::~Energy(void) {
}

void Energy::PowerUp(float amount) {
  if (amount < 0) amount = 0;

  float new_active = active_ + amount;
  if (new_active > active_max_)
    active_ = active_max_;
  else
    active_ = new_active;

  if (amount == 0)
    reached_energy_0_ = true;
  else
    reached_energy_0_ = false;
}

void Energy::PowerDown(float amount) {
  if (amount < 0) amount = 0;

  float new_active = active_ - amount;
  if (new_active < 0)
    active_ = 0;
  else
    active_ = new_active;
}

float Energy::UseEnergy(float amount, float recovery_percentage) {
  if (amount < 0) amount = 0;
  else if (amount > active_) amount = active_;
  if (recovery_percentage > 1) recovery_percentage = 1;
  else if (recovery_percentage < 0) recovery_percentage = 0;

  float recoverable = amount * recovery_percentage;

  set_active_max(active_max_ - amount);
  set_battle_point(battle_point_ - amount + recoverable);

  return amount;
}

void Energy::ExpendEnergy(float amount, float recovery_percentage) {
  if (amount < 0) amount = 0;
  if (recovery_percentage > 1) recovery_percentage = 1;
  else if (recovery_percentage < 0) recovery_percentage = 0;

  float battle_loss = amount - amount * recovery_percentage;
  if (battle_loss >= battle_point_)
    reached_energy_0_ = true;

  float recoverable = amount * recovery_percentage;

  set_active_max(active_max_ - amount);
  set_battle_point(battle_point_ - battle_loss);
}

void Energy::Recover(float amount) {
  if (amount < 0) amount = 0;

  float new_active_max = active_max_ + amount;
  if (new_active_max > battle_point_)
    active_max_ = battle_point_;
  else
    active_max_ = new_active_max;
}

void Energy::Rest(float amount, float percent_gain) {
  if (amount < 0) amount = 0;
  if (percent_gain < 0) percent_gain = 0;
  else if (percent_gain >= 1) percent_gain = 1 - FLT_EPSILON;

  if (active_max_ == absolute_max_) return;

  // Because Aboslute Max increases for each unit that Active Max increases
  // PAST Battle Recovery Point, there is an edge case where increasing Active
  // Max brings it past Battle Recovery Point, which means only some of it
  // contributes to the increase of Aboslute Max.
  float new_absolute_max = absolute_max_;
  if (active_max_ == battle_point_)  // if it's already at battle point
    new_absolute_max = absolute_max_ + amount * percent_gain;
  else if (active_max_ + amount > battle_point_)  // if raising it moves it past
    new_absolute_max = absolute_max_ + (active_max_ + amount - battle_point_) *
                       percent_gain;
  set_absolute_max(new_absolute_max);

  float new_active_max = active_max_ + amount;
  if (new_active_max > absolute_max_)
    set_active_max(absolute_max_);
  else
    set_active_max(new_active_max);

  // If somehow Aboslute Max is raised passed the maximum floating point value
  // and becomes infinity, just set every level to infinity.
  if (isInf(absolute_max_))
    set_active(absolute_max_);
}

void Energy::set_absolute_max(float abs_max) {
  if (abs_max < 0) abs_max = 0;

  if (abs_max > absolute_max_) {
    absolute_max_ = abs_max;
  } else {
    absolute_max_ = abs_max;
    maintain_relationship_top_();
  }
}

void Energy::set_battle_point(float battle_point) {
  if (battle_point < 0) battle_point = 0;

  if (battle_point > battle_point_) {
    battle_point_ = battle_point;
    maintain_relationship_bottom_();
  } else {
    battle_point_ = battle_point;
    maintain_relationship_top_();
  }
}

void Energy::set_active_max(float active_max) {
  if (active_max < 0) active_max = 0;

  if (active_max > active_max_) {
    active_max_ = active_max;
    maintain_relationship_bottom_();
  } else {
    active_max_ = active_max;
    maintain_relationship_top_();
  }
}

void Energy::set_active(float active) {
  if (active < 0) active = 0;

  if (active > active_) {
    active_ = active;
    maintain_relationship_bottom_();
  } else {
    active_ = active;
    maintain_relationship_top_();
  }
}

void Energy::maintain_relationship_top_() {
  if (absolute_max_ < battle_point_)
    battle_point_ = absolute_max_;
  if (battle_point_ < active_max_)
    active_max_ = battle_point_;
  if (active_max_ < active_)
    active_ = active_max_;
}

void Energy::maintain_relationship_bottom_() {
  if (active_ > active_max_)
    active_max_ = active_;
  if (active_max_ > battle_point_)
    battle_point_ = active_max_;
  if (battle_point_ > absolute_max_)
    absolute_max_ = battle_point_;
}

std::string Energy::ToString(uint32_t len) {
  std::stringstream ss;
  ss << active_ << "|" << active_max_ << "|" << battle_point_
     << "|" << absolute_max_ << " : ";
  if (len > 0) {
    uint32_t active_len = (uint32_t) (active_ / absolute_max_ * len);
    uint32_t active_max_len = (uint32_t) (active_max_ / absolute_max_ * len);
    uint32_t battle_len = (uint32_t) (battle_point_ / absolute_max_ * len);
    for (uint32_t i = 0; i <= len; i++) {
      if (i <= active_len || isInf(active_))
        ss << "1";
      else if (i <= active_max_len)
        ss << "2";
      else if (i <= battle_len)
        ss << "3";
      else
        ss << "4";
    }
  }
  return ss.str();
}
}  // namespace cc
