/* Copyright 2013 - Brandon Edgren */
#ifndef COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_
#define COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_

#include <stdint.h>

#include <cfloat>
#include <string>

/// Keeps track of and interacts with energy levels.
/**
    This class represents the energy levels of something. There are 4 levels
    that make up the system:
     - Aboslute Max: The highest current limit
     - Battle Recovery Point: The amount that can be recovered during battle
     - Active Max: The maximum currently available for use
     - Active: The amount actually available for use

    These levels share this relationship which is always maintained:
     Absolute Max >= Battle Recovery Point >= Active Max >= Active >= 0
 */
class Energy {
 public:
  /// Initializes all levels to the given argument.
  /**
      @param abs_max the value to set all the levels to.
   */
  explicit Energy(const float abs_max) :
    absolute_max_(abs_max),
    battle_point_(abs_max),
    active_max_(abs_max),
    active_(abs_max) {}

  virtual ~Energy(void);

  /* Normal Behaviors */

  /// Increases the Active level.
  /** 
      Increases the Active level by the given amount, up to Active Max. 
      Amounts less than 0 are treated as 0.
      @param amount the amount to raise the Active level by.
   */
  void PowerUp(const float amount);

  /// Decreases the Active level.
  /**
      Decreases the Active level by the given amount, but not past 0. 
      Amounts less than 0 are treated as 0.
      @param amount the amont to lower the Active level by.
   */
  void PowerDown(const float amount);

  /// Requests using energy.
  /** 
      This is meant to represent an entity using its energy of its own will,
      such as using an attack. The amount you can use is bound between 0 and the
      Active level. if you request an amount between that range then that same
      amount is returned, otherwise the closest edge of that bound is used and
      then returned. Using energy results in Active Max decreasing by the amount
      that was used and in Battle Recovery Point decreasing by an amount related
      to recovery_percentage and the amount used.
     @param amount the amount of energy you would like to use.
     @param recovery_percentage the percentage of the energy used that can
            be recovered in battle.
     @return the amount of energy that was actually used.
   */
  float UseEnergy(const float amount, const float recovery_percentage);

  /// Forces the loss of energy.
  /** 
      This is meant to represent an entity using it's energy not of its own will,
      such as taking a hit from an enemy. Expending energy results in Active Max
      decreasingby the amount given, which if less than 0 will be treated as 0.
      It also causes Battle Recovery Point decreasing by an amount related
      to recovery_percentage and the amount given (note that it's not the amount
      used).
      @param amount the amount of energy you would like to expend.
      @param recovery_percentage the percentage of the energy given that can
             be recovered in battle.
   */
  void ExpendEnergy(const float amount,
                            const float recovery_percentage);

  /// Increases the Active Max level.
  /** 
      This this the first method of energy recovery where the amount recovered
      is bound by Battle Recovery Point. Increases Active Max by the given
      amount, up to Battle Recovery Point. Amounts less than 0 are treated as 0.
      @param amount the amount to increase Active Max by.
   */
  void Recover(const float amount);

  /// Increases the Active Max level and the Aboslute Max level.
  /** 
      This is the second method of energy recovery where the amount recovered
      is only bound by Aboslute Max. For each unit that Active Max goes past
      Battle Recovery Point, Aboslute Max goes up by percent_gain of that unit.
      Amounts less than 0 are treated as 0, and perecnt_gain will be bound
      between 0 and the largest number less than 1.
      @param amount the amount to increase Active Max by.
      @param percent_gain how much Aboslute Max increases per unit that Active
                          Max increases past Battle Recovery Point.
   */
  void Rest(const float amount, const float percent_gain);

  /* Setters */

  /** @param abs_max the value to set Absolute Max at. */
  void set_absolute_max(const float abs_max);
  /** @param battle_point the value to set attle Recovery Point at. */
  void set_battle_point(const float battle_point);
  /** @param active_max the value to set Active Max at. */
  void set_active_max(const float active_max);
  /** @param active the value to set Active at. */
  void set_active(const float active);

  /// Sets the flag for whether Battle Recovery Point has reached 0.
  void set_reached_energy_0(const bool val) { reached_energy_0_ = val; }

  /* Getters */

  /** @return the current level of Absolute Max. */
  float absolute_max() const { return absolute_max_; }
  /** @return the current level of Battle Recovery Point. */
  float battle_point() const { return battle_point_; }
  /** @return the current level of Active Max. */
  float active_max() const { return active_max_; }
  /** @return the current level of Active. */
  float active() const { return active_; }

  /** @return Battle Recovery Point as a percent of Absolute Max */
  float battle_point_percent() const
          { return battle_point_ / absolute_max_; }
  /** @return Active Max as a percent of Absolute Max */
  float active_max_percent() const
          { return active_max_ / absolute_max_; }
  /** @return Active as a percent of Absolute Max */
  float active_percent() const { return active_ / absolute_max_; }

  /** @return whether Battle Recovery Point ever reached 0 */
  bool reached_energy_0() const { return reached_energy_0_; }

  /* For testing */

  /**
      If len > 0 then a ascii graphic with length len is displayed along with
      the numbers.
      @param len how many characters wide the graphic will be.
      @return a string representation of the energy levels.
   */
  std::string ToString(const uint32_t len = 0);

 private:
  /* maintains the relationship starting from the top */
  void maintain_relationship_top_();
  /* maintains the relationship starting from the bottom */
  void maintain_relationship_bottom_();

  float absolute_max_;
  float battle_point_;
  float active_max_;
  float active_;

  bool reached_energy_0_;
};

#endif  // COSMICCOMBATPROJECT_COSMICCOMBATPROJECT_ENERGY_H_
