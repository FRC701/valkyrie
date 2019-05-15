/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StageFourClimb.h"
#include "commands/ClimberDisengage.h"
#include "commands/ClimberEngage.h"
#include "commands/DriveClimb.h"
#include "commands/MotorClimb.h"
#include "subsystems/Chassis.h"

StageFourClimb::StageFourClimb() {
  AddSequential(new DriveClimb(0));
  AddSequential(new MotorClimb(0, 0));
}
