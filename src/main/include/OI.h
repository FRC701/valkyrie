#pragma once
#include <frc/WPILib.h>

class OI {
private:

  static std::shared_ptr<OI> self;
	std::shared_ptr<frc::Joystick> coDriver;
	std::shared_ptr<frc::Joystick> driver;
public:

	double getDriverLeftXAxis() const;
	double getDriverLeftYAxis() const;
	double getDriverRightXAxis() const;
	double getDriverRightYAxis() const;

	double getCoDriverLeftXAxis() const;
	double getCoDriverLeftYAxis() const;
	double getCoDriverRightXAxis() const;
	double getCoDriverRightYAxis() const;

  static std::shared_ptr<OI> getInstance();
	std::shared_ptr<frc::Joystick> getdriver();
	std::shared_ptr<frc::Joystick> getcoDriver();
	OI();

	static const int kLeftXAxis_ID = 0;
	static const int kLeftYAxis_ID = 1;
	static const int kRightXAxis_ID = 4;
	static const int kRightYAxis_ID = 5;

};
