/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchCargoSelector.h"

#include "OI.h"

#include "frc/Commands/Scheduler.h"

HatchCargoSelector::HatchCargoSelector(
 frc::Command* hatchControls,
 frc::Command* cargoControls):
 mHatchCommand(hatchControls),
 mCargoCommand(cargoControls)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void HatchCargoSelector::Initialize() {
  Command* command 
    = OI::getInstance()->isHatch()
    ? mHatchCommand : mCargoCommand;
  frc::Scheduler::GetInstance()->AddCommand(command);
}

// Called repeatedly when this Command is scheduled to run
void HatchCargoSelector::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool HatchCargoSelector::IsFinished() { return true; }

// Called once after isFinished returns true
void HatchCargoSelector::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchCargoSelector::Interrupted() {}
