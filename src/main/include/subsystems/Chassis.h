#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/CANSparkMax.h"
#include "rev/CANEncoder.h"
#include <frc/Drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>

class Chassis: public frc::Subsystem {
private:

  static const char kSubsystemName[];
  static std::shared_ptr<Chassis> self;

  rev::CANSparkMax right1Wheel;
  rev::CANSparkMax right2Wheel;
  rev::CANSparkMax left1Wheel;
  rev::CANSparkMax left2Wheel;
  rev::CANEncoder leftEncoder;
  rev::CANEncoder rightEncoder;

  
  frc::SpeedControllerGroup m_left;
  frc::SpeedControllerGroup m_right;
  frc::DifferentialDrive m_drive;

  std::shared_ptr<NetworkTable> mLimeLightTable;


  bool mIsHighGear;

 public:
  

  static std::shared_ptr<Chassis> getInstance();

  Chassis();

  void InitDefaultCommand();

  void SetTankDrive(double left, double right);
  void SetCoast();
  void SetBrake();
  void SetupDrive();
  void SetUpSpark(); 
  void DriveChassis(double speed);
  double GetRightPosition();
  double GetLeftPosition();
  double GetLeftCurrent();
  double GetRightCurrent();
  double GetLeftVoltage();
  double GetRightVoltage();
  void SetArcadeDrive(double speed, double rotation);
  double GetVisionRotation();
  
  void SetHighGear() { mIsHighGear = true; }
  void SetLowGear() { mIsHighGear = false; }
  bool IsHighGear() { return mIsHighGear; }

};
