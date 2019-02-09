/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <frc/WPILib.h>
#include "commands/Drive.h"
#include "commands/HatchIntakeDisengage.h"
#include "commands/HatchIntakeEngage.h"
#include "commands/HatchPuncherEngage.h"
#include "commands/HatchPuncherDisengage.h"
#include "commands/CarriageClawEngage.h"
#include "commands/CarriageClawDisengage.h"
#include "commands/CarriagePuncherDisengage.h"
#include "commands/CarriagePuncherEngage.h"
#include "commands/MotorClimb.h"



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
  frc::SmartDashboard::PutData("Puncher Engage", new HatchPuncherEngage());
  frc::SmartDashboard::PutData("Puncher Disengage", new HatchPuncherDisengage());
  frc::SmartDashboard::PutData("Hatch Intake Engage", new HatchIntakeEngage());
  frc::SmartDashboard::PutData("Hatch Intake Disengage", new HatchIntakeDisengage());
  frc::SmartDashboard::PutData("Pivot", new PivotHatch());
  frc::SmartDashboard::PutData("Carriage Claw Engage", new CarriageClawEngage());
  frc::SmartDashboard::PutData("Carriage Claw Disengage", new CarriageClawDisengage());
  frc::SmartDashboard::PutData("Carriage Puncher Engage", new CarriagePuncherEngage());
  frc::SmartDashboard::PutData("Carriage Puncher Disengage", new CarriagePuncherDisengage());
  frc::SmartDashboard::PutData("Climb Motor", new MotorClimb());
  frc::SmartDashboard::PutData("Run Cargo Roller", new RunCargoRoller());
  frc::SmartDashboard::PutData("Cargo Deployer In", new SetCargoDeployerIn());
  frc::SmartDashboard::PutData("Cargo Deployer out", new SetCargoDeployerOut());
  frc::SmartDashboard::PutData("Set Elevator", new SetElevator(0.3));
  frc::SmartDashboard::PutData("Set Elevator", new SetElevator(-0.3));
  frc::SmartDashboard::PutBoolean("Elevator Bottom Limit Switch", Elevator::getInstance()->IsRevLimitSwitchClosed());
  frc::SmartDashboard::PutBoolean("Cargo Intake Banner Sensor", CargoIntake::getInstance()->IsRevLimitSwitchClosed());
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