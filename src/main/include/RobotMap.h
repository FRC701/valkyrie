#pragma once

namespace RobotMap 
{

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
    
constexpr int kIDRight1Wheel {1};
constexpr int kIDRight2Wheel {2};
constexpr int kIDLeft1Wheel {3};
constexpr int kIDLeft2Wheel {4};

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



constexpr int kIDClimberDriveMotor {5};
constexpr int kIDClimberLiftMotor {5};
constexpr int kIDClimberForward {5};
constexpr int kIDClimberReverse {5}; 
}

