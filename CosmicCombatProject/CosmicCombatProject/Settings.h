/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_SETTINGS_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_SETTINGS_H_

#include <Box2D\Box2D.h>
#include <string>

const bool kDebugMode = true;

//const char *kWindowTitle = "Cosmic Combat";

const int32 kPixelsPerMeter = 16;

const float32 kMinTimeStep = 1.0f / 240.0f;
const int32 kVelocityIterations = 6;
const int32 kPositionIterations = 2;

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_SETTINGS_H_
