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
    	void SetUpTalons();
      }



void Elevator::InitDefaultCommand() {

}

void Elevator::SetElevator(double speed) {
          mRightElevator.Set(ControlMode::PercentOutput,speed);
		  mLeftElevator.Set(ControlMode::PercentOutput,speed);
}

/*void SetElevatorPos(int position){
  RightElevator.Set(ControlMode::MotionMagic, position);
}*/

void Elevator::SetUpTalons(){
  mRightElevator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
			kPID_PrimaryClosedLoop,
			kTimeout_10Millis);
	mRightElevator.ConfigForwardSoftLimitEnable(false, kTimeout_10Millis);
	mRightElevator.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
	mRightElevator.SetSensorPhase(true);
	mRightElevator.SetInverted(false);
	mRightElevator.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
	mRightElevator.ConfigPeakOutputReverse(-0.02, kTimeout_10Millis);

	mLeftElevator.SetInverted(true);
	mLeftElevator.Follow(mRightElevator);

}

bool Elevator::IsRevLimitSwitchClosed() {
	return mRightElevator.GetSensorCollection().IsRevLimitSwitchClosed();
}

/*double Elevator::GetPosError() {
	return RightElevator.GetClosedLoopError(kSlotIndex);
}*/


