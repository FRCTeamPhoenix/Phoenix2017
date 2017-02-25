#include "Robot.h"
#include "Actions/ActionFactory.h"

using namespace std;
using json=nlohmann::json;

void lidarThread(Robot * robot, Lidar * lidar) {
	while(true) {
		if(robot->IsEnabled())
		{
			lidar->run();
		}
	}
}

Robot::Robot() :
    		   m_talons("config/talons_validated.json", "schemas/talons.schema"),
			   m_FRDrive(7, m_talons.getTalonConfig(7), CANTalon::FeedbackDevice::QuadEncoder),
			   m_FLDrive(8, m_talons.getTalonConfig(8), CANTalon::FeedbackDevice::QuadEncoder),
			   m_BRDrive(1, m_talons.getTalonConfig(1), CANTalon::FeedbackDevice::QuadEncoder),
			   m_BLDrive(2, m_talons.getTalonConfig(2), CANTalon::FeedbackDevice::QuadEncoder),
			   m_mainAutoGroup(new ActionGroup()),
			   m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_expansionBoard, HeadingControl::GyroAxes::x),
			   m_topFlyWheelMotor(PortAssign::topFlyWheelMotor, m_talons.getTalonConfig(PortAssign::topFlyWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
			   m_lowerFlyWheelMotor(PortAssign::lowerFlyWheelMotor, m_talons.getTalonConfig(PortAssign::lowerFlyWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
			   m_turretRotateMotor(PortAssign::turret, m_talons.getTalonConfig(PortAssign::turret), CANTalon::FeedbackDevice::QuadEncoder),
			   m_leftLimitSwitch(PortAssign::leftLimitSwitch),
			   m_rightLimitSwitch( PortAssign::rightLimitSwitch),
			   m_joystick(PortAssign::joystick),
			   m_gamepad(PortAssign::gamepad),
			   m_customBox(PortAssign::customBox),
			   m_lidar(PortAssign::lidarTriggerPin, PortAssign::lidarMonitorPin, 0),
			   m_expansionBoard(),
			   m_visionComs(),
			   m_shooterCalibrator(),
			   m_flywheel(m_lowerFlyWheelMotor, m_topFlyWheelMotor, m_shooterCalibrator, m_lidar, m_customBox),
			   m_turret(m_turretRotateMotor,m_visionComs, m_customBox),
			   m_loggerController(),
			   m_configEditor(),
			   m_climberMotor(PortAssign::climber, m_talons.getTalonConfig(PortAssign::climber), CANTalon::FeedbackDevice::QuadEncoder),
			   m_climber(m_climberMotor, m_joystick),
			   m_gathererMotor(PortAssign::loader),
			   m_feederMotor(PortAssign::feeder, m_talons.getTalonConfig(PortAssign::feeder), CANTalon::FeedbackDevice::QuadEncoder),
			   m_indexerMotor(PortAssign::indexer, m_talons.getTalonConfig(PortAssign::indexer), CANTalon::FeedbackDevice::QuadEncoder),
			   m_indexer(m_indexerMotor, m_customBox),
			   m_feeder(m_feederMotor, m_customBox),
			   m_gatherer(m_gathererMotor, m_customBox),
			   m_robotController(m_flywheel,m_turret,m_feeder,m_indexer,m_customBox,m_climber,m_gatherer),
			   m_rlogger(m_topFlyWheelMotor, m_lowerFlyWheelMotor, m_lidar)
{

}

// Print the Message on the Drive Station For Test Mode
void printMSG(string place, string msg) {
	std::ostringstream stream;
	stream << msg;
	SmartDashboard::PutString("DB/String " + place, stream.str());
	stream.clear();
}

void Robot::RobotInit()
{

	CameraServer::GetInstance()->StartAutomaticCapture("Drive Cam", 0);
	CameraServer::GetInstance()->StartAutomaticCapture("Gear Cam", 1);
	CameraServer::GetInstance()->StartAutomaticCapture("Turret Cam", 2);

	cout << "In Robot INIT" << endl;
	initMainActionGroup();
	SmartDashboard::PutStringArray("Test List", testModes);

	std::thread runLidar(lidarThread, this, &m_lidar);
	runLidar.detach();
}

void Robot::Autonomous()
{
	LOGI << "Start Auto";
	initAutoMode();

	while (IsEnabled() && IsAutonomous())
	{
		m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
	}

}

void Robot::OperatorControl()
{
	m_expansionBoard.Reset();
	LOGI << "Start Teleop";

	bool lastPressed3 = false;
	bool lastPressed4 = false;
	switchToTeleoperated();
	while (IsEnabled() && IsOperatorControl())
	{
		m_rlogger.run();
		m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
		m_robotController.run();

		std::ostringstream lidarDistance;
		lidarDistance << "Distance: ";
		lidarDistance << m_lidar.getDistance();
		SmartDashboard::PutString("DB/String 6", lidarDistance.str());

		std::ostringstream topVel;
		topVel << "TopVel: ";
		topVel << m_topFlyWheelMotor.GetEncVel();
		SmartDashboard::PutString("DB/String 7", topVel.str());

		std::ostringstream lowVel;
		lowVel << "LowVel: ";
		lowVel << m_lowerFlyWheelMotor.GetEncVel();
		SmartDashboard::PutString("DB/String 8", lowVel.str());


		SmartDashboard::PutNumber("LidarDistance", m_lidar.getDistance());
		SmartDashboard::PutNumber("ShooterTopVel", m_topFlyWheelMotor.GetEncVel());
		SmartDashboard::PutNumber("ShooterLowVel", m_lowerFlyWheelMotor.GetEncVel());
	}
	m_rlogger.stop();
}

void Robot::Test()
{
	//    m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
	//    m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
	//    m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
	//    m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);
	//
	//    stringstream ss;
	//    ss << m_talons.m_status;
	//    SmartDashboard::PutString("DB/String 7", ss.str());
	//
	//    ss.str("");
	//    ss << m_talons.getTalonConfig(2)["speed"]["p"];
	//    SmartDashboard::PutString("DB/String 8", ss.str());
	m_pidState = PID;
	testModeSelector = t_Talons;
	while (IsEnabled() && IsTest())
	{
		/*
		 * Inside of the Drive Station the Control Mode is where you want to check.
		 * Weather or not you are in PID/VOLTAGE
		 * 1 is VOLTAGE 0 is PID
		 * EXAMPLE:
		 * Control Mode: 0
		 * That is PID
		 * Control Mode: 1
		 * That is Voltage
		 */
		switch(m_pidState) {
		case PID:
			if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
				m_pidState = VOLTAGE;
				break;
			}
			break;
		case VOLTAGE:
			if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
				m_pidState = PID;
				break;
			}
			break;
		}
		// IMPORTANT You have Full Joystick Controll So Be Careful
		float power = m_joystick.GetY();
		if (fabs(power) < 0.05f){
			power = 0.0f;
		}
		else{
			/*
			 * You can get Full Power So BE CAREFUL!
			 * Also if you need to you can set this to a specific value that can be changed at any time.
			 * Just remember that when you change a variable all other functions that use that variable can cause some issues.
			 * Otherwise be safe and have fun!
			 */
			power = m_joystick.GetY();
		}
		// Also you have full throttle controll SO BE CAREFUL!
		float throttle = m_joystick.GetThrottle();

		// updates the state of the Test Mode Selector
		string mode = SmartDashboard::GetString("Test Selector", "none");
		for (int x=t_Talons; x <= t_DriveTrain; x++) {
			if (mode == testModes[x]) {
				testModeSelector = static_cast<TestMode>(x);
			}
		}

		/*
		 * So some of the Test Modes have a way that you can controll them with a
		 * Throttle on the Joystick. The way that you can do that is by pressing
		 * Button Y and also moving the throttle at the same time.
		 * Otherwise it won't work. Also some of the Talons can be moved with a
		 * joystick on the gamepad so look for that...
		 */
		switch(testModeSelector)
		{
		case t_Talons: //Test all Talons on robot
		{
			printMSG("0", "All Talons");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "FRD ENC: " + std::to_string(m_FRDrive.GetEncPosition()));
			printMSG("3", "FLD ENC: " + std::to_string(m_FLDrive.GetEncPosition()));
			printMSG("4", "BRD ENC: " + std::to_string(m_BRDrive.GetEncPosition()));
			printMSG("5", "BLD ENC: " + std::to_string(m_BLDrive.GetEncPosition()));
			printMSG("6", "RFW ENC: " + std::to_string(m_lowerFlyWheelMotor.GetEncPosition()));
			printMSG("7", "LFW ENC: " + std::to_string(m_topFlyWheelMotor.GetEncPosition()));
			printMSG("8", "TRM ENC: " + std::to_string(m_turretRotateMotor.GetEncPosition()));
			m_FRDrive.goAt(power);
			m_FLDrive.goAt(power);
			m_BRDrive.goAt(power);
			m_BLDrive.goAt(power);
			m_lowerFlyWheelMotor.goAt(power);
			m_topFlyWheelMotor.goAt(power);
			m_turretRotateMotor.goAt(power);
			break;
		}

		case t_ShooterHead: //Test Shooter Head
		{
			printMSG("0", "Shooter Testing Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "RFW ENC: " + std::to_string(m_lowerFlyWheelMotor.GetEncPosition()));
			printMSG("3", "LFW ENC: " + std::to_string(m_topFlyWheelMotor.GetEncPosition()));
			printMSG("4", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("5", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
			if (m_pidState == PID) {
				m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
				m_topFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
				m_lowerFlyWheelMotor.goAt(power);
				m_topFlyWheelMotor.goAt(power);
			}
			else {
				m_lowerFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_topFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_lowerFlyWheelMotor.Set(power);
				m_topFlyWheelMotor.Set(power);
			}
			break;
		}

		case t_Feeder: //Test Feeder
		{
			// Feeder Can be controlled with Throttle as well look bellow for more info
			printMSG("0", "Feeder Testing Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "Feeder ENC: " + std::to_string(m_feederMotor.GetEncPosition()));
			printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
			if (m_pidState == PID) {
				m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
				// Feeder Can be controlled with buttonY and also Throttle
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_feederMotor.goAt(throttle);
				}
				else {
					m_feederMotor.goAt(power);
				}
			}
			else if (m_pidState == VOLTAGE){
				m_feederMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_feederMotor.Set(throttle);
				}
				else {
					m_feederMotor.Set(power);
				}
			}
			break;
		}

		case t_Indexer: //Test Indexer
		{
			printMSG("0", "Indexer Testing Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "Indexer ENC: " + std::to_string(m_indexerMotor.GetEncPosition()));
			printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));

			if (m_pidState == PID) {
				m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_indexerMotor.goAt(throttle);
				}
				else {
					m_indexerMotor.goAt(power);
				}
			}
			else if (m_pidState == VOLTAGE){
				m_indexerMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_feederMotor.Set(throttle);
				}
				else {
					m_feederMotor.Set(power);
				}
			}
			break;
		}

		case t_Gatherer: //Test Gather
		{
			printMSG("0", "Gather Testing Mode");
			printMSG("1", "Gatherer Speed: " + std::to_string(m_gathererMotor.GetSpeed()));
			printMSG("2", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("3", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
			m_gathererMotor.Set(power);
			break;
		}

		case t_Turret: //Test Turret
		{
			printMSG("0", "Turret Testing Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "Turret ENC: " + std::to_string(m_turretRotateMotor.GetEncPosition()));
			printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
			if (m_pidState == PID) {
				m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_turretRotateMotor.goAt(throttle);
				}
				else {
					m_turretRotateMotor.goAt(power);
				}
			}
			else {
				m_turretRotateMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
					m_turretRotateMotor.Set(throttle);
				}
				else {
					m_turretRotateMotor.Set(power);
				}
			}
			break;
		}

		case t_Climber: //Test Climber
		{
			printMSG("0", "Climber Testing Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "Climber ENCVEL: " + std::to_string(m_climberMotor.GetEncVel()));
			printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
			printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
			if (m_pidState == PID) {
				m_climberMotor.SetControlMode(CANSpeedController::kSpeed);
				m_climberMotor.goAt(power);
			}
			else if (m_pidState == VOLTAGE){
				m_climberMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_climberMotor.Set(power);
			}
			break;
		}

		/*
		 * Test Mode
		 * Button X Moves Feeder
		 * Button Y Moves the Indexer
		 * Button A Moves the FlyWheels
		 */
		case t_Shooter: //Test all Shooter Components
		{
			m_rlogger.run();
			printMSG("0", "All Shooter Test Mode");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "FeedVEL: " + std::to_string(m_feederMotor.GetEncVel()));
			printMSG("2", "IndxVEL: " + std::to_string(m_indexerMotor.GetEncVel()));
			printMSG("6", "VelLow: " + std::to_string(m_lowerFlyWheelMotor.GetEncVel()));
			printMSG("7", "VelTop: " + std::to_string(m_topFlyWheelMotor.GetEncVel()));
			printMSG("8", "LidarDistance: " + std::to_string(m_lidar.getDistance()));

			if (m_pidState == PID) {
				m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
				m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
				m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
				m_topFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
			}

			else if (m_pidState == VOLTAGE) {
				m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
				m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
				m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
				m_topFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
			}

			// Feeder Motor
			// Slider 1

			if ((m_pidState == VOLTAGE) && m_gamepad.GetRawButton(DriveStationConstants::buttonX)){
				m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0",0.0));
			}
			else if ((m_pidState == VOLTAGE))
			{
				m_feederMotor.Set(power / 2);
			}
			else if ((m_pidState == PID) && m_gamepad.GetRawButton(DriveStationConstants::buttonX)){
				m_feederMotor.goAt(SmartDashboard::GetNumber("DB/Slider 0",0.0));
			}
			else if ((m_pidState == PID)) {
				m_feederMotor.goAt(power / 2);
			}

			//indexer test
			// Slider 2

			if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonY))){
				m_indexerMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1",0.0));
			}
			if ((m_pidState == VOLTAGE) && (m_gamepad.GetRawButton(DriveStationConstants::buttonY))){
				m_indexerMotor.Set(SmartDashboard::GetNumber("DB/Slider 1",0.0));
			}
			else if ((m_pidState == PID)) {
				m_indexerMotor.goAt(power);
			}
			else if (m_pidState == VOLTAGE) {
				m_indexerMotor.Set(power);
			}

			// Fly wheel Test
			// Slider 3 for lowerflywheel
			// Slider 4 for topflywheel
			if ((m_pidState == VOLTAGE) && (m_gamepad.GetRawButton(DriveStationConstants::buttonA))){
				m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2",0.0));
				m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 3",0.0));
			}
			else if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonA))){
				m_lowerFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2",0.0));
				m_topFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 3",0.0));
			}
			m_configEditor.update();
			break;
		}

		case t_DriveTrain: //Test all 4 Drive Train Motors
		{
			printMSG("0", "Drive Train Motors Test");
			printMSG("1", "Control Mode: " + std::to_string(m_pidState));
			printMSG("2", "FRD ENC: " + std::to_string(m_FRDrive.GetEncPosition()));
			printMSG("3", "FLD ENC: " + std::to_string(m_FLDrive.GetEncPosition()));
			printMSG("4", "BRD ENC: " + std::to_string(m_BRDrive.GetEncPosition()));
			printMSG("5", "BLD ENC: " + std::to_string(m_BLDrive.GetEncPosition()));
			if (m_pidState == PID) {
				m_FRDrive.SetControlMode(CANSpeedController::kSpeed);
				m_FLDrive.SetControlMode(CANSpeedController::kSpeed);
				m_BRDrive.SetControlMode(CANSpeedController::kSpeed);
				m_BLDrive.SetControlMode(CANSpeedController::kSpeed);
				m_FRDrive.goAt(power);
				m_FLDrive.goAt(power);
				m_BRDrive.goAt(power);
				m_BLDrive.goAt(power);
			}
			if (m_pidState == VOLTAGE) {
				m_FRDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_FLDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_BRDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_BLDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
				m_FRDrive.Set(power);
				m_FLDrive.Set(power);
				m_BRDrive.Set(power);
				m_BLDrive.Set(power);
			}
			break;
		}
		}
	}
	m_rlogger.stop();
}

void Robot::initMainActionGroup ()
{
	json myJsonDoc;
	json mySchemaDoc;

	try
	{

		if (!valijson::utils::loadDocument ("/home/lvuser/schemas/actions.schema",
				mySchemaDoc))
		{
			cout << "Schema Failed Loading" << endl;

			throw std::runtime_error ("Failed to load schema document");
		}

		Schema mySchema;
		SchemaParser parser;
		NlohmannJsonAdapter mySchemaAdapter (mySchemaDoc);
		parser.populateSchema (mySchemaAdapter, mySchema);

		if (!valijson::utils::loadDocument ("/home/lvuser/config/actions.json",
				myJsonDoc))
		{
			cout << "Json Failed Loading" << endl;

			throw std::runtime_error ("Failed to load Json document");
		}

		Validator validator;
		NlohmannJsonAdapter myTargetAdapter (myJsonDoc);
		if (!validator.validate (mySchema, myTargetAdapter, NULL))
		{
			cout << "Validation Failed" << endl;

			throw std::runtime_error ("Validation failed.");
		}
		else
		{
			cout << "Validated" << endl;
		}

		m_mainAutoGroup->initActionGroup (myJsonDoc, shared_ptr<Robot>(this));

	}
	catch(runtime_error runtime){
		cout << runtime.what () << endl;

		vector<string> failureMessage = {"NO VALID ACTION JSON FOUND"};
		SmartDashboard::PutStringArray ("Auto List", failureMessage);
		return;
	}

	vector<string> topGroupNames;

	vector<shared_ptr<Action>> allActions = m_mainAutoGroup->getContainedActions ();

	vector<shared_ptr<Action>>::iterator actionIterator;
	for (actionIterator = allActions.begin (); actionIterator != allActions.end (); actionIterator++)
	{
		string name = actionIterator->get ()->getName ();
		if (name.find ("Auto") != string::npos)
		{
			topGroupNames.push_back (name);
		}
	}
	SmartDashboard::PutStringArray ("Auto List", topGroupNames);

}

void Robot::initAutoMode ()
{
	string mode = SmartDashboard::GetString ("Auto Selector", "None");

	vector<shared_ptr<Action>> allActions = m_mainAutoGroup->getContainedActions ();

	SmartDashboard::PutString("DB/String 6", mode);

	vector<shared_ptr<Action>>::iterator actionIterator;
	for(actionIterator = allActions.begin(); actionIterator != allActions.end(); actionIterator++)
	{
		if(actionIterator->get ()->getName () == mode)
		{
			SmartDashboard::PutString("DB/String 7","auto init");
			actionIterator->get ()->reset ();
		}
		else
		{
			actionIterator->get ()->disable ();
		}
	}

}

void Robot::switchToTeleoperated()
{
	vector<shared_ptr<Action>> allActions = m_mainAutoGroup->getContainedActions ();
	vector<shared_ptr<Action>>::iterator actionIterator;
	for(actionIterator = allActions.begin(); actionIterator != allActions.end(); actionIterator++)
	{
		string name = actionIterator->get ()->getName ();

		if ("Teleoperated" == name)
		{
			actionIterator->get ()->reset ();
			cout << "teleop init" <<endl;
		}
		else
		{
			actionIterator->get ()->disable ();
		}
	}
}

void Robot::driveAt(double speed, double angle)
{
	m_drivetrain.moveAt (speed, angle);
}

void Robot::driveDistance (double distance, double angle, double speed)
{
	m_drivetrain.moveDistance (distance, angle, speed);
}

void Robot::rotateAngle (double angle, double speed)
{
	m_drivetrain.moveDistance (0, 0, speed, angle);
}

bool Robot::doneDriveMove (double tolerance)
{
	return m_drivetrain.doneMove (tolerance);
}

void Robot::driveJoystick()
{
	double FB = -m_joystick.GetY();

	double LF = m_joystick.GetX();
	double rot = m_joystick.GetZ() / 2;

	FB = (fabs(FB) < 0.1) ? 0 : ((FB < 0) ? (FB + 0.1) / (0.9 / 0.75) : (FB - 0.1) / 0.9);
	LF = (fabs(LF) < 0.1) ? 0 : ((LF < 0) ? (LF + 0.1) / (0.9 / 1): (LF - 0.1) / 0.9);
	rot = (fabs(rot) < 0.1) ? 0 : ((rot < 0) ? (rot + 0.1) / (0.9 / 1) : (rot - 0.1) / 0.9);

	double throttle = (((-m_joystick.GetThrottle() + 1) / 2));
	if(throttle < 0.2)
	{
		throttle = 0.2;
	}
	if(throttle > 0.8)
	{
		throttle = 0.8;
	}

	FB *= throttle;
	LF *= throttle;
	rot *= throttle;

	if(m_joystick.GetRawButton(12))
	{
		m_drivetrain.moveRelative(LF, -FB / 2, rot / 2);
	}
	else
	{
		m_drivetrain.moveRelative(FB, LF, rot);
	}
}

void Robot::setIndexerSpeed(double speed)
{
	m_indexer.setSpeed(speed);
}

START_ROBOT_CLASS(Robot)
