/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StageOneClimb.h"
#include "commands/MotorClimb.h"
#include "commands/Delay.h"
#include "commands/ClimbAndDrive.h"

StageOneClimb::StageOneClimb() {
  constexpr double kUpSpeed = 0.5;
  constexpr int kUpEncoder = 29;

  AddSequential(new ClimbAndDrive(kUpSpeed, kUpEncoder));

}
