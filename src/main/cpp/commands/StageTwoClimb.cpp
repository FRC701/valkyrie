/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StageTwoClimb.h"
#include "commands/DriveClimb.h"
#include "commands/ClimberEngage.h"
#include "commands/ClimberDisengage.h"
#include "commands/MotorClimb.h"
#include "commands/Delay.h"
#include "commands/Drive.h"
#include "commands/ClimberDrive.h"
#include "commands/ClimbAndDrive.h"
#include "commands/SetArcadeDrive.h"

StageTwoClimb::StageTwoClimb() {
  constexpr double kDownSpeed = -0.6;
  constexpr int kDownEncoder = -56;

  // Don't engage the climber for level 2
  AddSequential(new ClimbAndDrive(kDownSpeed));
  AddSequential(new ClimberEngage());
  // stall the lift motor
  // so far stalling the motor is not needed
  // brake mode is strong
  //AddSequential(new DriveClimb(0.2));
  // Level 2: Let the joystick run both the chassis and the climber wheel
  // AddSequential(new Drive(0.0));
  AddParallel(new ClimberDrive());
  AddSequential(new SetArcadeDrive());
}
