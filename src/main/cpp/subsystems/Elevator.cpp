/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "RobotMap.h"
#include "subsystems/Elevator.h"

constexpr char Elevator::kSubsystemName[] = "Elevator";

std::shared_ptr<Elevator> Elevator::self;

std::shared_ptr<Elevator> Elevator::getInstance() {
	if (! self) {
		self = std::shared_ptr<Elevator>(new Elevator);
	}
	return self;
}

Elevator::Elevator() : Subsystem("Elevator"),
      LeftElevator(RobotMap::kIDLeftElevator),
      RightElevator(RobotMap::kIDRightElevator)

      {
       // void SetUpTalons();
      }



void Elevator::InitDefaultCommand() {

}

void Elevator::SetElevator(double speed) {
          RightElevator.Set(ControlMode::PercentOutput,speed);
		  LeftElevator.Set(ControlMode::PercentOutput,speed);
}

/*void SetElevatorPos(int position){
  RightElevator.Set(ControlMode::MotionMagic, position);
}*/

/*void Elevator::SetUpTalons(){
  RightElevator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
			kPID_PrimaryClosedLoop,
			kTimeout_10Millis);
	RightElevator.ConfigForwardSoftLimitEnable(false, kTimeout_10Millis);
	RightElevator.ConfigReverseSoftLimitEnable(false, kTimeout_10Millis);
	RightElevator.ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
	RightElevator.ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, kTimeout_10Millis);
	RightElevator.SetSensorPhase(true);
	RightElevator.SetInverted(false);
	RightElevator.ConfigPeakOutputForward(0.1, kTimeout_10Millis);
	RightElevator.ConfigPeakOutputReverse(-0.02, kTimeout_10Millis);

	LeftElevator.SetInverted(true);
	LeftElevator.Follow(RightElevator);

}*/

bool Elevator::IsFwdLimitSwitchClosed() {
	return RightElevator.GetSensorCollection().IsFwdLimitSwitchClosed();
}

bool Elevator::IsRevLimitSwitchClosed() {
	return RightElevator.GetSensorCollection().IsRevLimitSwitchClosed();
}

/*double Elevator::GetPosError() {
	return RightElevator.GetClosedLoopError(kSlotIndex);
}*/


