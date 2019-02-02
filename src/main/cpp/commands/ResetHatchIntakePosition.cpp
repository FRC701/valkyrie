/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetHatchIntakePosition.h"

ResetHatchIntakePosition::ResetHatchIntakePosition() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
    Requires(HatchIntake::getInstance().get());
}

// Called once when the command executes
void ResetHatchIntakePosition::Initialize() {
     HatchIntake::getInstance()->ResetHatchIntakePosition();
}
