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

#include <frc/Preferences.h>

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
    constexpr double kGainRatio {1.0};
    constexpr double pGain = kGainRatio * 1023.0 / kEigthUnitsPerRev;
    return pGain;
  }

  const std::string kArmSlope { "ArmSlope" };
  const std::string kArmYIntercept { "ArmYIntercept" };
  const std::string kHatchFwdSoftLimit { "HatchFwdSoftLimit" };
  const std::string kHatchRevSoftLimit { "HatchRevSoftLimit" };
  const std::string kAngleSlope { "AngleSlope" };
  const std::string kAngleYIntercept { "AngleYIntercept" };
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
mMotorPosition{0}
{
  SetUpTalons();
  SetupMotionMagic();
}

void HatchIntake::InitDefaultCommand() {
  SetDefaultCommand(new HatchIntakeSpeedDefaultCommand);
  // SetDefaultCommand(new HatchIntakeDefaultCommand); // TODO: When we're happy with positions.
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
void HatchIntake::SetUpTalons() {
  mPivot.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
                                       kPID_PrimaryClosedLoop,
                                       kTimeout_10Millis);
  mPivot.ConfigForwardSoftLimitEnable(false, kTimeout_10Millis);
  mPivot.ConfigReverseSoftLimitEnable(false, kTimeout_10Millis);
  mPivot.ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.SetSensorPhase(false);
  mPivot.SetInverted(true);
  mPivot.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
  mPivot.ConfigPeakOutputReverse(-0.1, kTimeout_10Millis);

  SetArmValue();
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
  constexpr double kF {0.128 /* calcFeedforward() */};
  constexpr double kP {calcP()};
  constexpr double kI {0};
  constexpr double kD {0};
  const double kMaxVelocity {800};//encoderFwd}; // Read as encoderFwd/sec Move from 0 to max forward in 1 sec
  const double kCruiseVelocity {800}; //Sensor Units per 100ms
  const double kMotionAcceleration {800};//kCruiseVelocity * 0.25}; //Sensor Units per 100ms/sec
  mPivot.SelectProfileSlot(kSlotIndex, kPID_PrimaryClosedLoop);
  mPivot.Config_kF(kSlotIndex, kF, kTimeout_10Millis);
  mPivot.Config_kP(kSlotIndex, kP, kTimeout_10Millis);
  mPivot.Config_kI(kSlotIndex, kI, kTimeout_10Millis);
  mPivot.Config_kD(kSlotIndex, kD, kTimeout_10Millis);
  mPivot.ConfigMotionCruiseVelocity(kCruiseVelocity, kTimeout_10Millis);
  mPivot.ConfigMotionAcceleration(kMotionAcceleration, kTimeout_10Millis); 
}

int HatchIntake::GetPositionError() {
  return mPivot.GetClosedLoopError(kSlotIndex);
}

void HatchIntake::ResetArmEncoder() {
  mPivot.SetSelectedSensorPosition(0, kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

int HatchIntake::GetArmPotValue() {
  return armPot.GetValue();
}

void HatchIntake::GetArmValuesFwd() {
  potFwd = armPot.GetValue();
  encoderFwd = mPivot.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
}

void HatchIntake::GetArmValuesRev() {
  potRev = armPot.GetValue();
  encoderRev = mPivot.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
  Preferences::GetInstance()->PutInt(kHatchFwdSoftLimit, encoderFwd);
  Preferences::GetInstance()->PutInt(kHatchRevSoftLimit, encoderRev);
  SetSoftLimits();
  LineCalculator potToEncoder(potFwd, encoderFwd, potRev, encoderRev);
  Preferences::GetInstance()->PutDouble(kArmSlope, potToEncoder.slope());
  Preferences::GetInstance()->PutDouble(kArmYIntercept, potToEncoder.yIntercept());
}

int HatchIntake::GetEncoderValue() {
  return mPivot.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
}

void HatchIntake::SetArmValue() {
  double armSlope = Preferences::GetInstance()->GetDouble(kArmSlope);
  double armYIntercept = Preferences::GetInstance()->GetDouble(kArmYIntercept);
  mPivot.SetSelectedSensorPosition(
    LineCalculator(armSlope, armYIntercept)(armPot.GetValue()), 
    kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

void HatchIntake::SetSoftLimits() {
  encoderFwd = Preferences::GetInstance()->GetInt(kHatchFwdSoftLimit);
  encoderRev = Preferences::GetInstance()->GetInt(kHatchRevSoftLimit);
  mPivot.ConfigForwardSoftLimitEnable(true);
  mPivot.ConfigForwardSoftLimitThreshold(7000);//encoderFwd);
  mPivot.ConfigReverseSoftLimitEnable(true);
  mPivot.ConfigReverseSoftLimitThreshold(-8000);//encoderRev);
}

void HatchIntake::UpdateSpeed() {
  mPivot.Set(ControlMode::PercentOutput, mMotorSpeed);
}

void HatchIntake::UpdatePosition() {
  mPivot.Set(ControlMode::MotionMagic, mMotorPosition);
}

void HatchIntake::SetAngleValue() {
  encoderRev = mPivot.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
  LineCalculator angleToEncoder(90., encoderFwd, -90, encoderRev);
  Preferences::GetInstance()->PutInt(kAngleSlope, angleToEncoder.slope());
  Preferences::GetInstance()->PutInt(kAngleYIntercept, angleToEncoder.yIntercept());
}

double HatchIntake::GetEncoderFromAngle(double angle) {
  int angleSlope = Preferences::GetInstance()->GetInt(kAngleSlope);
  int angleYIntercept = Preferences::GetInstance()->GetInt(kAngleYIntercept);
  double encoder = LineCalculator(angleSlope, angleYIntercept)(angle);
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
// Put methods for controlling this subsystem
// here. Call these from Commands.