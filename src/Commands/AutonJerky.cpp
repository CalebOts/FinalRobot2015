// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "AutonJerky.h"
#include "DriveForward.h"
#include "GatherCans.h"

AutonJerky::AutonJerky() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void AutonJerky::Initialize() {
	startTime = Timer::GetFPGATimestamp();
	durationTime = 10;
//	DriveForward::Command::Cancel();
}

// Called repeatedly when this Command is scheduled to run
void AutonJerky::Execute() {
//	Robot::drivetrain->DriveOnHeading(.85, fabs(SmartDashboard::GetNumber("AutonJerkyCorrectionConstant")));	//TODO: put on smart dashboard
	//SmartDashboard::GetNumber();
}

// Make this return true when this Command no longer needs to run execute()
bool AutonJerky::IsFinished() {
	return startTime + durationTime < Timer::GetFPGATimestamp();
}

// Called once after isFinished returns true
void AutonJerky::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonJerky::Interrupted() {

}
