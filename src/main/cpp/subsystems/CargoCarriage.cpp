/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "RobotMap.h"
#include "subsystems/CargoCarriage.h"
namespace
{
  constexpr frc::DoubleSolenoid::Value kEngage {frc::DoubleSolenoid::kForward};
  constexpr frc::DoubleSolenoid::Value kDisengage {frc::DoubleSolenoid::kReverse};
}

const char CargoCarriage::kSubsystemName[] = "CargoCarriage";

std::shared_ptr<CargoCarriage> CargoCarriage::self;

std::shared_ptr<CargoCarriage> CargoCarriage::getInstance() {
  if (! self) {
    self = std::shared_ptr<CargoCarriage>(new CargoCarriage);
  }
  return self;
}
CargoCarriage::CargoCarriage() : Subsystem("CargoCarriage"),
mPuncher(RobotMap::kIDCargoPuncherForward, RobotMap::kIDCargoPuncherReverse),
mLeftHook(RobotMap::kIDCargoRightForward, RobotMap::kIDCargoRightReverse),
mRightHook(RobotMap::kIDCargoRightForward, RobotMap::kIDCargoRightReverse)
 {

 }

void CargoCarriage::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void CargoCarriage::Engage()
{
  mLeftHook.Set(kEngage);
  mRightHook.Set(kEngage);
}

void CargoCarriage::Disengage()
{
  mLeftHook.Set(kDisengage);
  mRightHook.Set(kDisengage);
}

void CargoCarriage::Punch()
{
  mPuncher.Set(kEngage);
}

void CargoCarriage::PullBack()
{
  mPuncher.Set(kDisengage);
}
