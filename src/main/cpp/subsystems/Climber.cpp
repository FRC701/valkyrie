/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include "commands/ClimberDefaultPositionCommand.h"
#include "commands/ClimberDefaultSpeedCommand.h"
#include "RobotMap.h"
#include "frc/DoubleSolenoid.h"

namespace
{
constexpr frc::DoubleSolenoid::Value kClimberEngage {frc::DoubleSolenoid::kForward};
constexpr frc::DoubleSolenoid::Value kClimberDisengage {frc::DoubleSolenoid::kReverse};
constexpr int kPCMID1 {1};

constexpr double calcP()
{
    // Assumption: Acheive max speed when the target is 10 revolutions
    // Tuning: 
    // * Adjust kTargetMaxRevolutions for the maximum speed at a distance in revolutions
    // * Set kMaxRPM to the maximum speed you want the motor to move
    //   (or the maximum speed the motor *can* go.)
    constexpr auto kTargetMaxRevolutions = 10.;
    constexpr auto kMaxRPM = 1000;
    constexpr auto kMaxRPS = kMaxRPM / 60.;

    constexpr auto kTargetProportion = kMaxRPS / kTargetMaxRevolutions;
    return kTargetProportion;
}

using AccelStrategy = rev::CANPIDController::AccelStrategy;
struct ConfigPIDController
{
    int pidSlot;
    double p;
    double i;
    double d;
    double f;
    double dFilter;
    double iZone;
    double outputRangeMinimum;
    double outputRangeMaximum;
    double maxVelocity_RPM;
    double maxAcceleration_RPMPM;
    double minOutputVelocity_RPM;
    double allowedClosedLoopError;
    AccelStrategy accelStrategy;
    double maxIAccumulator;
};

ConfigPIDController kConfig =
{
    /* .pidSlot = */ 0,
    /* .p = */ calcP(),
    /* .i = */ 0,
    /* .d = */ 0,
    /* .f = */ 0, // feedforward should be 0 for position
    /* .dFilter = */ 0, // TODO how is dFilter set
    /* .iZone = */ 0, // TODO how is iZone set
    /* .outputRangeMaximum = */ 1,
    /* .outputRangeMinimum = */ -1,
    /* .maxVelocity_RPM = */ 4000,
    /* .maxAcceleration_RPMPM = */ 4000,
    /* .minOutputVelocity_RPM = */ 0,
    /* .allowedClosedLoopError = */ 0.1,
    /* .accelStrategy = */ AccelStrategy::kTrapezoidal,
    /* .maxIAccumulator = */ 0.0
};

void configurePIDController(
    rev::CANPIDController& controller
    , const ConfigPIDController& config)
{
    auto pidSlot = config.pidSlot;
    controller.SetP(config.p, pidSlot);
    controller.SetI(config.i, pidSlot);
    controller.SetD(config.d, pidSlot);
    controller.SetFF(config.f, pidSlot);
    controller.SetDFilter(config.dFilter, pidSlot);
    controller.SetIZone(config.iZone, pidSlot);
    controller.SetOutputRange(
        config.outputRangeMinimum, 
        config.outputRangeMaximum,
        pidSlot);
    controller.SetSmartMotionMaxVelocity(
        config.maxVelocity_RPM,
        pidSlot);
    controller.SetSmartMotionMaxAccel(
        config.maxAcceleration_RPMPM,
        pidSlot);
    controller.SetSmartMotionMinOutputVelocity(
        config.minOutputVelocity_RPM,
        pidSlot);
    controller.SetSmartMotionAllowedClosedLoopError(
        config.allowedClosedLoopError,
        pidSlot);
    controller.SetSmartMotionAccelStrategy(
        config.accelStrategy,
        pidSlot);
    controller.SetIMaxAccum(
        config.maxIAccumulator,
        pidSlot);
}

constexpr auto kNormallyClosed = rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed;
constexpr auto kNormallyOpen = rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen;

}

std::shared_ptr<Climber> Climber::self;
std::shared_ptr<Climber> Climber::getInstance() {
  if (! self) {
    self = std::shared_ptr<Climber>(new Climber);
  }
  return self;
}

Climber::Climber() : Subsystem("Climber"), 
    mDriveMotor(RobotMap::kIDClimberDriveMotor),
    mLiftMotor{RobotMap::kIDClimberLiftMotor, rev::CANSparkMax::MotorType::kBrushless},
    mLiftMotorController{mLiftMotor.GetPIDController()},
    mLiftMotorLimit{mLiftMotor.GetReverseLimitSwitch(kNormallyOpen)},
    mLiftMotorLimitOther{mLiftMotor.GetForwardLimitSwitch(kNormallyOpen)},
    mLiftSolenoid(kPCMID1, RobotMap::kIDClimberForward, RobotMap::kIDClimberReverse),
    mLiftMotorEncoder{mLiftMotor.GetEncoder()},
    mDriveMotorSpeed{0},
    mLiftMotorSpeed{0},
    mLiftMotorPosition_revs{0.},
    mPositionDefaultCommand{nullptr},
    mSpeedDefaultCommand{nullptr},
    mEncoderOffset{mLiftMotorEncoder.GetPosition()}
{
    mLiftSolenoid.Set(kClimberDisengage);
    mDriveMotor.SetInverted(true);
    mLiftMotor.SetInverted(false);
    mLiftMotorLimit.EnableLimitSwitch(true);
    mLiftMotorLimitOther.EnableLimitSwitch(true);

    configurePIDController(mLiftMotorController, kConfig);

    Update();
}

void Climber::InitDefaultCommand() {
    mPositionDefaultCommand = new ClimberDefaultPositionCommand;
    mSpeedDefaultCommand = new ClimberDefaultSpeedCommand;
    //SetPositionDefaultCommand();
    SetSpeedDefaultCommand();
}

void Climber::SetPositionDefaultCommand() {
    SetDefaultCommand(mPositionDefaultCommand);
}

void Climber::SetSpeedDefaultCommand() {
    SetDefaultCommand(mSpeedDefaultCommand);
}

void Climber::Engage() {
    mLiftSolenoid.Set(kClimberEngage);
}

void Climber::Disengage() {
    mLiftSolenoid.Set(kClimberDisengage);
}

void Climber::MotorClimber(double speed) {
    mLiftMotorSpeed = speed;
    Update();
}

void Climber::DriveClimb(double speed) {
    mDriveMotorSpeed = speed;
    Update();
}

void Climber::ClimbPosition(double position_revs)
{
    mLiftMotorPosition_revs = position_revs;
    UpdatePosition();
}

void Climber::Update() {
    mDriveMotor.Set(mDriveMotorSpeed);
    mLiftMotor.Set(mLiftMotorSpeed);
}

void Climber::UpdatePosition() {
    mDriveMotor.Set(mDriveMotorSpeed);
    mLiftMotorController.SetReference(mLiftMotorPosition_revs, rev::ControlType::kPosition);
}

bool Climber::IsCommandFinished() {
    return false;
}

bool Climber::IsClimberUp() {
    return mLiftMotorLimit.Get();
}

bool Climber::IsOtherLimitSwitch() {
    return mLiftMotorLimitOther.Get();
}

int Climber::GetLiftMotorEncoderValue() {
    return mLiftMotorEncoder.GetPosition() - mEncoderOffset;
}

void Climber::ResetEncoder() {
    mEncoderOffset = mLiftMotorEncoder.GetPosition();
}
