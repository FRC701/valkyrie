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
bool rotationL = false;
bool rotationR = false;

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
  double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetSkew = table->GetNumber("ts",0.0);

  if (targetOffsetAngle_Horizontal < 0) {
    //rotationL = true;
    //rotationR = false;
    Chassis::getInstance()->LimeLightDrive(-1,1);
  }
  else if (targetOffsetAngle_Horizontal > 0) {
    //rotationL = false;
    //rotationR = true;
    Chassis::getInstance()->LimeLightDrive(1,-1);
  }

  else {
    //rotationL = false;
    //rotationR = false;
    Chassis::getInstance()->LimeLightDrive(0,0);
  }
/*
  if (targetArea < 15) {
    driveF = true;
    driveB = false;
  }
  
  else if (targetArea > 25) {
    driveF = false;
    driveB = true;
  }

  else {
    driveF = false;
    driveB = true;
  }

  if (driveF == true && rotationL == true) {
    Chassis::getInstance()->LimeLightDrive(0.5,1);
  }
  else if (driveF == true && rotationL == false && rotationR == true) {
    Chassis::getInstance()->limeLightDrive(1,0.5);
  }
  else if (driveF == false && driveB == true && rotationL == true) {
    Chassis::getInstance()->limeLightDrive(-1,-0.5);
  }
  else if (driveF)
  */
}

// Make this return true when this Command no longer needs to run execute()
bool limeLight::IsFinished() { return false; }

// Called once after isFinished returns true
void limeLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void limeLight::Interrupted() {}
