/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoRollerOuttake.h"

#include "subsystems/CargoIntake.h"

#include "OI.h"

CargoRollerOuttake::CargoRollerOuttake(double timeout)
    : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(CargoIntake::getInstance().get());
}

// Called just before this Command runs the first time
void CargoRollerOuttake::Initialize() {
  CargoIntake::getInstance()->Squeeze();
}

// Called repeatedly when this Command is scheduled to run
void CargoRollerOuttake::Execute() {
  CargoIntake::getInstance()->SetCargoRoller(-1.0);
}

// Called once after command times out
void CargoRollerOuttake::End() {
  OI::getInstance()->HatchIntakeControls();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoRollerOuttake::Interrupted() {
  OI::getInstance()->HatchIntakeControls();
}
