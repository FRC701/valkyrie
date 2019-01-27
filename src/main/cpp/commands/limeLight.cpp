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

  if (targetOffsetAngle_Horizontal < -4) {
    rotation = true;
    Chassis::getInstance()->LimeLightDrive(0.025,-0.025);
  }
  if (targetOffsetAngle_Horizontal > -2) {
    rotation = true;
    Chassis::getInstance()->LimeLightDrive(-0.025,0.025);
  }

  if (targetOffsetAngle_Horizontal < -2 && targetOffsetAngle_Horizontal > -4) {
    rotation = false;
    Chassis::getInstance()->LimeLightDrive(0,0);
  }

  if (targetArea < 3) {
    driveF = true;
    driveB = false;
  }
  
  if (targetArea > 3.5) {
    driveF = false;
    driveB = true;
  }

  if (targetArea < 3.5 && targetArea > 3) {
    driveF = false;
    driveB = false;
  }

  if (rotation == true) {
    
  }
  if (rotation == false) {
    if (driveF == true) {
      Chassis::getInstance()->LimeLightDrive(0.05,0.05);   
    }
    if (driveB == true) {
      Chassis::getInstance()->LimeLightDrive(-0.05,-0.05);
    }
    if (driveF == false && driveB == false) {
      Chassis::getInstance()->LimeLightDrive(0,0);
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool limeLight::IsFinished() { return false; }

// Called once after isFinished returns true
void limeLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void limeLight::Interrupted() {}