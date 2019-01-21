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
  right1Wheel{RobotMap::kIDRight1Wheel},
  right2Wheel{RobotMap::kIDRight2Wheel},
  left1Wheel{RobotMap::kIDLeft1Wheel},
  left2Wheel{RobotMap::kIDLeft2Wheel}
  {
    right1Wheel.SetInverted(true);
    right2Wheel.SetInverted(true);
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

