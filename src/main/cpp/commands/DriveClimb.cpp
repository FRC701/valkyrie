/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveClimb.h"
#include "subsystems/Climber.h"

DriveClimb::DriveClimb(double speed) : mDriveMotorSpeed(speed)  {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Climber::getInstance().get());
}

// Called just before this Command runs the first time
void DriveClimb::Initialize() {
  Climber::getInstance()->DriveClimb(mDriveMotorSpeed);
}
