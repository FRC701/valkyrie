/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "commands/SetClimbMotorSpeed.h"

class ClimbAndDrive : public SetClimbMotorSpeed {
 public:
  using Super = SetClimbMotorSpeed;
  ClimbAndDrive(double speed);
  void Execute() override;
};
