/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/Smartdashboard.h>

#include "commands/limeLight.h"
#include "subsystems/Chassis.h"

bool driveF = false;
bool driveB = false;
bool rotation = false;
double tx = 0.0;
double ta = 0.0;

limeLight::limeLight() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Chassis::getInstance().get());
}

// Called just before this Command runs the first time
void limeLight::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void limeLight::Execute() {

  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double targetOffsetAngle_HorizontalL = table->GetNumber("tx0",0.0);
  double targetOffsetAngle_HorizontalS = table->GetNumber("tx1",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetAreaL = table->GetNumber("ta0",0.0);
  double targetAreaS = table->GetNumber("ta1",0.0);
  double angleCoefficiant = 0;
  if (targetOffsetAngle_HorizontalS > targetOffsetAngle_HorizontalL) {
    angleCoefficiant = 1;
  }
  if (targetOffsetAngle_HorizontalS < targetOffsetAngle_HorizontalL) {
    angleCoefficiant = -1;
  }
  double targetAngle = (targetAreaL - targetAreaS) * angleCoefficiant
  double turnAngle = 90 - targetAngle;

  if (targetAngle != 0 && targetAngle < 45 && targetAngle > -45) {
    
  }

   

}

// Make this return true when this Command no longer needs to run execute()
bool limeLight::IsFinished() { return false; }

// Called once after isFinished returns true
void limeLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void limeLight::Interrupted() {}