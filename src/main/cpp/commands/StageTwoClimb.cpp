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

StageTwoClimb::StageTwoClimb() {
  constexpr double kDownSpeed = 0.2;
  constexpr int kDownEncoder = 59;

  AddSequential(new ClimberEngage());
  AddSequential(new MotorClimb(kDownSpeed, kDownEncoder));
  // stall the lift motor
  // so far stalling the motor is not needed
  // brake mode is strong
  //AddSequential(new DriveClimb(0.2));
  AddSequential(new Drive(0.0));
  AddSequential(new ClimberDrive());
}
