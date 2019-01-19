/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include "frc/DoubleSolenoid.h"

class CargoCarriage : public frc::Subsystem {
 private:
  static const char kSubsystemName[];
  static std::shared_ptr<CargoCarriage> self;
  frc::DoubleSolenoid mPuncher;
  frc::DoubleSolenoid mLeftHook;
  frc::DoubleSolenoid mRightHook;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  static std::shared_ptr<CargoCarriage> getInstance();
  CargoCarriage();
  void InitDefaultCommand() override;
  void Engage();
  void Disengage();
  void Punch();
  void PullBack();
};
