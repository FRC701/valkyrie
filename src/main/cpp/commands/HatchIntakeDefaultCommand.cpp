/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchIntakeDefaultCommand.h"
#include "subsystems/HatchIntake.h"

HatchIntakeDefaultCommand::HatchIntakeDefaultCommand() 
: mHatchIntake(HatchIntake::getInstance()) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(mHatchIntake.get());
}

// Called just before this Command runs the first time
void HatchIntakeDefaultCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchIntakeDefaultCommand::Execute() {
  constexpr double kMaxArmCurrent { 25 };
  if (mHatchIntake->GetCurrent() > kMaxArmCurrent) {
    mHatchIntake->ResetPosition();
  } else {
    mHatchIntake->UpdatePosition();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchIntakeDefaultCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchIntakeDefaultCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchIntakeDefaultCommand::Interrupted() {}
