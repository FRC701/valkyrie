/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "subsystems/Climber.h"

class MotorClimb : public frc::Command {
 public:
  MotorClimb(double speed, double encoderFinish);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

protected:
  std::shared_ptr<Climber> mClimber;

private:
  double mSpeed;
  double mEncoderFinish;
};
