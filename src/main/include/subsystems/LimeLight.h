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
 
  static const char kSubsystemName[];
  static std::shared_ptr<LimeLight> self;

 public:

  static std::shared_ptr<LimeLight> getInstance();


  LimeLight();
  void InitDefaultCommand() override;
  void SetVariables();
  double GetTargetArea();
  double GetLargeTargetArea();
  double GetSmallTargetArea();
  double GetTargetOffset();
  double GetLargeTargetOffset();
  double GetSmallTargetOffset();
  double GetDistanceToTargetInches();
  double GetTargetAngle();
  void SetPath();
};
