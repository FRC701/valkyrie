/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotMap.h"
#include "subsystems/Elevator.h"
#include "commands/ElevatorDefaultCommand.h"
#include "commands/ElevatorSpeedDefaultCommand.h"
#include "utilities/LineCalculator.h"


using RobotMap::kPID_PrimaryClosedLoop;
using RobotMap::kTimeout_10Millis;


namespace
{
constexpr int kSlotIndex {0};
//constexpr int kForwardSoftLimit {72000}; // TODO, please fix this number or else interrupted
constexpr int kForwardSoftLimit {72000 - 55000 + 50000}; // TODO, please fix this number or else interrupted

constexpr double calcFeedforward() {
  constexpr double kMaxUnitsPer100ms {3675.0};
  // constexpr double kUnitsPerRev = 4096.0;
  // double rpm = (kMaxUnitsPer100ms * 600.0) / kUnitsPerRev;
  double feedforward {1023.0 / kMaxUnitsPer100ms};
  return feedforward;
}

constexpr double calcP(){
  constexpr double kEigthUnitsPerRev {4096.0/ 1.0};
  double pGain {1.0 * 1023.0/kEigthUnitsPerRev};
  return pGain;
}
}
constexpr char Elevator::kSubsystemName[] = "Elevator";

std::shared_ptr<Elevator> Elevator::self;

std::shared_ptr<Elevator> Elevator::getInstance() {
	if (! self) {
		self = std::shared_ptr<Elevator>(new Elevator);
	}
	return self;
}

const std::string kElevatorSlope {"ElevatorSlope"};
const std::string kElevatorYIntercept {"ElevatorYIntercept"};

Elevator::Elevator() : Subsystem("Elevator"),
  mLeftElevator(RobotMap::kIDLeftElevator),
  mRightElevator(RobotMap::kIDRightElevator),
  mMotorSpeed{0},
  mMotorPos{0},
  mPositionDefaultCommand(nullptr),
  mSpeedDefaultCommand(nullptr),
  mSensorPhase(*frc::Preferences::GetInstance(), "ElevatorSensorPhase")
{
  SetUpTalons();
  SetUpMotionMagic();
}

void Elevator::InitDefaultCommand() {
    mPositionDefaultCommand = new ElevatorDefaultCommand;
    mSpeedDefaultCommand = new ElevatorSpeedDefaultCommand;
    SetPositionDefaultCommand();
}

void Elevator::SetPositionDefaultCommand() {
  SetDefaultCommand(mPositionDefaultCommand);
}

void Elevator::SetSpeedDefaultCommand() {
  SetDefaultCommand(mSpeedDefaultCommand);
}

void Elevator::SetElevatorSpeed(double speed) {
  mMotorSpeed = speed;
  UpdateSpeed();
}

void Elevator::SetElevatorPosition(double position){
  mMotorPos = position;
  UpdatePos();
}

void Elevator::SetElevatorPositionInches(double inches) {
  SetElevatorPosition(InchesToEncoderTicks(inches));
}

bool Elevator::IsElevatorDown()
{
  return IsFwdLimitSwitchClosed();
}

bool Elevator::IsFwdLimitSwitchClosed(){
  mLeftElevator.GetSensorCollection().IsFwdLimitSwitchClosed();
}

void Elevator::SetUpTalons(){
  mLeftElevator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
			kPID_PrimaryClosedLoop,
			kTimeout_10Millis);
	mLeftElevator.ConfigForwardSoftLimitEnable(true, kTimeout_10Millis);
	mLeftElevator.ConfigForwardSoftLimitThreshold(kForwardSoftLimit);
	mLeftElevator.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector,
    LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
	mLeftElevator.SetSensorPhase(mSensorPhase);
	mLeftElevator.SetInverted(true);
	mLeftElevator.ConfigPeakOutputForward(1., kTimeout_10Millis);
	mLeftElevator.ConfigPeakOutputReverse(-1., kTimeout_10Millis);

	mRightElevator.SetInverted(false);
	mRightElevator.Follow(mLeftElevator);
	mRightElevator.ConfigForwardSoftLimitEnable(true, kTimeout_10Millis);
	mRightElevator.ConfigForwardSoftLimitThreshold(kForwardSoftLimit);
  mRightElevator.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector,
    LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
}

void Elevator::SetUpMotionMagic() {
  mLeftElevator.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, kTimeout_10Millis);
  mLeftElevator.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, kTimeout_10Millis);

  mLeftElevator.ConfigNominalOutputForward(0, kTimeout_10Millis);
  mLeftElevator.ConfigNominalOutputReverse(0, kTimeout_10Millis);
  mLeftElevator.ConfigPeakOutputForward(1., kTimeout_10Millis);
  mLeftElevator.ConfigPeakOutputReverse(-1., kTimeout_10Millis);

  constexpr double kF {0};  // Feedforward should be 0 for position control
  constexpr double kP {calcP()};
  constexpr double kI {0};
  constexpr double kD {0};
  constexpr double kMaxVelocity {3675};
  constexpr double kCruiseVelocity {3000}; //Sensor Units per 100ms
  constexpr double kMotionAcceleration {3675};//kCruiseVelocity * 2}; //Sensor Units per 100ms/sec

  mLeftElevator.SelectProfileSlot(kSlotIndex, kPID_PrimaryClosedLoop);
  mLeftElevator.Config_kF(kSlotIndex, kF, kTimeout_10Millis);
  mLeftElevator.Config_kP(kSlotIndex, kP, kTimeout_10Millis);
  mLeftElevator.Config_kI(kSlotIndex, kI, kTimeout_10Millis);
  mLeftElevator.Config_kD(kSlotIndex, kD, kTimeout_10Millis);
  mLeftElevator.ConfigMotionCruiseVelocity(kCruiseVelocity, kTimeout_10Millis);
  mLeftElevator.ConfigMotionAcceleration(kMotionAcceleration, kTimeout_10Millis);
}

void Elevator::UpdateSpeed() {
  mLeftElevator.Set(ControlMode::PercentOutput, mMotorSpeed);
}

void Elevator::UpdatePos() {
  mLeftElevator.Set(ControlMode::MotionMagic, mMotorPos);
}

double Elevator::GetEncoderValue(){
	return mLeftElevator.GetSelectedSensorPosition(kPID_PrimaryClosedLoop);
}

void Elevator::ResetElevatorEncoder() {
  mLeftElevator.SetSelectedSensorPosition(0, kPID_PrimaryClosedLoop, kTimeout_10Millis);
}

double Elevator::GetRightCurrent() {
  return mRightElevator.GetOutputCurrent();
}

double Elevator::GetLeftCurrent() {
  return mLeftElevator.GetOutputCurrent();
}

double Elevator::GetRightVoltage() {
  return mRightElevator.GetMotorOutputVoltage();
}

double Elevator::GetLeftVoltage() {
  return mLeftElevator.GetMotorOutputVoltage();
}

double Elevator::InchesToEncoderTicks(double inches) {
  // TODO: get all of these values
  constexpr double encoderBottom {0.};
  constexpr double encoderTop {23000.}; 
  constexpr double inchesBottom {19.};
  constexpr double inchesTop {12. * 8.}; // 8 feet?
  LineCalculator inchesToEncoder(inchesBottom, encoderBottom, inchesTop, encoderTop);
  double encoder = inchesToEncoder(inches);
  return encoder;
}

void Elevator::ResetPosition() {
  double position = GetEncoderValue();
  SetElevatorPosition(position); 
}

bool Elevator::IsRevLimitSwitchClosed(){
  mLeftElevator.GetSensorCollection().IsRevLimitSwitchClosed();
}

double Elevator::GetEncoderError(){
  mLeftElevator.GetClosedLoopError();
}
