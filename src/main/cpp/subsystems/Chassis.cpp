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
  rightEncoder{right1Wheel.GetEncoder()}
  {
    left1Wheel.SetRampRate(1.0);
    left2Wheel.SetRampRate(1.0);
    right1Wheel.SetRampRate(1.0);
    right2Wheel.SetRampRate(1.0);

    left1Wheel.SetInverted(true);
    left2Wheel.SetInverted(true);

    //right2Wheel.Follow(right1Wheel);
    //left2Wheel.Follow(left1Wheel); 
  }

void Chassis::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new TankDrive);
}

void Chassis::SetTankDrive(double left, double right) {
  left1Wheel.Set(left);
  right1Wheel.Set(right);
  left2Wheel.Set(left);
  right2Wheel.Set(right);

}

void Chassis::DriveChassis(double speed) {
  left1Wheel.Set(speed);
  left2Wheel.Set(speed);
  right1Wheel.Set(speed);
  right2Wheel.Set(speed);
}

double Chassis::GetLeftPosition() {
  return leftEncoder.GetPosition();
}

double Chassis::GetRightPosition() {
  return rightEncoder.GetPosition();

}

