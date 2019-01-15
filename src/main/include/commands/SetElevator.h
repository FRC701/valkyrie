#pragma once
#include <frc/commands/Command.h>

class SetElevator : public frc::Command{
public:
        SetElevator(double speed);
        void Initialize();
        void Execute();
        bool IsFinished();
        void End();
        void Interrupted();
private:
        double mSpeed;
};

// SetElevator_H