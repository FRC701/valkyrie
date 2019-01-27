/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include "commands/SetClimber.h"
#include "RobotMap.h"
#include "frc/DoubleSolenoid.h"

namespace
{
constexpr frc::DoubleSolenoid::Value kClimberEngage {frc::DoubleSolenoid::kForward};
constexpr frc::DoubleSolenoid::Value kClimberDisengage {frc::DoubleSolenoid::kReverse};
}

std::shared_ptr<Climber> Climber::self;
std::shared_ptr<Climber> Climber::getInstance() {
  if (! self) {
    self = std::shared_ptr<Climber>(new Climber);
  }
  return self;
}
Climber::Climber() : Subsystem("Climber"),
    mDriveMotor(RobotMap::kIDClimberDriveMotor),
    mLiftMotor(RobotMap::kIDClimberLiftMotor),
    mLiftSolenoid(1, RobotMap::kIDClimberForward, RobotMap::kIDClimberReverse)
{
    mLiftSolenoid.Set(kClimberDisengage);
}

void Climber::InitDefaultCommand() {
}

void Climber::Engage() {
    mLiftSolenoid.Set(kClimberEngage);
}

void Climber::Disengage() {
    mLiftSolenoid.Set(kClimberDisengage);
}

void Climber::MotorClimber(double speed) {
    mLiftMotor.Set(speed);
}

void Climber::DriveClimb(double speed) {
    mDriveMotor.Set(speed);
}
