#include "commands/TankDrive.h"
#include "subsystems/Chassis.h"
#include "OI.h"

TankDrive::TankDrive(): frc::Command() {
  Requires(Chassis::getInstance().get());
}

void TankDrive::Initialize() {
  //Chassis::getInstance()->SetupDrive();
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
  std::shared_ptr<Chassis> chassis = Chassis::getInstance();
  std::shared_ptr<OI> oi = OI::getInstance();

  double left = oi->getDriverLeftYAxis();
  double right = oi->getDriverRightYAxis();

  chassis->SetTankDrive(left,right);
}

bool TankDrive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void TankDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {

}
