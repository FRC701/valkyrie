/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "commands/RunCargoRoller.h"
#include "subsystems/CargoIntake.h"

constexpr frc::DoubleSolenoid::Value kSqueeze = frc::DoubleSolenoid::kForward;
constexpr frc::DoubleSolenoid::Value kOpenSqueeze = frc::DoubleSolenoid::kReverse;

const char CargoIntake::kSubsystemName[] = "CargoIntake";

std::shared_ptr<CargoIntake> CargoIntake::self;

std::shared_ptr<CargoIntake> CargoIntake::getInstance() {
  if (! self) {
    self = std::shared_ptr<CargoIntake>(new CargoIntake);
  }
  return self;
}

CargoIntake::CargoIntake() : Subsystem("CargoIntake"),
squeezer(RobotMap::kIDCargoPneumaticForward, RobotMap::kIDCargoPneumaticReverse), 
roller(RobotMap::kIDCargoRoller)
{}


void CargoIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunCargoRoller(0));
}
void CargoIntake::Squeeze()
{
  squeezer.Set(kSqueeze);
}

void CargoIntake::OpenSqueeze()
{
  squeezer.Set(kOpenSqueeze);
}

void CargoIntake::SetCargoRoller(double speed)
{
  roller.Set(speed);
}
bool CargoIntake::IsCargoIn() {
  return roller.GetSensorCollection().IsRevLimitSwitchClosed();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
