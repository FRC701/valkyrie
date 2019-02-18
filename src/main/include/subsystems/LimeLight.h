/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

class LimeLight : public frc::Subsystem {
 private:

 public:
  LimeLight();
  void InitDefaultCommand() override;
  void GetVariables();
  void GetDistanceToTargetInches();
  double GetTargetAngle();
  void SetPath();
};
