#include "subsystems/Chassis.h"
#include "RobotMap.h"
#include "commands/TankDrive.h"

const char Chassis::kSubsystemName[] = "Chassis";

std::shared_ptr<Chassis> Chassis::self;

std::shared_ptr<Chassis> Chassis::getInstance() {
  if (! self) {
     self = std::shared_ptr<Chassis>(new Chassis);
  }
  return self;
}



Chassis::Chassis() : Subsystem(kSubsystemName),
  //defaultCommand(nullptr),
  right1Wheel{RobotMap::kIDRight1Wheel, rev::CANSparkMax::MotorType::kBrushless},
  right2Wheel{RobotMap::kIDRight2Wheel, rev::CANSparkMax::MotorType::kBrushless},
  left1Wheel{RobotMap::kIDLeft1Wheel, rev::CANSparkMax::MotorType::kBrushless},
  left2Wheel{RobotMap::kIDLeft2Wheel, rev::CANSparkMax::MotorType::kBrushless},
  leftEncoder{left1Wheel.GetEncoder()},
  rightEncoder{right1Wheel.GetEncoder()},
  mIsHighGear(true)
  {
    left1Wheel.SetRampRate(0.2);
    left2Wheel.SetRampRate(0.2);
    right1Wheel.SetRampRate(0.2);
    right2Wheel.SetRampRate(0.2);

    right1Wheel.SetInverted(true);
    right2Wheel.SetInverted(true);

    //right2Wheel.Follow(right1Wheel);
    //left2Wheel.Follow(left1Wheel); 
  }

void Chassis::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new TankDrive);
}

void Chassis::SetTankDrive(double left, double right) {
  constexpr auto kHighGear = 0.75;
  constexpr auto kLowGear = 0.25;

  if (IsHighGear())
  {
    left *= kHighGear;
    right *= kHighGear;
  } else {
    left *= kLowGear;
    right *= kLowGear;
 }

  left1Wheel.Set(left);
  right1Wheel.Set(right);
  left2Wheel.Set(left);
  right2Wheel.Set(right);

}

void Chassis::DriveChassis(double speed) {
  left1Wheel.Set(speed*.75);
  left2Wheel.Set(speed*.75);
  right1Wheel.Set(speed*.75);
  right2Wheel.Set(speed*.75);
}

double Chassis::GetLeftPosition() {
  return leftEncoder.GetPosition();
}

double Chassis::GetRightPosition() {
  return rightEncoder.GetPosition();
}

double Chassis::GetLeftCurrent() {
  return left1Wheel.GetOutputCurrent();
}

double Chassis::GetRightCurrent() {
  return right1Wheel.GetOutputCurrent();
}

double Chassis::GetLeftVoltage() {
  return left1Wheel.GetAppliedOutput();
}

double Chassis::GetRightVoltage() {
  return right2Wheel.GetAppliedOutput();
}
