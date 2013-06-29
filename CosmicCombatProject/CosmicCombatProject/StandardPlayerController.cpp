/* Copyright 2013 Brandon Edgren */

#include "./StandardPlayerController.h"
#include "./Util.h"

StandardPlayerController::StandardPlayerController() {
  combo_tracker_.OnComboComplete(this);
  combo_tracker_.RegisterCombo("abc", ComboTracker::MODE0);
}


StandardPlayerController::~StandardPlayerController(void) {
}

void StandardPlayerController::OnComboComplete(string sequence, uint32_t time) {
  printf("combo complete: %s\n", sequence.c_str());
  combo_tracker_.ResetCombo(ComboTracker::MODE0);
}

void StandardPlayerController::ProcessEvent(sf::Event event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed:
      //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      break;
    case sf::Event::MouseButtonReleased:
      //if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
      break;
    case sf::Event::MouseMoved:
      break;
    case sf::Event::KeyPressed:
      printf("key down: %d / %c\n", event.key.code, CodeToChar(event.key.code));
      combo_tracker_.KeyDown(CodeToChar(event.key.code), 0);
      break;
    case sf::Event::KeyReleased:
      printf("key up: %d / %c\n", event.key.code, CodeToChar(event.key.code));
      combo_tracker_.KeyUp(CodeToChar(event.key.code), 0);
      break;
    default:
      break;
  }
}

void StandardPlayerController::Tick() {
  combo_tracker_.CheckCombos();
}
