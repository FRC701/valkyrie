/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <frc/WPILib.h>
#include "commands/Drive.h"
#include "commands/SetClimber.h"
#include "commands/MotorClimb.h"
#include "commands/SaveHatchIntakeValueFWD.h"
#include "commands/SaveHatchIntakeValueREV.h"
#include "commands/ResetHatchIntakePosition.h"
#include "subsystems/HatchIntake.h"
#include "commands/SetHatchIntakeAngleValue.h"
#include "commands/SettingEncoderValues.h"


std::shared_ptr<OI> OI::self;

std::shared_ptr<OI> OI::getInstance() {
  if (! self) {
    self = std::make_shared<OI>();
  }
  return self;
}

OI::OI() {

  coDriver.reset(new frc::Joystick(1));

  driver.reset(new frc::Joystick(0));
  // Process operator interface input here.
  frc::SmartDashboard::PutData("Drive 25", new Drive(.25));
  frc::SmartDashboard::PutData("Drive 50", new Drive(.50));
  frc::SmartDashboard::PutData("Drive 75", new Drive(.75));
  frc::SmartDashboard::PutData("Drive 100", new Drive(1));
  frc::SmartDashboard::PutData("Drive -25", new Drive(-.25));
  frc::SmartDashboard::PutData("Drive -50", new Drive(-.50));
  frc::SmartDashboard::PutData("Drive -75", new Drive(-.75));
  frc::SmartDashboard::PutData("Drive -100", new Drive(-1));
  frc::SmartDashboard::PutData("Run Climber Motor 50%", new SetClimber(0.5));
  frc::SmartDashboard::PutData("Run Climber Motor -50%", new SetClimber(-0.5));
  frc::SmartDashboard::PutData("Run Climber Drive", new MotorClimb(.8));
  frc::SmartDashboard::PutData("Run Climber 0%", new SetClimber(0.));
  frc::SmartDashboard::PutData("Stop Climber Drive", new MotorClimb(0.));
  //Hatch arm  clibration:
  frc::SmartDashboard::PutData("Reset hatch Encoder", new ResetHatchIntakePosition());
  frc::SmartDashboard::PutData("Save hatch Forward Point", new SaveHatchIntakeValueREV());
  frc::SmartDashboard::PutData("Save hatch Reverse Point", new SaveHatchIntakeValueFWD());
  frc::SmartDashboard::PutData("Set Hatch Encoder values", new SettingEncoderValues());
  frc::SmartDashboard::PutData("Set Hatch Intake Angle", new SetHatchIntakeAngleValue());
}

std::shared_ptr<frc::Joystick> OI::getdriver() {
  return driver;
}

std::shared_ptr<frc::Joystick> OI::getcoDriver() {
  return coDriver;
}

double OI::getDriverLeftXAxis() const{
  return driver->GetRawAxis(kLeftXAxis_ID);
}

double OI::getDriverLeftYAxis() const{
  return driver->GetRawAxis(kLeftYAxis_ID);
}

double OI::getDriverRightXAxis() const{
  return driver->GetRawAxis(kRightXAxis_ID);
}

double OI::getDriverRightYAxis() const{
  return driver->GetRawAxis(kRightYAxis_ID);
}