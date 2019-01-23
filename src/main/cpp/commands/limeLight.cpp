/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/limeLight.h"
#include "Networktables/NetworkTable.h"
#include "frc/smartdashboard/Smartdashboard.h"

std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
double targetArea = table->GetNumber("ta",0.0);
double targetSkew = table->GetNumber("ts",0.0);

limeLight::limeLight() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void limeLight::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void limeLight::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool limeLight::IsFinished() { return false; }

// Called once after isFinished returns true
void limeLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void limeLight::Interrupted() {}
