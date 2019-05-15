/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetHatchIntakeSpeedDefaultCommand.h"
#include "commands/HatchIntakeSpeedDefaultCommand.h"
#include "subsystems/HatchIntake.h"

SetHatchIntakeSpeedDefaultCommand::SetHatchIntakeSpeedDefaultCommand()
: mCommand(nullptr) 
{
  // Use Requires() here to declare subsystem dependencies
  Requires(HatchIntake::getInstance().get());
}

frc::Command* SetHatchIntakeSpeedDefaultCommand::getCommand()
{
  if ( ! mCommand)
  {
    mCommand = new HatchIntakeSpeedDefaultCommand;
  }
  return mCommand;
}

// Called once when the command executes
void SetHatchIntakeSpeedDefaultCommand::Initialize() {
  HatchIntake::getInstance()->SetDefaultCommand(getCommand());
}
