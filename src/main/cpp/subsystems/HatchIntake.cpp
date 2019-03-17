/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchIntake.h"
#include "commands/HatchIntakeDefaultCommand.h"
#include "commands/HatchIntakeSpeedDefaultCommand.h"
#include "utilities/LineCalculator.h"
#include "commands/PivotHatch.h"

using RobotMap::kPID_PrimaryClosedLoop;
using RobotMap::kTimeout_10Millis;
using frc::Preferences;

namespace
{
  constexpr frc::DoubleSolenoid::Value kMotorEngage {frc::DoubleSolenoid::kForward};
  constexpr frc::DoubleSolenoid::Value kMotorDisengage {frc::DoubleSolenoid::kReverse};
  constexpr int kSlotIndex {0};

  constexpr double calcFeedforward() 
  {
   constexpr double kMaxUnitsPer100ms {3675.0};
    // static const double kUnitsPerRev = 4096.0;
    // double rpm = (kMaxUnitsPer100ms * 600.0) / kUnitsPerRev;
    double feedforward = 1023.0 / kMaxUnitsPer100ms;
    return feedforward;
  }

  constexpr double calcP() 
  {
    // TODO: What is the knob? What do we change to make this different.
    constexpr double kEigthUnitsPerRev {4096.0 / 1.0};
    constexpr double kGainRatio {2.0};
    constexpr double pGain = kGainRatio * 1023.0 / kEigthUnitsPerRev;
    return pGain;
  }
}

const char HatchIntake::kSubsystemName[] { "HatchIntake" };
std::shared_ptr<HatchIntake> HatchIntake::self;

std::shared_ptr<HatchIntake> HatchIntake::getInstance() {
  if (! self) {
    self = std::shared_ptr<HatchIntake>(new HatchIntake);
  }
  return self;
}

HatchIntake::HatchIntake() : Subsystem("HatchIntake"),
mPuncher(RobotMap::kIDHatchPuncherForward, RobotMap::kIDHatchPuncherReverse), 
mPivot(RobotMap::kIDHatchPivot),
armPot(RobotMap::kIDArmPot),
mMotorSpeed{0},
mMotorPosition{0},
mArmSlope{*frc::Preferences::GetInstance(), "ArmSlope"},
mArmYIntercept{*frc::Preferences::GetInstance(), "ArmYIntercept"},
mHatchFwdSoftLimit{*frc::Preferences::GetInstance(), "HatchFwdSoftLimit"},
mHatchRevSoftLimit{*frc::Preferences::GetInstance(), "HatchRevSoftLimit"},
mAngleSlope{*frc::Preferences::GetInstance(), "AngleSlope"},
mAngleYIntercept{*frc::Preferences::GetInstance(), "AngleYIntercept"},
mSensorPhase{*frc::Preferences::GetInstance(), "HatchIntakeSensorPhase"}
{
  SetUpTalons();
  SetupMotionMagic();

  SetArmValue();
}

void HatchIntake::InitDefaultCommand() {
   SetDefaultCommand(new HatchIntakeDefaultCommand);
}

void HatchIntake::Disengage() {
  mPuncher.Set(kMotorDisengage);
}

void HatchIntake::Engage() {
  mPuncher.Set(kMotorEngage);
}

void HatchIntake::Pivot(double speed) {
  mMotorSpeed = speed;
  UpdateSpeed();
}

void HatchIntake::PivotPosition(double position) {
  mMotorPosition = position;
  UpdatePosition();
}

void HatchIntake::PivotPositionByAngle(double angle)
{
  PivotPosition(GetEncoderFromAngle(angle));
}

void HatchIntake::SetUpTalons() {
  mPivot.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
                                       kPID_PrimaryClosedLoop,
                                       kTimeout_10Millis);
  mPivot.ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.SetSensorPhase(mSensorPhase); 
  mPivot.SetInverted(true);
  mPivot.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
  mPivot.ConfigPeakOutputReverse(-0.1, kTimeout_10Millis);

  SetSoftLimits();
}

int HatchIntake::GetVelocity()
{
 return mPivot.GetSelectedSensorVelocity(RobotMap::kPID_PrimaryClosedLoop);
}

int HatchIntake::GetPosition()
{
  return mPivot.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
}

void HatchIntake::SetupMotionMagic()
{
  mPivot.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, kTimeout_10Millis);
  mPivot.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, kTimeout_10Millis);

  mPivot.ConfigNominalOutputForward(0, kTimeout_10Millis);
  mPivot.ConfigNominalOutputReverse(0, kTimeout_10Millis);
  mPivot.ConfigPeakOutputForward(1, kTimeout_10Millis);
  mPivot.ConfigPeakOutputReverse(-1, kTimeout_10Millis);
  constexpr double kF {0}; // feedforward is 0 for position
  constexpr double kP {calcP()};
  constexpr double kI {0};
  constexpr double kD {0};
  const double kMaxVelocity {1200};//encoderFwd}; // Read as encoderFwd/sec Move from 0 to max forward in 1 sec
  const double kCruiseVelocity {1000}; //Sensor Units per 100ms
  const double kMotionAcceleration {1800};//kCruiseVelocity * 0.25}; //Sensor Units per 100ms/sec
  mPivot.SelectProfileSlot(kSlotIndex, kPID_PrimaryClosedLoop);
  mPivot.Config_kF(kSlotIndex, kF, kTimeout_10Millis);
  mPivot.Config_kP(kSlotIndex, kP, kTimeout_10Millis);
  mPivot.Config_kI(kSlotIndex, kI, kTimeout_10Millis);
  mPivot.Config_kD(kSlotIndex, kD, kTimeout_10Millis);
  mPivot.ConfigMotionCruiseVelocity(kCruiseVelocity, kTimeout_10Millis);
  mPivot.ConfigMotionAcceleration(kMotionAcceleration, kTimeout_10Millis); 
}

double HatchIntake::GetPositionError() {
  return mPivot.GetClosedLoopError(kSlotIndex);
}

void HatchIntake::ResetArmEncoder() {
  mPivot.SetSelectedSensorPosition(0, kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

int HatchIntake::GetArmPotValue() {
  return armPot.GetValue();
}

void HatchIntake::GetArmValuesFwd() {
  potFwd = GetArmPotValue();
  encoderFwd = GetPosition();
}

void HatchIntake::GetArmValuesRev() {
  potRev = GetArmPotValue();
  encoderRev = GetPosition();
  mHatchFwdSoftLimit = encoderFwd;
  mHatchRevSoftLimit = encoderRev;
  SetSoftLimits();
  LineCalculator potToEncoder(potFwd, encoderFwd, potRev, encoderRev);
  mArmSlope = potToEncoder.slope();
  mArmYIntercept = potToEncoder.yIntercept();
}

void HatchIntake::SetArmValue() {
  mPivot.SetSelectedSensorPosition(
    LineCalculator(mArmSlope, mArmYIntercept)(armPot.GetValue()), 
    kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

void HatchIntake::SetSoftLimits() {
  // TODO: Is this side affect on purpose?
  encoderFwd = mHatchFwdSoftLimit;
  encoderRev = mHatchRevSoftLimit;
  mPivot.ConfigForwardSoftLimitEnable(true);
  mPivot.ConfigForwardSoftLimitThreshold(encoderFwd);
  mPivot.ConfigReverseSoftLimitEnable(true);
  mPivot.ConfigReverseSoftLimitThreshold(encoderRev);
}

void HatchIntake::UpdateSpeed() {
  mPivot.Set(ControlMode::PercentOutput, mMotorSpeed);
}

void HatchIntake::UpdatePosition() {
  mPivot.Set(ControlMode::MotionMagic, mMotorPosition);
}

void HatchIntake::SetAngleValue() {
  encoderRev = GetPosition();
  LineCalculator angleToEncoder(90.0, encoderFwd, -90.0, encoderRev);
  mAngleSlope = angleToEncoder.slope();
  mAngleYIntercept = angleToEncoder.yIntercept();
}

double HatchIntake::GetEncoderFromAngle(double angle) {
  double encoder = LineCalculator(mAngleSlope, mAngleYIntercept)(angle);
  return encoder;
}

double HatchIntake::GetArmPotVoltage(){
  return armPot.GetVoltage();
}

bool HatchIntake::IsEngage() {
  return mPuncher.Get() == kMotorEngage;
}

void HatchIntake::ResetPosition() {
  double encoder = GetPosition();
  PivotPosition(encoder);
}

double HatchIntake::GetCurrent() {
  return mPivot.GetOutputCurrent();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.