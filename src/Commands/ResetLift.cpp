// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ResetLift.h"

ResetLift::ResetLift() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::lift);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	isFinished = false;
}

// Called just before this Command runs the first time
void ResetLift::Initialize() {
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void ResetLift::Execute() {
	if(RobotBase::getInstance().IsAutonomous()){
	Robot::lift->pidController->Disable();
	Robot::lift->gearboxShifter->Set(DoubleSolenoid::kReverse);
	Robot::lift->speedController1->Set(-1);
	Robot::lift->currentHookIndex = 0;
	}
	else
		Robot::lift->pidController->Enable();
		Robot::lift->pidController->SetSetpoint(-287);
		Robot::lift->currentHookIndex = 0;
}

// Make this return true when this Command no longer needs to run execute()
bool ResetLift::IsFinished() {
	if(Robot::RobotBase::getInstance().IsAutonomous()){
		isFinished = Robot::lift->limitSwitch->Get();
	}
	return 	isFinished;
}

// Called once after isFinished returns true
void ResetLift::End() {
	Robot::lift->speedController1->Set(0);
	if(Robot::RobotBase::getInstance().IsAutonomous()){
		Robot::lift->encoder->Reset();
		isFinished = false;
	}
//	Robot::lift->gearboxShifter->Set(DoubleSolenoid::kForward);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetLift::Interrupted() {

}
