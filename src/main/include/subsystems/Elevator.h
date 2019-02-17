/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

class Elevator : public frc::Subsystem {
 private:
      	static const char kSubsystemName[];
      	static std::shared_ptr<Elevator> self;
        WPI_TalonSRX mLeftElevator;
        WPI_TalonSRX mRightElevator;

        void SetUpTalons();

        double mMotorSpeed;
        double mMotorPos;
  
 public:
        static std::shared_ptr<Elevator> getInstance();

        Elevator();
        void InitDefaultCommand() override;
        void SetElevatorSpeed(double speed);
        void SetElevatorPosition(double position);
        bool IsFwdLimitSwitchClosed();
        //double GetPosError();
        void SetUpMotionMagic();
        void UpdateSpeed();
        void UpdatePos();
        double GetEncoderValue();
        void ResetElevatorEncoder();
        double GetRightCurrent();
        double GetLeftCurrent();
        double GetRightVoltage();
        double GetLeftVoltage();
        bool IsRevLimitSwitchClosed();
        double EncoderTicksToInches(double inches);
        double GetEncoderFromAngle(double angle);


};
