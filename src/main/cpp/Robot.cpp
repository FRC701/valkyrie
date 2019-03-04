/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "subsystems/CargoIntake.h"
#include "subsystems/Chassis.h"
#include "subsystems/Elevator.h"
#include "subsystems/HatchIntake.h"

ExampleSubsystem Robot::m_subsystem;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption("Default Auto", &m_defaultAuto);
  m_chooser.AddOption("My Auto", &m_myAuto);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  Chassis::getInstance();
  HatchIntake::getInstance();
  Elevator::getInstance();
  CargoIntake::getInstance();
  // Initialize the OI after all the subsystems have been setup
  OI::getInstance();

}

const void EncoderValues() {
    frc::SmartDashboard::PutNumber("Left Encoder Position", Chassis::getInstance()->GetLeftPosition());
    frc::SmartDashboard::PutNumber("Right Encoder Position", Chassis::getInstance()->GetRightPosition());
    frc::SmartDashboard::PutNumber("Arm Encoder Value", HatchIntake::getInstance()->GetEncoderValue());
    frc::SmartDashboard::PutNumber("Arm Pot Value", HatchIntake::getInstance()->GetArmPotValue());
    frc::SmartDashboard::PutNumber("Arm Pot Voltage", HatchIntake::getInstance()->GetArmPotVoltage());
    frc::SmartDashboard::PutNumber("Arm Set Point", HatchIntake::getInstance()->GetSetPoint());
    frc::SmartDashboard::PutNumber("Arm Position Error", HatchIntake::getInstance()->GetPositionError());
    frc::SmartDashboard::PutNumber("Elevator Encoder Value", Elevator::getInstance()->GetEncoderValue());
    frc::SmartDashboard::PutNumber("Right Elevator Current", Elevator::getInstance()->GetRightCurrent());
    frc::SmartDashboard::PutNumber("Left Elevator Current", Elevator::getInstance()->GetLeftCurrent());
    frc::SmartDashboard::PutNumber("Right Elevator Voltage", Elevator::getInstance()->GetRightVoltage());
    frc::SmartDashboard::PutNumber("Left Elevator Voltage", Elevator::getInstance()->GetLeftVoltage());
    frc::SmartDashboard::PutBoolean("Elevator Is Down", Elevator::getInstance()->IsElevatorDown());
    frc::SmartDashboard::PutNumber("Elevator Error", Elevator::getInstance()->GetEncoderError());
    frc::SmartDashboard::PutNumber("Left Drive Current", Chassis::getInstance()->GetLeftCurrent());
    frc::SmartDashboard::PutNumber("Right Drive Current", Chassis::getInstance()->GetRightCurrent());
    frc::SmartDashboard::PutNumber("Left Drive Voltage", Chassis::getInstance()->GetLeftVoltage());
    frc::SmartDashboard::PutNumber("Right Drive Voltage", Chassis::getInstance()->GetRightVoltage());
    frc::SmartDashboard::PutNumber("Roller current", CargoIntake::getInstance()->RollerCurrent());
}
/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
    EncoderValues();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

  Elevator::getInstance()->ResetPosition();
  HatchIntake::getInstance()->ResetPosition();

  m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }

  Elevator::getInstance()->ResetPosition();
  HatchIntake::getInstance()->ResetPosition();
}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
