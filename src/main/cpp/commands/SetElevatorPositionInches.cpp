/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetElevatorPositionInches.h"

#include "subsystems/Elevator.h"

SetElevatorPositionInches::SetElevatorPositionInches(double inches): mInches(inches) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Elevator::getInstance().get());
}

// Called just before this Command runs the first time
void SetElevatorPositionInches::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetElevatorPositionInches::Execute() {
  Elevator::getInstance()->SetElevatorPositionInches(mInches);
}

// Make this return true when this Command no longer needs to run execute()
bool SetElevatorPositionInches::IsFinished() { return true; }

// Called once after isFinished returns true
void SetElevatorPositionInches::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevatorPositionInches::Interrupted() {}
