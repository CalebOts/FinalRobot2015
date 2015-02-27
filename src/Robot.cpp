// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Timer.h"
#include "Diagnostics.h"
#include "xbox.h"
#include "Commands/AutonCalibration.h"
#include "Commands/RunLift.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
EagleWings* Robot::eagleWings = 0;
Drivetrain* Robot::drivetrain = 0;
Lift* Robot::lift = 0;
StepDetectorator* Robot::stepDetectorator = 0;
Compresoratoror* Robot::compresoratoror = 0;
OI* Robot::oi = 0;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::startDiagnosticLogging() {
	//starts logging and prints headers
	startLogging();
	///print header for log
	bufferPrintf("Gyro, Acc X, Acc Y\n");
}
void Robot::logRow() {
	bufferPrintf("%f, %f, %f\n",RobotMap::drivetraindriveGyro->GetAngle(),
			stepDetectorator->accelerometer->GetX(), stepDetectorator->accelerometer->GetY());
	printf("Acc x: %f Acc y: %f", stepDetectorator->accelerometer->GetX(), stepDetectorator->accelerometer->GetY());
	DashboardPrintf("Acc x:","%f",stepDetectorator->accelerometer->GetX());
	DashboardPrintf("Acc x:","%f",drivetrain->driveGyro->GetAngle());

}
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	eagleWings = new EagleWings();
	drivetrain = new Drivetrain();
	lift = new Lift(new ResetLift());
	stepDetectorator = new StepDetectorator();
	compresoratoror = new Compresoratoror();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
//	CameraServer::GetInstance()->SetQuality(50);
//	CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new GatherCans();
	autonCalibration = new AutonCalibration();
	alignWithStep = new AlignWithStep();
	backupToAutonZone = new BackupToAutonZone();
	driveForward = new DriveForward();
	gatherCans = new GatherCans();
	lowerOneTote = new LowerOneTote();
	raiseOneTote = new RaiseOneTote();
	raiseWings = new RaiseWings();
	retractWings = new RetractWings();
	rotateWingsForward = new RotateWings(.2,.5);
	rotateWingsBackward = new RotateWings(-.2,.5);
	driverStick = new Joystick(0);
	techStick = new Joystick(1);
	raiseLift = new RunLift(0.5);
	lowerLift = new RunLift(-0.5);
	stopLift = new RunLift(0);
	push = new APusH();
	gearUp = new ShiftToHighGear();
	gearDown = new ShiftToLowGear();
	pull = new UnAPusH();
	resetLift = new ResetLift();
	pidLift = new PIDLift();
	//TODO: add code to ensure gyroscope has initialized
	RobotMap::drivetraindriveGyro->InitGyro();	//probably takes 10 seconds
	startDiagnosticLogging();
}
void Robot::DisabledInit(){
	flushToDisk();
}
void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
//	if(RobotMap::liftlimitSwitch->Get()) {
//		printf("Start Auton Calibration\n");
//		autonCalibration->SetRunWhenDisabled(true);
//		autonCalibration->Start();
//	}

}
void Robot::AutonomousInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	logRow();
}

void Robot::TeleopInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
	//TODO: put this in a reset method that is shared with autoninit
	RobotMap::drivetraindriveGyro->Reset();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
//	printf("Teleop\n");
//	printf("liftencoder %f", Robot::lift->encoder->GetDistance());
	logRow();
	//liftcode
	DashboardPrintf("encoder ", "%f", lift->encoder->GetDistance());
	DashboardPrintf("high value ", "%f", lift->highEncoderValue);
	RobotMap::drivetrainrobotDrive->MecanumDrive_Cartesian(Robot::driverStick->GetX()*0.5, Robot::driverStick->GetY()*0.5,Robot::driverStick->GetRawAxis(4)*0.5);
	if(driverStick->GetRawButton(XBOX::LBUMPER) || techStick->GetRawButton(XBOX::LBUMPER)) {
		lowerOneTote->Start();
	}

	if(driverStick->GetRawButton(XBOX::RBUMPER) || techStick->GetRawButton(XBOX::RBUMPER)) {
		raiseOneTote->Start();
	}

	if(driverStick->GetRawAxis(RIGHT_TRIGGER) > .5 || techStick->GetRawAxis(RIGHT_TRIGGER) > .5) {
		raiseLift->Start();
	}else if(driverStick->GetRawAxis(LEFT_TRIGGER) > .5 || techStick->GetRawAxis(LEFT_TRIGGER) > .5) {
		lowerLift->Start();
	}else {
		raiseLift->Cancel();
		lowerLift->Cancel();
	}

	if(techStick->GetRawButton(XBOX::START)){
		rotateWingsForward->Start();
	}else {
		rotateWingsForward->Cancel();
	}

	if(techStick->GetRawButton(XBOX::BACK)){
		rotateWingsBackward->Start();
	}else {
		rotateWingsBackward->Cancel();
	}

	if(techStick->GetRawButton(XBOX::XBUTTON)){
		eagleWings->leftWinch->Set(.4);
	}else {
		eagleWings->leftWinch->Set(0);
	}

	if(techStick->GetRawButton(XBOX::BBUTTON)){
		eagleWings->rightWinch->Set(.4);
	}else {
		eagleWings->rightWinch->Set(0);
	}

	if(driverStick->GetRawButton(XBOX::ABUTTON) || techStick->GetRawButton(XBOX::YBUTTON)) {
		Robot::resetLift->Start(); //starts the command that catches the limit switch
	}

	if(techStick->GetRawButton(XBOX::ABUTTON) || driverStick->GetRawButton(XBOX::YBUTTON)){
		gearToggle = gearToggle * -1;
	}
	if(gearToggle == 1){
		Robot::gearUp->Start();
		Robot::gearDown->Cancel();
	}
	else{
		Robot::gearDown->Start();
		Robot::gearUp->Cancel();
	}

	if(techStick->GetRawButton(XBOX::LSTICKP)){
		pushToggle = pushToggle * -1;
	}
	if(pushToggle == 1){
		Robot::push->Start();
		Robot::pull->Cancel();
	}
	else{
		Robot::pull->Start();
		Robot::push->Cancel();
	}
	if(driverStick->GetRawButton(XBOX::XBUTTON)){
		lowerLift->Start();
	}
//	if(techStick->GetRawButton(XBOX::LSTICKP)){
//		camNumber = camNumber == 1 ? 0 : 1;
//		CameraServer::GetInstance()->StartAutomaticCapture("cam"+camNumber);
//	}

}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
