/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LimeLight.h"
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <vector>
#include <pathfinder.h>
#include <stdlib.h>
#include <cmath>

constexpr double angleCoefficiant = 75;
double distanceFromTarget;
double driveSpeed;

constexpr double angleCoefficiant {75};
double targetOffsetAngleHorizontal;
double targetOffsetAngleHorizontalL;
double targetOffsetAngleHorizontalS;
double targetArea;
double targetAreaL;
double targetAreaS;

double distanceFromTargetInches;

std::shared_ptr<NetworkTable> table = NetworkTableInstance::GetDefault().GetTable("limelight");


LimeLight::LimeLight() : Subsystem("ExampleSubsystem") {}

void LimeLight::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void LimeLight::GetVariables() {
  double targetOffsetAngleHorizontal = table->GetNumber("tx", 0.0);
  double targetOffsetAngleHorizontalL = table->GetNumber("tx0", 0.0);
  double targetOffsetAngleHorizontalS = table->GetNumber("tx1", 0.0);
  double targetArea = table->GetNumber("ta", 0.0);
  double targetAreaL = table->GetNumber("ta0", 0.0);
  double targetAreaS = table->GetNumber("ta1", 0.0);
}

void LimeLight::GetDistanceToTargetInches() {
  GetVariables();
  distanceFromTargetInches = 69.291 * exp(-1.51 * targetArea);
}

void LimeLight::GetTargetAngle() {
  targetAngle = (targetAreaL - targetAreaS) * 75;
  if (targetOffsetAngleHorizontalL < targetOffsetAngleHorizontalS) {
    targetAngle = targetAngle * -1;
  }
  else {
    targetAngle = targetAngle * 1;
  }
}

void LimeLight::SetPath() {
  GetDistanceToTargetInches();
  const int pointLength = 2;

  Waypoint points[pointLength];

  Waypoint p1 = { 0, 0, 0 };
  Waypoint p2 = { distanceFromTargetInches, 0, 0 };
  points[0] = p1;
  points[1] = p2;


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

// Put methods for controlling this subsystem
// here. Call these from Commands.
