/* Copyright 2013 - Brandon Edgren */

#include <sstream>
#include <string>
#include <vector>

#include "./ComboTracker.h"

using std::endl;
using std::stringstream;

ComboTracker::ComboTree::ComboNode::~ComboNode(void) {
  for (unordered_map<int8_t, ComboNode*>::iterator it = children_.begin();
    it != children_.end(); it++)
      delete it->second;
}

void ComboTracker::ComboTree::ComboNode::AddChild(ComboNode *node) {
  children_data_.insert(node->data());
  children_[node->data()] = node;
}

bool ComboTracker::ComboTree::ComboNode::HasChild(const int8_t key) {
  return children_data_.count(key) == 1;
}

ComboTracker::ComboTree::~ComboTree(void) {
  delete root_;
}

void ComboTracker::ComboTree::AddSequence(const string sequence) {
  ComboNode *current = root_;
  for (int8_t c : sequence) {
    if (!current->HasChild(c))
      current->AddChild(new ComboNode(c));
    current = current->children()[c];
  }
}

bool ComboTracker::ComboTree::Advance(const int8_t key) {
  if (!current_->HasChild(key))
    return false;

  current_ = current_->children()[key];
  current_combo_ += key;
  return true;
}

void ComboTracker::ComboTree::Restart() {
  current_ = root_;
  current_combo_ = "";
}

bool ComboTracker::ComboTree::AtStart() {
  return current_ == root_;
}

string ComboTracker::ComboTree::ToString() const {
  return ComboTreeToStringHelper_(root_);
}

string ComboTracker::ComboTree::ComboTreeToStringHelper_(
  const ComboNode *node) const {
  unordered_map<int8_t, ComboNode*> m = node->children();
  stringstream ret;
  ret << node->data();
  if (node == current_)
      ret << "*";
  if (!m.empty()) {
    ret << "(";
    for (unordered_map<int8_t, ComboNode*>::iterator it = m.begin();
      it != m.end(); it++) {
      ret << ComboTreeToStringHelper_(it->second) << " ";
    }
    ret << ")";
  }
  return ret.str();
}

void DefaultCallback_(string sequence, uint32_t time) {
  printf("combo %s completed in %u ms\n", sequence.c_str(), time);
}

ComboTracker::ComboTracker(void)
  : mode_trees_(2), mode_combos_(2),
    mode_start_times_(2), mode_end_times_(2) {
  OnComboComplete_ = DefaultCallback_;
}

ComboTracker::~ComboTracker(void) {
}

void ComboTracker::RegisterCombo(const string sequence, const MODE mode) {
  mode_trees_[mode].AddSequence(sequence);
  mode_combos_[mode].insert(sequence);
}

void ComboTracker::OnComboComplete(const callback func) {
  OnComboComplete_ = func;
}

void ComboTracker::OnComboComplete(ComboTrackerUser *user) {
  user_ = user;
}

void ComboTracker::KeyDown(const int8_t key, const uint32_t time) {
  int32_t mode = 0;
  for (vector<ComboTree>::iterator it = mode_trees_.begin();
       it != mode_trees_.end(); it++) {
    if (it->AtStart())
      mode_start_times_[mode] = time;
    mode_end_times_[mode] = time;
    // For modes 0 and 1, if the key does not advance the combo then it is not
    // part of a combo and we need to restart.
    if (mode == 0 || mode == 1)
      if (!it->Advance(key)) {
        it->Restart();
        // Advance again so the key isn't ignored
        it->Advance(key);
      }
    mode++;
  }
}

void ComboTracker::KeyUp(const int8_t key, const uint32_t time) {
  // For mode 0, if any key is lifted then the combo is failed unless a
  // combo is being completed, in which case it doesn't stop until the
  // last key is lifted.
  bool mode0_complete = mode_combos_[0].count(mode_trees_[0].current_combo())
                        == 1;
  if ((mode0_complete && key == mode_trees_[0].current_combo().back()) ||
      !mode0_complete)
    mode_trees_[0].Restart();

  // For mode 1, if the last key of the combo is lifted then it's over
  if (mode_combos_[1].count(mode_trees_[1].current_combo()) &&
      key == mode_trees_[1].current_combo().back())
    mode_trees_[1].Restart();
}

void ComboTracker::CheckCombos() {
  int32_t mode = 0;
  for (vector<ComboTree>::iterator it = mode_trees_.begin();
       it != mode_trees_.end(); it++) {
    string sequence = it->current_combo();
    uint32_t time = mode_end_times_[mode] - mode_start_times_[mode];
    if (mode_combos_[mode].count(sequence) && user_ != NULL) {
      user_->OnComboComplete(sequence, time);
    }
    mode++;
  }
}

void ComboTracker::ResetCombo(MODE mode) {
  mode_trees_[mode].Restart();
}

string ComboTracker::ToString() const {
  stringstream ret;
  uint32_t i = 0;
  for (vector<ComboTree>::const_iterator it = mode_trees_.begin();
       it != mode_trees_.end(); it++) {
    ret << "mode" << i << ": " << it->ToString();
    if (i < mode_trees_.size() - 1)
      ret << endl;
    i++;
  }
  return ret.str();
}

std::ostream &operator<<(std::ostream &out, const ComboTracker &ct) {
  return out << ct.ToString();
}
