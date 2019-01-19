/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "commands/MotorClimb.h"
#include "subsystems/Climber.h"

MotorClimb::MotorClimb() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Climber::getInstance().get());
}

// Called just before this Command runs the first time
void MotorClimb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MotorClimb::Execute() {
  Climber::getInstance()->MotorClimb(0.3);
}

// Make this return true when this Command no longer needs to run execute()
bool MotorClimb::IsFinished() { return false; }

// Called once after isFinished returns true
void MotorClimb::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MotorClimb::Interrupted() {}
