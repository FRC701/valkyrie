/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FullArmMoveTwo.h"
#include "commands/FullArmPosition.h"
#include "commands/FullElevatorLevel.h"

FullArmMoveTwo::FullArmMoveTwo() {
  AddSequential(new FullElevatorLevel(8000));
  AddSequential(new FullArmPosition(130));
  AddSequential(new FullElevatorLevel(0));
}
