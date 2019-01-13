/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/InstantCommand.h>
#include "subsystems/HatchIntake.h"

class HatchPuncherDisengage : public frc::InstantCommand {
 public:
  HatchPuncherDisengage();
  void Initialize() override;
};
