/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchIntakeSpeedDefaultCommand.h"
#include "subsystems/HatchIntake.h"
#include "OI.h"

HatchIntakeSpeedDefaultCommand::HatchIntakeSpeedDefaultCommand() {
  // Use Requires() here to declare subsystem dependencies
  Requires(HatchIntake::getInstance().get());
}

// Called just before this Command runs the first time
void HatchIntakeSpeedDefaultCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchIntakeSpeedDefaultCommand::Execute() {
  double right = OI::getInstance()->getDriverRightYAxis();  
  HatchIntake::getInstance()->Pivot(right);
}

// Make this return true when this Command no longer needs to run execute()
bool HatchIntakeSpeedDefaultCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchIntakeSpeedDefaultCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchIntakeSpeedDefaultCommand::Interrupted() {}