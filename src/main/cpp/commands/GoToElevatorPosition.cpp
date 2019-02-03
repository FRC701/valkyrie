/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GoToElevatorPosition.h"
#include "subsystems/Elevator.h"

GoToElevatorPosition::GoToElevatorPosition(double position): mPosition(position) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Elevator::getInstance().get());
}

// Called just before this Command runs the first time
void GoToElevatorPosition::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void GoToElevatorPosition::Execute() {
  Elevator::getInstance()->SetElevatorPos(mPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool GoToElevatorPosition::IsFinished() {     
  return Elevator::getInstance()->IsRevLimitSwitchClosed();
 }

// Called once after isFinished returns true
void GoToElevatorPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GoToElevatorPosition::Interrupted() {}
