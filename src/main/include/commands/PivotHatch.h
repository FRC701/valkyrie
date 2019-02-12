/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/InstantCommand.h>

class PivotHatch : public frc::InstantCommand {
private:
  double mSpeed;
 public:
  PivotHatch(double speed);
  void Initialize() override;
  bool IsFinished() override;
};
