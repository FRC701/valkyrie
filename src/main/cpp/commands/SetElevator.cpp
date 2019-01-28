#include "commands/SetElevator.h"
#include "subsystems/Elevator.h"

SetElevator::SetElevator(double speed): mSpeed(speed) {
        // Use Requires() here to declare subsystem dependencies
        // eg. Requires(Robot::chassis.get());
        Requires(Elevator::getInstance().get());
}

// Called just before this command runs the first time
void SetElevator::Initialize() {

}

// Called repeatedly when this command is schduled to run
void SetElevator::Execute() {
        Elevator::getInstance()->SetElevator(mSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool SetElevator::IsFinished() {
    return Elevator::getInstance()->IsRevLimitSwitchClosed();
}
// Called once after isFinished returns true
void SetElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is schduled to run
void SetElevator::Interrupted() { 

}