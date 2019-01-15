#ifndef _ELEVATOR_H
#define _ELEVATOR_H
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "RobotMap.h"
#include <frc/commands/Subsystem.h>
#include <frc/AnalogInput.h>
#include <frc/Preferences.h>

class Elevator : public frc::Subsystem {
 private:
      	static const char kSubsystemName[];
      	static std::shared_ptr<Elevator> self;
        WPI_TalonSRX LeftElevator;
        WPI_TalonSRX RightElevator;

        //void SetUpTalons();
  
 public:
        static std::shared_ptr<Elevator> getInstance();

        Elevator();
        void InitDefaultCommand() override;
        void SetElevator(double speed);
        //void SetElevatorPos(int position);
        bool IsFwdLimitSwitchClosed();
        bool IsRevLimitSwitchClosed();
        //double GetPosError();



};

#endif
