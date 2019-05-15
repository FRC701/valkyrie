/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StageThreeClimb.h"
#include "commands/ClimberEngage.h"
#include "commands/ClimberDisengage.h"
#include "commands/DriveClimb.h"
#include "commands/MotorClimb.h"
#include "subsystems/Chassis.h"

StageThreeClimb::StageThreeClimb() {
  // Murphy is an idiot make this a commamd
  // Chassis::getInstance()->GetCurrentCommand()->Cancel();
  //AddSequential(new ClimberDisengage());
  AddSequential(new DriveClimb(0.));
}
