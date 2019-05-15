/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberDrive.h"
#include "subsystems/Climber.h"
#include "OI.h"

ClimberDrive::ClimberDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Climber::getInstance().get());
}

// Called just before this Command runs the first time
void ClimberDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberDrive::Execute() {  
  double left = OI::getInstance()->getDriverLeftYAxis();
  Climber::getInstance()->DriveClimb(left);
  Climber::getInstance()->MotorClimber(-0.3);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDrive::Interrupted() {}
