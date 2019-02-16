/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include "frc/DoubleSolenoid.h"
#include "ctre/Phoenix.h"
#include <frc/AnalogInput.h>

class HatchIntake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  static const char kSubsystemName[];
  static std::shared_ptr<HatchIntake> self;
  
  frc::DoubleSolenoid mPuncher;
  WPI_TalonSRX mPivot;
  frc::AnalogInput armPot;

  int potFwd;
  int potRev;
  int encoderFwd;
  int encoderRev;

  void SetupMotionMagic();
  void SetUpTalons();

  double mMotorSpeed;
  double mMotorPosition;
 public:

  HatchIntake();
  static std::shared_ptr<HatchIntake> getInstance();
  void InitDefaultCommand() override;
  void Engage();
  void Disengage();
  void Pivot(double speed);
  void PivotPosition(double position);
  int GetVelocity();
  int GetPosition();
  int GetPositionError();
  void ResetArmEncoder();
  int GetArmPotValue();
  void GetArmValuesFwd();
  void GetArmValuesRev();
  int GetEncoderValue();
  void SetArmValue();
  void SetSoftLimits();
  void UpdateSpeed();
  void UpdatePosition();
  void SetAngleValue();
  double GetEncoderFromAngle(double angle);
  

};
