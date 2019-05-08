/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MotorClimb.h"

#include "subsystems/Climber.h"

MotorClimb::MotorClimb(double speed, double encoderFinish)
: mSpeed(speed)
, mEncoderFinish(encoderFinish)
, mClimber(Climber::getInstance())
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(mClimber.get());
}

// Called just before this Command runs the first time
void MotorClimb::Initialize() {
  mClimber->MotorClimber(mSpeed);
}

// Called repeatedly when this Command is scheduled to run
void MotorClimb::Execute() {
  mClimber->Update();
}

// Make this return true when this Command no longer needs to run execute()
bool MotorClimb::IsFinished() {
  if (mSpeed == 0) return true;

  if (mSpeed > 0) 
  {
    return mClimber->GetLiftMotorEncoderValue() >= mEncoderFinish; 
  }
  else
  {
    return mClimber->GetLiftMotorEncoderValue() <= mEncoderFinish; 
  }
}

// Called once after isFinished returns true
void MotorClimb::End() {
  mClimber->MotorClimber(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MotorClimb::Interrupted() {
  mClimber->MotorClimber(0);
}
