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
static constexpr int kIDRight1Wheel {1};
static constexpr int kIDRight2Wheel {2};
static constexpr int kIDLeft1Wheel {3};
static constexpr int kIDLeft2Wheel {4};

//Elevator motors
static constexpr int kIDLeftElevator {5};
static constexpr int kIDRightElevator {6};

//Climber motors
// static constexpr int kIDClimberDriveMotor {7};
// static constexpr int kIDClimberLiftMotor {8};

//Cargo Motors
static constexpr int kIDCargoRoller {9};

//Hatch Motors
static constexpr int kIDHatchPivot {10};

//Hatch Pnuematics
static constexpr int kIDHatchPuncherForward {1};
static constexpr int kIDHatchPuncherReverse {6};


//Cargo Pneumatics
static constexpr int kIDCargoClawForward {3};
static constexpr int kIDCargoClawReverse {4};
static constexpr int kIDCargoPuncherForward {2};
static constexpr int kIDCargoPuncherReverse {5};
static constexpr int kIDCargoPneumaticForward {0};
static constexpr int kIDCargoPneumaticReverse {7};

//Climber Pnuematics
static constexpr int kIDClimberForward {0};
static constexpr int kIDClimberReverse {7}; 

static constexpr int kIDArmPot {3};
static constexpr int kPID_PrimaryClosedLoop {0};
static constexpr int kPID_CascadedClosedLoop {1};

static constexpr int kTimeout_DontBlock {0};
static constexpr int kTimeout_10Millis {10};

static constexpr int kSlot0 {0};
static constexpr int kSlot1 {1};
}

