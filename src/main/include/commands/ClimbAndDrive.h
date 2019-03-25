/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "commands/MotorClimb.h"

class ClimbAndDrive : public MotorClimb {
 public:
  using Super = MotorClimb;
  ClimbAndDrive(double speed, double encoderFinish);
  void Execute() override;
};
