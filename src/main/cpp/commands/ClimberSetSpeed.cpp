/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberSetSpeed.h"

#include "subsystems/Climber.h"

ClimberSetSpeed::ClimberSetSpeed() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Climber::getInstance().get());
}

// Called just before this Command runs the first time
void ClimberSetSpeed::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberSetSpeed::Execute() {
  Climber::getInstance()->MotorClimber(-0.3);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberSetSpeed::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberSetSpeed::End() {
  Climber::getInstance()->MotorClimber(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberSetSpeed::Interrupted() {
  Climber::getInstance()->MotorClimber(0);
}
