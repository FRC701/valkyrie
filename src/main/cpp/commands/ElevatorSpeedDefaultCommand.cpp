/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSpeedDefaultCommand.h"

#include "subsystems/Elevator.h"

#include "OI.h"

ElevatorSpeedDefaultCommand::ElevatorSpeedDefaultCommand() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Elevator::getInstance().get());
}

// Called just before this Command runs the first time
void ElevatorSpeedDefaultCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorSpeedDefaultCommand::Execute() {
  double left = -OI::getInstance()->getCoDriverLeftYAxis();
  Elevator::getInstance()->SetElevatorSpeed(left*0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSpeedDefaultCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorSpeedDefaultCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSpeedDefaultCommand::Interrupted() {}
