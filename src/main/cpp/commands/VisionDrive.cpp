/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionDrive.h"
#include "subsystems/Chassis.h"
#include "OI.h"

VisionDrive::VisionDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Chassis::getInstance().get());
}

// Called just before this Command runs the first time
void VisionDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {

  std::shared_ptr<OI> oi = OI::getInstance();
  std::shared_ptr<Chassis> chassis = Chassis::getInstance();

  Chassis::getInstance()->SetArcadeDrive(oi->getDriverLeftYAxis(), chassis->GetVisionRotation());
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void VisionDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {}
