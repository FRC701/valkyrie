/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotMap.h"
#include "subsystems/Elevator.h"
using RobotMap::kPID_PrimaryClosedLoop;
using RobotMap::kTimeout_10Millis;

namespace
{
constexpr int kSlotIndex {0};
constexpr int kForwardSoftLimit {1234567890}; // TODO, please fix this number or else interrupted

constexpr double calcFeedforward() {
  constexpr double kMaxUnitsPer100ms {3675.0};
  // constexpr double kUnitsPerRev = 4096.0;
  // double rpm = (kMaxUnitsPer100ms * 600.0) / kUnitsPerRev;
  double feedforward {1023.0 / kMaxUnitsPer100ms};
  return feedforward;
}

constexpr double calcP(){
  constexpr double kEigthUnitsPerRev {4096.0/ 1.0};
  double pGain {1* 1023.0/kEigthUnitsPerRev};
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

Elevator::Elevator() : Subsystem("Elevator"),
      mLeftElevator(RobotMap::kIDLeftElevator),
      mRightElevator(RobotMap::kIDRightElevator)

      {
		SetUpTalons();
      }



void Elevator::InitDefaultCommand() {

}

void Elevator::SetElevator(double speed) {
          mRightElevator.Set(ControlMode::PercentOutput,speed);
}

void Elevator::SetElevatorPosition(double position){
   mRightElevator.Set(ControlMode::MotionMagic, position);
}

void Elevator::SetUpTalons(){
  mRightElevator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
			kPID_PrimaryClosedLoop,
			kTimeout_10Millis);
	mRightElevator.ConfigForwardSoftLimitEnable(true, kTimeout_10Millis);
	mRightElevator.ConfigForwardSoftLimitThreshold(kForwardSoftLimit);
	mRightElevator.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
	mRightElevator.SetSensorPhase(true);
	mRightElevator.SetInverted(false);
	mRightElevator.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
	mRightElevator.ConfigPeakOutputReverse(-0.02, kTimeout_10Millis);

	mLeftElevator.SetInverted(true);
	mLeftElevator.Follow(mRightElevator);
	mLeftElevator.ConfigForwardSoftLimitEnable(true, kTimeout_10Millis);
	mLeftElevator.ConfigForwardSoftLimitThreshold(kForwardSoftLimit);
}

bool Elevator::IsRevLimitSwitchClosed() {
	return mRightElevator.GetSensorCollection().IsRevLimitSwitchClosed();
}
void Elevator::SetUpMotionMagic() {
  mRightElevator.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, kTimeout_10Millis);
  mRightElevator.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, kTimeout_10Millis);

  mRightElevator.ConfigNominalOutputForward(0, kTimeout_10Millis);
  mRightElevator.ConfigNominalOutputReverse(0, kTimeout_10Millis);
  mRightElevator.ConfigPeakOutputForward(1, kTimeout_10Millis);
  mRightElevator.ConfigPeakOutputReverse(-1, kTimeout_10Millis);

  constexpr double kF {calcFeedforward()};
  constexpr double kP {calcP()};
  constexpr double kI {0};
  constexpr double kD {0};
  constexpr double kMaxVelocity {3675};
  constexpr double kCruiseVelocity {kMaxVelocity}; //Sensor Units per 100ms
  constexpr double kMotionAcceleration {kCruiseVelocity * 2}; //Sensor Units per 100ms/sec

  mRightElevator.SelectProfileSlot(kSlotIndex, kPID_PrimaryClosedLoop);
  mRightElevator.Config_kF(kSlotIndex, kF, kTimeout_10Millis);
  mRightElevator.Config_kP(kSlotIndex, kP, kTimeout_10Millis);
  mRightElevator.Config_kI(kSlotIndex, kI, kTimeout_10Millis);
  mRightElevator.Config_kD(kSlotIndex, kD, kTimeout_10Millis);
  mRightElevator.ConfigMotionCruiseVelocity(kCruiseVelocity, kTimeout_10Millis);
  mRightElevator.ConfigMotionAcceleration(kMotionAcceleration, kTimeout_10Millis);
}

/*double Elevator::GetPosError() {
	return RightElevator.GetClosedLoopError(kSlotIndex);
}*/


