#include "subsystems/Chassis.h"
#include "subsystems/Elevator.h"

#include "commands/SetControlDrive.h"

#include "RobotMap.h"

#include <networktables/NetworkTableInstance.h>

const char Chassis::kSubsystemName[] = "Chassis";

constexpr double kDefaultHighGear {0.85};

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
  m_left{left1Wheel, left2Wheel},
  m_right{right1Wheel, right2Wheel},
  m_drive{m_left, m_right},
  mLimeLightTable{nt::NetworkTableInstance::GetDefault().GetTable("limelight")},
  mIsHighGear(true),
  mHighGear(.90),
  mLowGear(0.50)
  {
    left1Wheel.SetOpenLoopRampRate(0.2);
    left2Wheel.SetOpenLoopRampRate(0.2);
    right1Wheel.SetOpenLoopRampRate(0.2);
    right2Wheel.SetOpenLoopRampRate(0.2);

    right1Wheel.SetInverted(true);
    right2Wheel.SetInverted(true);

    //right2Wheel.Follow(right1Wheel);
    //left2Wheel.Follow(left1Wheel); 

    m_drive.SetRightSideInverted(false);
  }

void Chassis::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new SetControlDrive());
}

void Chassis::SetTankDrive(double left, double right) {
  // auto elevator = Elevator::getInstance();
  auto gear = IsHighGear() ? mHighGear : mLowGear;
  // gear = elevator->IsElevatorDown() ? gear : mLowGear; // Driver does not want this feature

  left *= gear;
  right *= gear;

  m_drive.TankDrive(left, right);
}

void Chassis::SetArcadeDrive(double speed, double rotation) {
  m_drive.ArcadeDrive(speed, rotation);
}

double Chassis::GetVisionRotation() {
  constexpr double maxSpeed {1};
  constexpr double maxAngle {27.0};
  constexpr double pRotation {maxSpeed / maxAngle};
  constexpr double setPoint {0};
  double measuredValue = mLimeLightTable->GetNumber("tx",0.0);
  return pRotation * (setPoint - measuredValue);
}

double Chassis::GetVisionDepth() {
  double pDepth = 0;
  if (mLimeLightTable->GetNumber("tv",0.0) == 1) {
    constexpr double maxDepthSpeed {0.5};
    constexpr double desiredDepth {10.0};
    double currentDepth = mLimeLightTable->GetNumber("ta",0.0);
    double changeRequired = desiredDepth - currentDepth + 4;
    pDepth = (changeRequired / desiredDepth) * maxDepthSpeed;
  }
  else {
    pDepth = 0;
  }
  return pDepth;
}

void Chassis::DriveChassis(double speed) {
  m_drive.TankDrive(speed, speed);
}

double Chassis::GetLeftPosition() {
  return leftEncoder.GetPosition();
}

double Chassis::GetRightPosition() {
  return rightEncoder.GetPosition();
}

double Chassis::GetLeft1Current() {
  return left1Wheel.GetOutputCurrent();
}

double Chassis::GetLeft2Current() {
  return left2Wheel.GetOutputCurrent();
}

double Chassis::GetRight1Current() {
  return right1Wheel.GetOutputCurrent();
}

double Chassis::GetRight2Current() {
  return right2Wheel.GetOutputCurrent();
}

double Chassis::GetLeftVoltage() {
  return left1Wheel.GetAppliedOutput();
}

double Chassis::GetRightVoltage() {
  return right2Wheel.GetAppliedOutput();
}

void Chassis::SetCamVisionProcessing() {
  mLimeLightTable->PutNumber("camMode", 0);
  mLimeLightTable->PutNumber("ledMode", 0);
}

void Chassis::SetCamDriverCam() {
  mLimeLightTable->PutNumber("camMode", 1);
  mLimeLightTable->PutNumber("ledMode", 1);

}
