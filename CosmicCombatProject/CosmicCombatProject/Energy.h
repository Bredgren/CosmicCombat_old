/* Copyright 2013 - Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_

#include <stdint.h>

class Energy;

/// Represents the energy of something/someone.
/**
    There are 3 values that make up the system:
     - Max energy: The highest the energy can be
     - Available energy: The actual amount of energy currently available
     - Strength: Determines the effectiveness in using energy

    These levels share this relationship which is always maintained:
      Max >= Available >= Strength >= 0
 */
class Energy {
 public:
  /// Initializes all levels to the given argument.
  /**
      @param max the value to set all the levels to.
   */
  explicit Energy(const float max) :
    max_(max),
    available_(max),
    strength_(max) {}
  Energy() { Energy(100); }

  virtual ~Energy(void);

  /// The maximum energy.
  /**
      Supports -Is, -Inc and -Dec
   */
  float max() const;
  void maxIs(const float amount);
  void maxInc(const float amount);
  void maxDec(const float amount);

  /// The energy currently available.
  /**
      Supports -Is, -Inc, -Dec, and -AsPercentOfMax
   */
  float available() const;
  void availableIs(const float amount);
  void availableInc(const float amount);
  void availableDec(const float amount);
  float availableAsPercentOfMax() const;

  /// The current strength.
  /**
      Supports -Is, -Inc, -Dec, and -AsPercentOfMax
   */
  float strength() const;
  void strengthIs(const float amount);
  void strengthInc(const float amount);
  void strengthDec(const float amount);
  float strengthAsPercentOfMax() const;

  ///// Increases the available energy and the maximum energy.
  ///**
  //    The available energy is increased by the given amount but not past the
  //    maximum energy. The maximum energy is increased by the given percent of
  //    the amount that the available energy is increased by.
  //    @param amount how much to encreas the available energy by.
  //    @param percent the percent of the amount that the available energy is
  //           increased by to increase the maximum energy by.
  // */
  //void Recover(float amount, float percent);

  /// Returns string representation for testing.
  /**
      If len > 0 then a ascii graphic with length len is displayed along with
      the numbers.
      @param len how many characters wide the graphic will be.
      @return a string representation of the energy levels.
   */
  std::string String(const uint32_t len = 0);

 private:
  float max_;
  float available_;
  float strength_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_
