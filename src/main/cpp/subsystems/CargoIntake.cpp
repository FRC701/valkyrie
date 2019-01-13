/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoIntake.h"
static frc::DoubleSolenoid::Value kDeployerOut = frc::DoubleSolenoid::kForward;
static frc::DoubleSolenoid::Value kDeployerIn = frc::DoubleSolenoid::kReverse;


const char CargoIntake::kSubsystemName[] = "CargoIntake";

std::shared_ptr<CargoIntake> CargoIntake::self;

std::shared_ptr<CargoIntake> CargoIntake::getInstance() {
  if (! self) {
    self = std::shared_ptr<CargoIntake>(new CargoIntake);
  }
  return self;
}

CargoIntake::CargoIntake() : Subsystem("CargoIntake"),
deployer(RobotMap::kIDCargoPneumaticForward, RobotMap::kIDCargoPneumaticReverse), 
roller(RobotMap::kIDCargoRoller)
{}


void CargoIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void CargoIntake::DeployIn()
{
  deployer.Set(kDeployerIn);
}

void CargoIntake::DeployOut()
{
  deployer.Set(kDeployerOut);
}

void CargoIntake::SetCargoRoller(double speed)
{
  roller.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
