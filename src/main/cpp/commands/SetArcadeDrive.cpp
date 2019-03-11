/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArcadeDrive.h"
#include "subsystems/Chassis.h"
#include "OI.h"

SetArcadeDrive::SetArcadeDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Chassis::getInstance().get());
}

// Called just before this Command runs the first time
void SetArcadeDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetArcadeDrive::Execute() {
  constexpr double kMaxSpeed {0.75};
  double left = OI::getInstance()->getDriverLeftYAxis();
  Chassis::getInstance()->SetArcadeDrive(left * kMaxSpeed, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool SetArcadeDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void SetArcadeDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetArcadeDrive::Interrupted() {}
