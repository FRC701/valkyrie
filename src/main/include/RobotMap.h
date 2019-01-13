#pragma once

namespace RobotMap 
{

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

//Climber motors
constexpr int kIDClimberDriveMotor {7};
constexpr int kIDClimberLiftMotor {8};

//Cargo Motors
constexpr int kIDCargoRoller {9};

//Hatch Motors
constexpr int kIDHatchPivot {10};
constexpr int kIDHatchPuncherForward {2};
constexpr int kIDHatchPuncherReverse {6};

//Hatch Pnuematics
constexpr int kIDHatchPuncherForward {1};
constexpr int kIDHatchPuncherReverse {5};


//Cargo Pneumatics
constexpr int kIDCargoClawForward {2};
constexpr int kIDCargoClawReverse {6};
constexpr int kIDCargoPuncherForward {3};
constexpr int kIDCargoPuncherReverse {7};
constexpr int kIDCargoPneumaticForward {4};
constexpr int kIDCargoPneumaticReverse {8};

//Climber Pnuematics
constexpr int kIDClimberForward {1};
constexpr int kIDClimberReverse {5}; 
}

