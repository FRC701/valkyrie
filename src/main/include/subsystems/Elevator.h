/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Preferences.h>

#include <ctre/Phoenix.h>

#include "utilities/Preference.h"

class Elevator : public frc::Subsystem {
 private:
      	static const char kSubsystemName[];
      	static std::shared_ptr<Elevator> self;
        WPI_TalonSRX mLeftElevator;
        WPI_TalonSRX mRightElevator;

        void SetUpTalons();

        double mMotorSpeed;
        double mMotorPos;

        frc::Command* mPositionDefaultCommand;
        frc::Command* mSpeedDefaultCommand;
  
       // Private functions -- use the abstraction 
       bool IsFwdLimitSwitchClosed();
       bool IsRevLimitSwitchClosed();

       using BoolPreference = Preference<frc::Preferences, bool>;

       BoolPreference mSensorPhase;
 public:
        static std::shared_ptr<Elevator> getInstance();

        Elevator();
        void InitDefaultCommand() override;
        void SetPositionDefaultCommand();
        void SetSpeedDefaultCommand();
        void SetElevatorSpeed(double speed);
        void SetElevatorPosition(double position);
        bool IsElevatorDown();
        void SetUpMotionMagic();
        void UpdateSpeed();
        void UpdatePos();
        double GetEncoderValue();
        void ResetElevatorEncoder();
        double GetRightCurrent();
        double GetLeftCurrent();
        double GetRightVoltage();
        double GetLeftVoltage();
        double InchesToEncoderTicks(double inches);
        void SetElevatorPositionInches(double inches);
       
       void ResetPosition();
       double GetEncoderError();
};
