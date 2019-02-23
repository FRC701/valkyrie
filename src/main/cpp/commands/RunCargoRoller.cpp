/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunCargoRoller.h"
#include "subsystems/CargoIntake.h"
#include "OI.h"

RunCargoRoller::RunCargoRoller(double speed): mSpeed(speed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(CargoIntake::getInstance().get());
}

// Called just before this Command runs the first time
void RunCargoRoller::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunCargoRoller::Execute() 
{
  CargoIntake::getInstance()->SetCargoRoller(mSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool RunCargoRoller::IsFinished() {
  if(mSpeed < 0){
    return ! CargoIntake::getInstance()->IsCargoIn();
  }
  else{
    return CargoIntake::getInstance()->IsCargoIn();
  }


}

// Called once after isFinished returns true
void RunCargoRoller::End() {
  //OI::getInstance()->CargoIntakeControls();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunCargoRoller::Interrupted() {}
