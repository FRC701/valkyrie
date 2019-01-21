#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/SparkMax.h"

class Chassis: public frc::Subsystem {
private:

  static const char kSubsystemName[];
  static std::shared_ptr<Chassis> self;

  rev::SparkMax right1Wheel;
  rev::SparkMax right2Wheel;
  rev::SparkMax left1Wheel;
  rev::SparkMax left2Wheel;

 public:
  

  static std::shared_ptr<Chassis> getInstance();

  Chassis();

  void InitDefaultCommand();

  void SetTankDrive(double left, double right);
  void SetCoast();
  void SetBrake();
  void SetupDrive();
  void SetUpSpark(); 

};
