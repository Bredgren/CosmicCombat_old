/* Copyright 2013 - Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_COMBOTRACKER_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_COMBOTRACKER_H_

#include <stdint.h>

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

/// A general key combo tracker.
/**
    Allows the user to use a string to represent a combo as a sequence charaters.
    The user also specifies what happens when one of the registered combos is
    achieved. Multiple systems for combos are supported and they are watched
    simultaniously, so it is possible for a combo from each system to be achieved
    at the same time.
   
   Two types of combo systems are supported:
    - MODE0: All buttons of the combo are pressed in the correct order and are 
      all held simultaniously. If the combo is achieved it will continue to be
      considered so until the last key of the combo is lifted regardless of
      what happens to the other keys of the combo. Note that combos that 
      sequences with keys that appear more than once do not make sense here and,
      indeed, will not work.
    - MODE1: All buttons of the combo are pressed in the correct order but they 
      do not have to be held simultaniously. If the combo is achieved it will continue to be
      considered so until the last key of the combo is lifted regardless of
      what happens to the other keys of the combo.
 */
class ComboTracker {
 public:
  /**
      This is the type of function that will be called when a combo is achevied. 
      @param sequence the combo that was completed.
      @param time the time in milliseconds between the first and last key.
   */
  typedef void (*callback)(const string sequence, const uint32_t time);

  /** Possible modes to use */
  enum MODE {
    MODE0,
    MODE1
  };

  ComboTracker(void);
  virtual ~ComboTracker(void);

  /// Adds a combo to look for.
  /**
      There is no way to unregister a combo because I can't imagine when you
      would want it, just stop restonding to the combo if you need to.
      @param sequence the sequence of characters of the combo.
      @param mode the mode to attach the sequence to.
   */
  void RegisterCombo(const string sequence, const MODE mode);

  /// Sets the callback function
  /** 
      Specifies the function to call when a combo has been achieved. The default
      function printf's the paramaters that the callback takes.
      @param func a pointer to the function to call.
   */
  void OnComboComplete(const callback func);

  /// Tells the ComboTracker that a key has been pressed.
  /**
      Tells the ComboTracker when a key was pressed and which one. Note that the
      callback function will not be called during this method.
      @param key the key that wash pushed.
      @param time the current time in milliseconds.
   */
  void KeyDown(const int8_t key, const uint32_t time);

  /// Tells the ComboTracker that a key has been lifted.
  /**
      Tells the ComboTracker when a key was lifted and which one. Note that the
      callback function will not be called during this method.
      @param key the key that wash lifted.
      @param time the current time in milliseconds.
   */
  void KeyUp(const int8_t key, const uint32_t time);

  /// Checks whether any combos are currently being completed.
  /**
      If a combo is currently being completed this will call the function given
      to OnComboComplete.
   */
  void CheckCombos();

  /// Resets the combo for the given mode.
  /**
      This can be useful if you want something to only happen once when a combo
      is completed.
      @param mode the mode to reset.
   */
  void ResetCombo(MODE mode);

  /** @return a string representation of the state of each combo mode */
  string ToString() const;

 private:
  /* The ComboTree is a tree that represents a set of combos */
  class ComboTree {
   public:
    ComboTree() : root_(new ComboNode(0)),
                  current_(root_),
                  current_combo_("") {}
    virtual ~ComboTree(void);

    void AddSequence(const string sequence);

    /* Advances the combo by the given key if there is an extension of the
       current combo whoes next value is the key. Returns true if the
       advancment was successful.
     */
    bool Advance(const int8_t key);

    /* Resets the current state of the combo back to the beginning */
    void Restart();

    /* Returnst whether the combo is at the start node, meaning there is no
       current progress on any combo
     */
    bool AtStart();

    string current_combo() const { return current_combo_; }

    string ToString() const;

   private:
    /* A node in the ComboTree */
    class ComboNode {
     public:
      explicit ComboNode(int8_t data) : data_(data) {}
      virtual ~ComboNode(void);
      void AddChild(ComboNode *node);
      bool HasChild(const int8_t key);
      int8_t data() const { return data_; }
      unordered_map<int8_t, ComboNode*> children() const { return children_; }
     private:
      int8_t data_;
      unordered_set<int8_t> children_data_;
      unordered_map<int8_t, ComboNode*> children_;
    };

    string ComboTreeToStringHelper_(const ComboNode *node) const;

    ComboNode *root_;
    ComboNode *current_;
    string current_combo_;
  };

  vector<ComboTree> mode_trees_;
  vector<unordered_set<string>> mode_combos_;
  vector<int32_t> mode_start_times_;
  vector<int32_t> mode_end_times_;

  callback OnComboComplete_;
};

std::ostream &operator<<(std::ostream &out, const ComboTracker &ct);

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_COMBOTRACKER_H_
