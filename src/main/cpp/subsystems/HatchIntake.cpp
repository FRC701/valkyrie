/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchIntake.h"
namespace
{
  constexpr frc::DoubleSolenoid::Value kMotorEngage {frc::DoubleSolenoid::kForward};
  constexpr frc::DoubleSolenoid::Value kMotorDisengage {frc::DoubleSolenoid::kReverse};
}

const char HatchIntake::kSubsystemName[] = "HatchIntake";

std::shared_ptr<HatchIntake> HatchIntake::self;

std::shared_ptr<HatchIntake> HatchIntake::getInstance() {
  if (! self) {
    self = std::shared_ptr<HatchIntake>(new HatchIntake);
  }
  return self;
}

HatchIntake::HatchIntake() : Subsystem("HatchIntake"),
mPuncher(RobotMap::kIDHatchPuncherForward, RobotMap::kIDHatchPuncherReverse), 
mPivot(RobotMap::kIDHatchPivot)
{}

void HatchIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void HatchIntake::Disengage() {
  mPuncher.Set(kMotorEngage);
}

void HatchIntake::Engage() {
  mPuncher.Set(kMotorDisengage);
}

void HatchIntake::Pivot(double speed) 
{
  
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
