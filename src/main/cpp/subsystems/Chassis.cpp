#include "subsystems/Chassis.h"
#include "RobotMap.h"
#include "commands/TankDrive.h"
#include <pathfinder.h>

#include <stdlib.h>

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

#include <vector>

void Chassis::Pathfinder() {
  const int pointLength = 3;

  Waypoint points[pointLength];

  Waypoint p1 = { -4, -1, d2r(45) };
  Waypoint p2 = { -1, 2, 0};
  Waypoint p3 = { 2, 4, 0 };
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;


  TrajectoryCandidate candidate;

  constexpr double kTimeStep_Seconds = 0.001;
  constexpr double kMaxVelocity_meters_per_second = 15.0;
  constexpr double kMaxAcceleration_meters_per_second_per_second = 10.0;
  constexpr double kMaxJerk_yeah_you_type_it_out = 60.0;
  pathfinder_prepare(points, pointLength, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 
    kTimeStep_Seconds, 
    kMaxVelocity_meters_per_second, 
    kMaxAcceleration_meters_per_second_per_second, 
    kMaxJerk_yeah_you_type_it_out, 
    &candidate);

  int length = candidate.length;

  // Segment *trajectory = static_cast<Segment *>(malloc(length * sizeof(Segment)));
  std::vector<Segment> trajectory(length);
  pathfinder_generate(&candidate, trajectory.data());

}
