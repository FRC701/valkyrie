/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetElevatorSpeedDefaultCommand.h"
#include "subsystems/Elevator.h"

SetElevatorSpeedDefaultCommand::SetElevatorSpeedDefaultCommand() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Elevator::getInstance().get());
}

// Called once when the command executes
void SetElevatorSpeedDefaultCommand::Initialize() {
  Elevator::getInstance()->SetSpeedDefaultCommand();
}
