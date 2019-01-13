/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "commands/TankDrive.h"
#include <frc/WPILib.h>

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