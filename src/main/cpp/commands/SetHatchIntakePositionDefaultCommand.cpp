/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetHatchIntakePositionDefaultCommand.h"
#include "subsystems/HatchIntake.h"
#include "commands/SetHatchIntakePositionDefaultCommand.h"


SetHatchIntakePositionDefaultCommand::SetHatchIntakePositionDefaultCommand()
: mCommand(new SetHatchIntakePositionDefaultCommand) {
  // Use Requires() here to declare subsystem dependencies
  Requires(HatchIntake::getInstance().get());
}

// Called once when the command executes
void SetHatchIntakePositionDefaultCommand::Initialize() {
  HatchIntake::getInstance()->SetDefaultCommand(mCommand);
}
