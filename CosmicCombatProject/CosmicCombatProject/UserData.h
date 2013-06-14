/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_USERDATA_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_USERDATA_H_

enum DataType {
  kNone,
  kCharacter,
  kCharacterTarget
};

struct UserData {
  DataType type;
  void *data;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_USERDATA_H_
