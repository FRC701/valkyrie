#pragma once
#include <frc/WPILib.h>
#include "frc/buttons/POVButton.h"

class OI {
private:

	std::shared_ptr<frc::Joystick> driver;
	frc::JoystickButton dA;
  frc::JoystickButton dB;
  frc::JoystickButton dX;
  frc::JoystickButton dY;
  frc::JoystickButton dLB;
  frc::JoystickButton dRB;
  frc::JoystickButton dL3;
  frc::JoystickButton dR3;
  frc::JoystickButton dStart;
  frc::JoystickButton dBack;

	std::shared_ptr<frc::Joystick> coDriver;

	frc::JoystickButton coA;
  frc::JoystickButton coB;
  frc::JoystickButton coX;
  frc::JoystickButton coY;
  frc::JoystickButton coLB;
  frc::JoystickButton coRB;
  frc::JoystickButton coL3;
  frc::JoystickButton coR3;
  frc::JoystickButton coStart;
  frc::JoystickButton coBack;
  frc::POVButton coPOV0;
  frc::POVButton coPOV90;
  frc::POVButton coPOV180;
  frc::POVButton coPOV270;

  frc::Command* mElevatorHatchLevel_0;
  frc::Command* mElevatorHatchLevel_1;
  frc::Command* mElevatorHatchLevel_2;
  frc::Command* mHatchIntakeEngage;

  frc::Command* mElevatorCargoLevel_0;
  frc::Command* mElevatorCargoLevel_1;
  frc::Command* mElevatorCargoLevel_2;
  frc::Command* mScoreCargo;

	static std::shared_ptr<OI> self;

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

	static constexpr int kButtonA_ID { 1 };
  static constexpr int kButtonB_ID { 2 };
  static constexpr int kButtonX_ID { 3 };
  static constexpr int kButtonY_ID { 4 };
  static constexpr int kButtonLB_ID { 5 };
  static constexpr int kButtonRB_ID { 6 };
  static constexpr int kButtonBack_ID { 7 };
  static constexpr int kButtonStart_ID { 8 };
  static constexpr int kButtonL3_ID { 9 };
  static constexpr int kButtonR3_ID { 10 };

  void HatchIntakeControls() { mIsHatch = true; }
  void CargoIntakeControls() { mIsHatch = false; }
  bool isHatch(){ return mIsHatch; }
  private: 
  bool mIsHatch;
};
