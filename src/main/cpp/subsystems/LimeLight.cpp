/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LimeLight.h"
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <pathfinder.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

const char LimeLight::kSubsystemName[] = "LimeLight";

std::shared_ptr<LimeLight> LimeLight::self;

std::shared_ptr<LimeLight> LimeLight::getInstance() {
  if (! self) {
     self = std::shared_ptr<LimeLight>(new LimeLight);
  }
  return self;
}

//.....Constants.....
const int pointLength {2};
constexpr double angleCoefficiant {75};
constexpr double kTimeStep_Seconds {0.001};
constexpr double kMaxVelocityMPS {15.0};
constexpr double kMaxAccelerationMPSPS {10.0};
constexpr double kMaxJerkMPSPSPS {60.0};
//.....LimeLight Variables.....
double targetOffsetAngleHorizontal;
double targetOffsetAngleHorizontalL;
double targetOffsetAngleHorizontalS;
double targetArea;
double targetAreaL;
double targetAreaS;
//.....Calculated Variables.....
double distanceFromTargetInches;
double distanceFromTarget;
double driveSpeed;
double targetAngle;
//.....NetworkTable shared pointer.....
std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

LimeLight::LimeLight() : Subsystem(kSubsystemName) {}

void LimeLight::InitDefaultCommand() {
}
void LimeLight::SetVariables() {
  double targetOffsetAngleHorizontal = table->GetNumber("tx", 0.0);
  double targetOffsetAngleHorizontalL = table->GetNumber("tx0", 0.0);
  double targetOffsetAngleHorizontalS = table->GetNumber("tx1", 0.0);
  double targetArea = table->GetNumber("ta", 0.0);
  double targetAreaL = table->GetNumber("ta0", 0.0);
  double targetAreaS = table->GetNumber("ta1", 0.0);
}

double LimeLight::GetDistanceToTargetInches() {
  distanceFromTargetInches = 69.291 * exp(-1.51 * targetArea);
  return distanceFromTargetInches;
}

double LimeLight::GetTargetAngle() {
  targetAngle = (targetAreaL - targetAreaS) * (2.08 * distanceFromTargetInches);
  if (targetOffsetAngleHorizontalL < targetOffsetAngleHorizontalS) {
    targetAngle = targetAngle * -1;
  }
  else {
    targetAngle = targetAngle * 1;
  }
  return targetAngle;
}

void LimeLight::SetPath() {
  SetVariables();
  GetDistanceToTargetInches();
  GetTargetAngle();

  Waypoint points[pointLength];

  Waypoint p1 = { 0, 0, 0 };
  Waypoint p2 = { distanceFromTargetInches, 0, -(targetAngle) };
  points[0] = p1;
  points[1] = p2;


  TrajectoryCandidate candidate;

  pathfinder_prepare(points, pointLength, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 
    kTimeStep_Seconds, 
    kMaxVelocityMPS, 
    kMaxAccelerationMPSPS, 
    kMaxJerkMPSPSPS, 
    &candidate);

  int length = candidate.length;

  // Segment *trajectory = static_cast<Segment *>(malloc(length * sizeof(Segment)));
  std::vector<Segment> trajectory(length);
  pathfinder_generate(&candidate, trajectory.data());
}