#pragma once

#include "frc/commands/Command.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TankDrive: public frc::Command {
public:
	TankDrive();

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
};
