/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StageTwoClimb.h"
#include "commands/ClimbAndDrive.h"
#include "commands/ClimberDisengage.h"
#include "commands/ClimberDrive.h"
#include "commands/ClimberEngage.h"
#include "commands/ClimberSetSpeed.h"
#include "commands/Delay.h"
#include "commands/Drive.h"
#include "commands/DriveClimb.h"
#include "commands/MotorClimb.h"
#include "commands/SetArcadeDrive.h"

StageTwoClimb::StageTwoClimb() {
  constexpr double kDownSpeed = -0.6;
  // Don't engage the climber for level 2
  AddSequential(new ClimberEngage());
  AddSequential(new ClimbAndDrive(kDownSpeed));
  // stall the lift motor
  // so far stalling the motor is not needed
  // brake mode is strong
  //AddSequential(new ClimberSetSpeed());
  // Level 2: Let the joystick run both the chassis and the climber wheel
  // AddSequential(new Drive(0.0));
  AddParallel(new SetArcadeDrive());
  AddSequential(new ClimberDrive());
}
