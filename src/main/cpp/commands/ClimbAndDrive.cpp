/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbAndDrive.h"
#include "subsystems/Chassis.h"
#include "subsystems/Climber.h"


ClimbAndDrive::ClimbAndDrive(double speed) : Super(speed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called repeatedly when this Command is scheduled to run
void ClimbAndDrive::Execute() {
  Super::Execute();
  Climber::getInstance()->DriveClimb(0.15);
}

