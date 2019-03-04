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

Climb::Climb() {
  AddSequential(new MotorClimb(0.));
  AddSequential(new DriveClimb(0.));
  AddSequential(new MotorClimb(0.));
}
