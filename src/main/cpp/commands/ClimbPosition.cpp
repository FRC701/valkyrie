/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbPosition.h"
#include "subsystems/Climber.h"

ClimbPosition::ClimbPosition(double position)
:  mPosition(position) 
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Climber::getInstance().get());
}

// Called once when the command executes
void ClimbPosition::Initialize() {
  Climber::getInstance()->ClimbPosition(mPosition);

}
