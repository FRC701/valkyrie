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
#include "commands/SetElevatorSpeed.h"
#include "commands/HatchIntakeDisengage.h"
#include "commands/HatchIntakeEngage.h"
#include "commands/HatchPuncherEngage.h"
#include "commands/HatchPuncherDisengage.h"
#include "commands/CarriageClawEngage.h"
#include "commands/CarriageClawDisengage.h"
#include "commands/CarriagePuncherDisengage.h"
#include "commands/CarriagePuncherEngage.h"
#include "commands/PivotHatch.h"
#include "commands/RunCargoRoller.h"
#include "commands/TestingCargoIntake.h"
#include "commands/SetCargoDeployerIn.h"
#include "commands/SetCargoDeployerOut.h"
#include "commands/SetHatchIntakeAngleValue.h"
#include "commands/SetElevator.h"
#include "commands/ResetElevatorPosition.h"
#include "commands/PivotPosition.h"
#include "commands/HatchIntakeToggle.h"
#include "commands/SetElevatorPositionInches.h"
#include "commands/SetElevatorPosDefaultCommand.h"
#include "commands/SetElevatorSpeedDefaultCommand.h"
#include "commands/ScoreCargo.h"
#include "commands/FullCargoLevel.h"
#include "commands/FullHatchLevel.h"
#include "commands/FullArmPosition.h"

std::shared_ptr<OI> OI::self;

std::shared_ptr<OI> OI::getInstance() {
  if (! self) {
    self = std::make_shared<OI>();
  }
  return self;
}

OI::OI() 
: driver(new frc::Joystick(0))

, dA(driver.get(), kButtonA_ID)
, dB(driver.get(), kButtonB_ID)
, dX(driver.get(), kButtonX_ID)
, dY(driver.get(), kButtonY_ID)
, dLB(driver.get(), kButtonLB_ID)
, dRB(driver.get(), kButtonRB_ID)
, dL3(driver.get(), kButtonL3_ID)
, dR3(driver.get(), kButtonR3_ID)
, dStart(driver.get(), kButtonStart_ID)
, dBack(driver.get(), kButtonBack_ID)

, coDriver(new frc::Joystick(1))

, coA(coDriver.get(), kButtonA_ID)
, coB(coDriver.get(), kButtonB_ID)
, coX(coDriver.get(), kButtonX_ID)
, coY(coDriver.get(), kButtonY_ID)
, coLB(coDriver.get(), kButtonLB_ID)
, coRB(coDriver.get(), kButtonRB_ID)
, coL3(coDriver.get(), kButtonL3_ID)
, coR3(coDriver.get(), kButtonR3_ID)
, coStart(coDriver.get(), kButtonStart_ID)
, coBack(coDriver.get(), kButtonBack_ID)
, coPOV0(*coDriver.get(), 0)
, coPOV90(*coDriver.get(), 90)
, coPOV180(*coDriver.get(), 180)
, coPOV270(*coDriver.get(), 270)
{
  
  coLB.WhenPressed(new HatchIntakeToggle());
  coStart.WhenPressed(new FullCargoLevel(29000));
  coL3.WhenPressed(new SetElevator(29000));
  coR3.WhenPressed(new SetElevator(0));
  coX.WhenPressed(new RunCargoRoller(0.3));
  coPOV0.WhenPressed(new FullArmPosition(0));
  coPOV90.WhenPressed(new FullArmPosition(6000));
  //coPOV180.WhenPressed();
  coPOV270.WhenPressed(new FullArmPosition(-7000));

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
  frc::SmartDashboard::PutData("1. Reset Encoder", new ResetHatchIntakePosition());
  frc::SmartDashboard::PutData("2. Hatch Forward Point", new SaveHatchIntakeValueFWD());
  frc::SmartDashboard::PutData("3. Hatch Reverse Point", new SaveHatchIntakeValueREV());
  frc::SmartDashboard::PutData("3. Set Hatch Intake Angle", new SetHatchIntakeAngleValue());
   frc::SmartDashboard::PutData("Puncher Engage", new HatchPuncherEngage());
  frc::SmartDashboard::PutData("Puncher Disengage", new HatchPuncherDisengage());
  frc::SmartDashboard::PutData("Hatch Intake Engage", new HatchIntakeEngage());
  frc::SmartDashboard::PutData("Hatch Intake Disengage", new HatchIntakeDisengage());
  frc::SmartDashboard::PutData("Pivot fwd", new PivotHatch(0.3));
  frc::SmartDashboard::PutData("Pivot rev", new PivotHatch(-0.3));
  frc::SmartDashboard::PutData("Carriage Claw Engage", new CarriageClawEngage());
  frc::SmartDashboard::PutData("Carriage Claw Disengage", new CarriageClawDisengage());
  frc::SmartDashboard::PutData("Carriage Puncher Engage", new CarriagePuncherEngage());
  frc::SmartDashboard::PutData("Carriage Puncher Disengage", new CarriagePuncherDisengage());
  frc::SmartDashboard::PutData("Run Cargo Roller 30%", new RunCargoRoller(0.3));
  frc::SmartDashboard::PutData("Run Cargo Roller -30%", new RunCargoRoller(-0.3));
  frc::SmartDashboard::PutData("Running Test Cargo Roller 30%", new TestingCargoIntake(0.3));
  frc::SmartDashboard::PutData("Running Test Cargo Roller -30%", new TestingCargoIntake(-0.3));
  frc::SmartDashboard::PutData("Cargo Deployer In", new SetCargoDeployerIn());
  frc::SmartDashboard::PutData("Cargo Deployer out", new SetCargoDeployerOut());
  frc::SmartDashboard::PutData("Elevator Run forward", new SetElevatorSpeed(0.3));
  frc::SmartDashboard::PutData("Elevator Run reverse", new SetElevatorSpeed(-0.3));
  frc::SmartDashboard::PutData("Elevator Pos 25%", new SetElevator(0.005));
  frc::SmartDashboard::PutData("Elevator Pos 50%", new SetElevator(-0.005));
  frc::SmartDashboard::PutData("Reset Elevator Encoder", new ResetElevatorPosition());
  frc::SmartDashboard::PutData("Level 1", new SetElevator(500));
  frc::SmartDashboard::PutData("Level 2", new SetElevator(27000));
  frc::SmartDashboard::PutData("Level 3", new SetElevator(50000));
  frc::SmartDashboard::PutData("Elevator Inches Lvl 1", new SetElevatorPositionInches(19));
  frc::SmartDashboard::PutData("Elevator Inches Lvl 2", new SetElevatorPositionInches(47));
  frc::SmartDashboard::PutData("Elevator Inches Lvl 3", new SetElevatorPositionInches(75));
  frc::SmartDashboard::PutData("Elevator: Position Default", new SetElevatorPosDefaultCommand());
  frc::SmartDashboard::PutData("Elevator: Speed Default", new SetElevatorSpeedDefaultCommand());
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

void OI::HatchIntakeControls(){
  coY.WhenPressed(new FullHatchLevel(0));
  coB.WhenPressed(new FullHatchLevel(29000));
  coA.WhenPressed(new FullHatchLevel(50000));
  coRB.WhenPressed(new HatchIntakeEngage());
}

void OI::CargoIntakeControls(){
  coY.WhenPressed(new FullCargoLevel(5000));
  coB.WhenPressed(new FullCargoLevel(35000));
  coA.WhenPressed(new FullCargoLevel(55000));
  coRB.WhenPressed(new ScoreCargo());
}
