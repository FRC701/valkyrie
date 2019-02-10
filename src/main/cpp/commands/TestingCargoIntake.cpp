/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TestingCargoIntake.h"

TestingCargoIntake::TestingCargoIntake(double speed) : RunCargoRoller(speed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Make this return true when this Command no longer needs to run execute()
bool TestingCargoIntake::IsFinished() { return false; }

