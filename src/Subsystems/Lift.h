// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "../Commands/ResetLift.h"
#ifndef LIFT_H
#define LIFT_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <array>

/**
 *
 *
 * @author ExampleAuthor
 */
class Lift: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SpeedController* speedController1;
	Encoder* encoder;
	DigitalInput* limitSwitch;
	DoubleSolenoid* gearboxShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	PIDController* pidController;
	Lift(Command* resetLift);
	void InitDefaultCommand();
	static void LowerSwitchTriggered();
	static void HigherLimitSwitchTriggered();
	double highEncoderValue;
	void toggleGear();
	double lastLiftShiftTime;
	std::array<int,5> hookPositions = {{-221,44,662,1338,2047}};
	int currentHookIndex;
	float p = 0.01;
	float i = 0.00005;
	float d = 0.0001;
	int getCurrentPosition();
	int previousPosition();
	int nextPosition();
	void indexUp();
	void indexDown();
};
void LiftInterupt(uint32_t x, void *param);
#endif
