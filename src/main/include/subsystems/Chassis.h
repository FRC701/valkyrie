#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/CANSparkMax.h"

class Chassis: public frc::Subsystem {
private:

  static const char kSubsystemName[];
  static std::shared_ptr<Chassis> self;

  rev::CANSparkMax right1Wheel;
  rev::CANSparkMax right2Wheel;
  rev::CANSparkMax left1Wheel;
  rev::CANSparkMax left2Wheel;

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
