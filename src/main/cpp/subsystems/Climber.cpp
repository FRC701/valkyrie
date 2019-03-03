/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include "commands/ClimberDefaultCommand.h"
#include "RobotMap.h"
#include "frc/DoubleSolenoid.h"

namespace
{
    static constexpr frc::DoubleSolenoid::Value kClimberEngage {frc::DoubleSolenoid::kForward};
    static constexpr frc::DoubleSolenoid::Value kClimberDisengage {frc::DoubleSolenoid::kReverse};
    static constexpr int kPCMID1 {1};
}

std::shared_ptr<Climber> Climber::self;
std::shared_ptr<Climber> Climber::getInstance() {
  if (! self) {
    self = std::shared_ptr<Climber>(new Climber);
  }
  return self;
}
Climber::Climber() : Subsystem("Climber"), 
    mDriveMotorSpeed{0},
    mLiftMotorSpeed{0},
    // mDriveMotor(RobotMap::kIDClimberDriveMotor),
    // mLiftMotor{RobotMap::kIDClimberLiftMotor, rev::CANSparkMax::MotorType::kBrushless},
    mLiftSolenoid(kPCMID1, RobotMap::kIDClimberForward, RobotMap::kIDClimberReverse)
{
    mLiftSolenoid.Set(kClimberDisengage);
    // mDriveMotor.Set(0.0);
    // mLiftMotor.Set(0.0);
    // mDriveMotor.SetInverted(true);
    // mLiftMotor.SetInverted(true);
}

void Climber::InitDefaultCommand() {
      SetDefaultCommand(new ClimberDefaultCommand());
}

void Climber::Engage() {
    mLiftSolenoid.Set(kClimberEngage);
}

void Climber::Disengage() {
    mLiftSolenoid.Set(kClimberDisengage);
}

void Climber::MotorClimber(double speed) {
    mDriveMotorSpeed = speed;
    Update();
}

void Climber::DriveClimb(double speed) {
    mLiftMotorSpeed = speed;
    Update();
}

void Climber::Update() {
    //mDriveMotor.Set(mDriveMotorSpeed);
    //mLiftMotor.Set(mLiftMotorSpeed);
}