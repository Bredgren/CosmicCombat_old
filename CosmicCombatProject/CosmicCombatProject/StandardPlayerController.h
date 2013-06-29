/* Copyright 2013 Brandon Edgren */

#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_

#include <string>
#include <vector>

#include "./CharacterController.h"
#include "./ComboTracker.h"

class StandardPlayerController
  : public CharacterController, public ComboTrackerUser {
 public:
  explicit StandardPlayerController();
  virtual ~StandardPlayerController(void);

  void OnComboComplete(string sequence, uint32_t time);

  void ProcessEvent(sf::Event event);

  void Tick();

 private:
  ComboTracker combo_tracker_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_STANDARDPLAYERCONTROLLER_H_
