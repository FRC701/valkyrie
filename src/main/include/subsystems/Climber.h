/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>
#include "rev/CANSparkMax.h"

class Climber : public frc::Subsystem {
 private:

        static const char kSubsystemName[];
        static std::shared_ptr<Climber> self;

        WPI_TalonSRX mDriveMotor;
        rev::CANSparkMax  mLiftMotor;
        frc::DoubleSolenoid mLiftSolenoid;
        double mDriveMotorSpeed;
        double mLiftMotorSpeed;
       
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
        static std::shared_ptr<Climber> getInstance();

        Climber();
        void InitDefaultCommand() override;
        void Engage();
        void Disengage();
        void MotorClimber(double speed);
        void DriveClimb(double speed);
        void Update();
};
