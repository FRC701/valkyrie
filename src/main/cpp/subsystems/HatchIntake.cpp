/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchIntake.h"
#include <frc/Preferences.h>
using RobotMap::kPID_PrimaryClosedLoop;
using RobotMap::kTimeout_10Millis;

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
    constexpr double kEigthUnitsPerRev = 4096.0/ 1.0;
    double pGain = 1* 1023.0/kEigthUnitsPerRev;
    return pGain;
  }
}

const char HatchIntake::kSubsystemName[] = "HatchIntake";

const std::string kKey = "ArmScale";
const std::string kKeyPot = "ArmPotBottom";

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
armPot(RobotMap::kIDArmPot)
{

}

void HatchIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void HatchIntake::Engage() {
  mPuncher.Set(kMotorEngage);
}

void HatchIntake::Disengage() {
  mPuncher.Set(kMotorDisengage);
}

void HatchIntake::Pivot(double speed) {

}
void HatchIntake::SetUpTalons() {
  mPivot.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
                                       kPID_PrimaryClosedLoop,
                                       kTimeout_10Millis);
  mPivot.ConfigForwardSoftLimitEnable(false, kTimeout_10Millis);
  mPivot.ConfigReverseSoftLimitEnable(false, kTimeout_10Millis);
  mPivot.ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
  mPivot.SetSensorPhase(true);
  mPivot.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
  mPivot.ConfigPeakOutputReverse(-0.02, kTimeout_10Millis);



  mPivot.SetSelectedSensorPosition(CalculateEncoderPos(), RobotMap::kPID_PrimaryClosedLoop, kTimeout_10Millis);
 
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
  constexpr double kF {calcFeedforward()};
  constexpr double kP {calcP()};
  constexpr double kI {0};
  constexpr double kD {0};
  constexpr double kMaxVelocity {3675};
  constexpr double kCruiseVelocity {kMaxVelocity}; //Sensor Units per 100ms
  constexpr double kMotionAcceleration {kCruiseVelocity * 2}; //Sensor Units per 100ms/sec
  mPivot.SelectProfileSlot(kSlotIndex, kPID_PrimaryClosedLoop);
  mPivot.Config_kF(kSlotIndex, kF, kTimeout_10Millis);
  mPivot.Config_kP(kSlotIndex, kP, kTimeout_10Millis);
  mPivot.Config_kI(kSlotIndex, kI, kTimeout_10Millis);
  mPivot.Config_kD(kSlotIndex, kD, kTimeout_10Millis);
  mPivot.ConfigMotionCruiseVelocity(kCruiseVelocity, kTimeout_10Millis);
  mPivot.ConfigMotionAcceleration(kMotionAcceleration, kTimeout_10Millis); 
}

int HatchIntake::GetPositionError(){
  return mPivot.GetClosedLoopError(kSlotIndex);
}

int HatchIntake::GetArmPotValue(){
  return armPot.GetValue();
}

int HatchIntake::GetArmPotVoltage(){
  return armPot.GetVoltage();
}

void HatchIntake::ResetArmPos(){
  mPivot.SetSelectedSensorPosition(0, kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

void HatchIntake::SetArmPositionDown(int potentiometer, int encoder)
{
  calibrateEncoderDown = encoder;
  calibratePotDown = potentiometer;
}

void HatchIntake::SetArmPositionUp(int potentiometer, int encoder)
{
  double scaleFactor = (calibrateEncoderDown - encoder) / (calibratePotDown - potentiometer);
  frc::Preferences::GetInstance()->PutDouble(kKey, scaleFactor);
  frc::Preferences::GetInstance()->PutDouble(kKeyPot, calibratePotDown);
}

int HatchIntake::CalculateEncoderPos()
{
  return frc::Preferences::GetInstance()->GetDouble(kKey,0) * (HatchIntake::GetArmPotValue() - frc::Preferences::GetInstance()->GetDouble(kKeyPot,0));
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
