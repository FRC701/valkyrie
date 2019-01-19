/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
namespace RobotMap 
{
constexpr int kIDHatchPuncherForward {16};
constexpr int kIDHatchPuncherReverse {16};
constexpr int kIDHatchPivot {16};

constexpr int kIDLeftElevator {10};
constexpr int kIDRightElevator {11};

constexpr int kIDCargoPneumaticForward {16};
constexpr int kIDCargoPneumaticReverse {16};
constexpr int kIDCargoRoller {16};
constexpr int kIDCargoLeftForward {16};
constexpr int kIDCargoLeftReverse {16};
constexpr int kIDCargoRightForward {16};
constexpr int kIDCargoRightReverse {16};
constexpr int kIDCargoPuncherForward {16};
constexpr int kIDCargoPuncherReverse {16};


}


// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
