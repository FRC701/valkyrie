#pragma once

namespace RobotMap 
{

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 //Chassis Motors   
constexpr int kIDRight1Wheel {1};
constexpr int kIDRight2Wheel {2};
constexpr int kIDLeft1Wheel {3};
constexpr int kIDLeft2Wheel {4};

//Elevator motors
constexpr int kIDLeftElevator {5};
constexpr int kIDRightElevator {6};

//Climber motors
constexpr int kIDClimberDriveMotor {7};
constexpr int kIDClimberLiftMotor {8};

//Cargo Motors
constexpr int kIDCargoRoller {9};

//Hatch Motors
constexpr int kIDHatchPivot {10};

//Hatch Pnuematics
constexpr int kIDHatchPuncherForward {1};
constexpr int kIDHatchPuncherReverse {6};


//Cargo Pneumatics
constexpr int kIDCargoClawForward {3};
constexpr int kIDCargoClawReverse {4};
constexpr int kIDCargoPuncherForward {0};
constexpr int kIDCargoPuncherReverse {7};
constexpr int kIDCargoPneumaticForward {2};
constexpr int kIDCargoPneumaticReverse {5};

//Climber Pnuematics
constexpr int kIDClimberForward {0};
constexpr int kIDClimberReverse {7}; 

constexpr int kIDArmPot {3};
constexpr int kPID_PrimaryClosedLoop {0};
constexpr int kPID_CascadedClosedLoop {1};

constexpr int kTimeout_DontBlock {0};
constexpr int kTimeout_10Millis {10};

constexpr int kSlot0 {0};
constexpr int kSlot1 {1};
}

