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
#include "ctre/Phoenix.h"

class CargoIntake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
    static const char kSubsystemName[];
  static std::shared_ptr<CargoIntake> self;
 frc::DoubleSolenoid squeezer;
 WPI_TalonSRX roller;

 public:
  CargoIntake();
  static std::shared_ptr<CargoIntake> getInstance();
  void InitDefaultCommand() override;
  void Squeeze();
  void OpenSqueeze();
  void SetCargoRoller(double speed);
  bool IsCargoIn();
};
