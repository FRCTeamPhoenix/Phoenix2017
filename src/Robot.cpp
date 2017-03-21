#include "Robot.h"
#include "Actions/ActionFactory.h"
#include "Indexer.h"

using namespace std;
using json=nlohmann::json;

void lidarThread(Robot * robot, Lidar * lidar) {
    while(true) {
//        if(robot->IsEnabled())
//        {
            lidar->run();
//        }
    }
}

Robot::Robot() :
        m_talons("config/talons_validated.json", "schemas/talons.schema"),
        m_FRDrive(PortAssign::frontRightWheelMotor, m_talons.getTalonConfig(PortAssign::frontRightWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
        m_FLDrive(PortAssign::frontLeftWheelMotor, m_talons.getTalonConfig(PortAssign::frontLeftWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
        m_BRDrive(PortAssign::backRightWheelMotor, m_talons.getTalonConfig(PortAssign::backRightWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
        m_BLDrive(PortAssign::backLeftWheelMotor, m_talons.getTalonConfig(PortAssign::backLeftWheelMotor), CANTalon::FeedbackDevice::QuadEncoder),
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
        m_robotController(m_flywheel,m_turret,m_feeder,m_indexer,m_customBox,m_climber,m_gatherer)
{

}

// Print the Message on the Drive Station For Test Mode
void printMSG(string place, string msg) {
    std::ostringstream stream;
    stream << msg;
    SmartDashboard::PutString("DB/String " + place, stream.str());
    stream.clear();
}

void Robot::VisionThread()
{
    static cs::UsbCamera cam0 = cs::UsbCamera("Gear Cam", 0);
    cam0.SetResolution(320,240);
    cam0.SetFPS(15);
    static cs::UsbCamera cam1 = cs::UsbCamera("Drive Cam", 1);
    cam1.SetResolution(320,240);
    cam1.SetFPS(15);
    static cs::UsbCamera cam2 = cs::UsbCamera("Turret Cam", 2);
    cam2.SetResolution(320,240);
    cam2.SetFPS(15);
    cv::Mat source(320, 240, CV_32FC3);
    cs::CvSink cvSink0 = CameraServer::GetInstance()->GetVideo(cam0);
    cs::CvSink cvSink1 = CameraServer::GetInstance()->GetVideo(cam1);
    cs::CvSink cvSink2 = CameraServer::GetInstance()->GetVideo(cam2);
    cs::CvSource cvSource = CameraServer::GetInstance()->PutVideo("Current View", 320,240);
    while(true){
        int frameRate = SmartDashboard::GetNumber("Frame Rate", 15);
        int camNum = SmartDashboard::GetNumber("Camera Select",1);
        if(camNum == 0){
            cvSink1.SetEnabled(false);
            cvSink2.SetEnabled(false);
            cvSink0.SetEnabled(true);
            cvSink0.GrabFrame(source);
        }
        else if(camNum == 1)
        {
            cvSink0.SetEnabled(false);
            cvSink2.SetEnabled(false);
            cvSink1.SetEnabled(true);
            cvSink1.GrabFrame(source);
        }
        else
        {
            cvSink0.SetEnabled(false);
            cvSink1.SetEnabled(false);
            cvSink2.SetEnabled(true);
            cvSink2.GrabFrame(source);
        }
        cvSource.SetFPS(frameRate);
        cvSource.PutFrame(source);
        Wait(1/frameRate);
    }
}

void Robot::RobotInit()
{
	cout << "In Robot INIT" << endl;
	initMainActionGroup();
	SmartDashboard::PutStringArray("Test List", testModes);

	m_indexer.initSpeedGroup(shared_ptr<Robot>(this));

    std::thread runLidar(lidarThread, this, &m_lidar);
    runLidar.detach();

    std::thread runVision(VisionThread);
    runVision.detach();
}

void Robot::Autonomous()
{
	LOGI << "Start Auto";
	initAutoMode();

	m_robotController.setState(RobotController::AUTO);
	while (IsEnabled() && IsAutonomous())
	{
            m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
            m_robotController.run();

	}
	m_robotController.setState(RobotController::TELEOP);

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

        m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
        m_robotController.run();

        std::ostringstream lidarDistance;
        lidarDistance << "Distance: ";
        lidarDistance << m_lidar.getDistance();
        SmartDashboard::PutString("DB/String 3", lidarDistance.str());

        std::ostringstream topVel;
        topVel << "TopVel: ";
        topVel << m_topFlyWheelMotor.GetEncVel();
        SmartDashboard::PutString("DB/String 4", topVel.str());

        std::ostringstream lowVel;
        lowVel << "LowVel: ";
        lowVel << m_lowerFlyWheelMotor.GetEncVel();
        SmartDashboard::PutString("DB/String 5", lowVel.str());


		SmartDashboard::PutNumber("LidarDistance", m_lidar.getDistance());
        SmartDashboard::PutNumber("ShooterTopVel", m_topFlyWheelMotor.GetEncVel());
        SmartDashboard::PutNumber("ShooterLowVel", m_lowerFlyWheelMotor.GetEncVel());



	}
}

void Robot::Test()
{
    stringstream ss;
    ss << m_talons.m_status;
    SmartDashboard::PutString("DB/String 7", ss.str());

    ss.str("");
    ss << m_talons.getTalonConfig(2)["speed"]["p"];
    SmartDashboard::PutString("DB/String 8", ss.str());

    LOGI << "Start Test Mode";
    m_pidState = VOLTAGE;
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
        switch (m_pidState)
        {
        case PID:
            if (m_joystick.GetRawButton(12))
            {
                m_pidState = VOLTAGE;
                break;
            }
            break;
        case VOLTAGE:
            if (m_joystick.GetRawButton(11))
            {
                m_pidState = PID;
                break;
            }
            break;
        }
        // IMPORTANT You have Full Joystick Controll So Be Careful
        float power = m_joystick.GetY();
        if (fabs(power) < 0.05f)
        {
            power = 0.0f;
        }
        else
        {
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

        // updates the state of the TALONS as PID or VOLTAGE
        string mode = SmartDashboard::GetString("Test Selector", "none");
        for (int x = t_Talons; x <= t_DriveTrain; x++)
        {
            if (mode == testModes[x])
            {
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
        switch (testModeSelector)
        //switch(testModes)
        {
        case t_Talons: //Test all Talons on robot
        {
            if(m_gamepad.GetRawButton(DriveStationConstants::buttonY))
            {
                printMSG("0", "FRD ENC: " + (m_FRDrive.testStr(0.25)));
                printMSG("1", "FLD ENC: " + (m_FLDrive.testStr(0.25)));
                printMSG("2", "BRD ENC: " + (m_BRDrive.testStr(0.25)));
                printMSG("3", "BLD ENC: " + (m_BLDrive.testStr(0.25)));
                printMSG("4", "RFW ENC: " + (m_lowerFlyWheelMotor.testStr(0.25)));
                printMSG("5", "LFW ENC: " + (m_topFlyWheelMotor.testStr(0.25)));
                printMSG("6", "TRM ENC: " + (m_turretRotateMotor.testStr(0.1, 0.25)));
                printMSG("7", "FED ENC: " + (m_feederMotor.testStr(0.25)));
                printMSG("8", "IDX ENC: " + (m_indexerMotor.testStr(0.25)));
            }

//            m_turretRotateMotor.goAt(power);
            break;
        }

        case t_ShooterHead: //Test Shooter Head
        {
            printMSG("0", "Shooter Testing Mode");
            printMSG("1", "Control Mode: " + std::to_string(m_pidState));
            printMSG("2", "RFW ENC: " + std::to_string(m_lowerFlyWheelMotor.GetEncPosition()));
            printMSG("3", "LFW ENC: " + std::to_string(m_topFlyWheelMotor.GetEncPosition()));
            printMSG("4", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("5", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
            if (m_pidState == PID)
            {
                m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                m_topFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                m_lowerFlyWheelMotor.goAt(power);
                m_topFlyWheelMotor.goAt(power);
            }
            else
            {
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
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
            if (m_pidState == PID)
            {
                m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
                // Feeder Can be controlled with buttonY and also Throttle
                if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                {
                    m_feederMotor.goAt(throttle);
                }
                else
                {
                    m_feederMotor.goAt(power);
                }
            }
            else if (m_pidState == VOLTAGE)
            {
                m_feederMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                {
                    m_feederMotor.Set(throttle);
                }
                else
                {
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
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));

            if (m_pidState == PID)
            {
                m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
                if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                {

                    m_indexerMotor.goAt(throttle);
                }
                else
                {
                    m_indexerMotor.goAt(power);
                }
            }
            else if (m_pidState == VOLTAGE)
            {
                m_indexerMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                {
                    m_indexerMotor.Set(throttle);
                }
                else
                {
                    m_indexerMotor.Set(power);
                }
            }
            break;
        }

        case t_Gatherer: //Test Gather
        {
            printMSG("0", "Gather Testing Mode");
            printMSG("1", "Gatherer Speed: " + std::to_string(m_gathererMotor.GetSpeed()));
            printMSG("2", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("3", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
            m_gathererMotor.Set(power);
            break;
        }

        case t_Turret: //Test Turret
        {
            printMSG("0", "Turret Testing Mode");
            printMSG("1", "Control Mode: " + std::to_string(m_pidState));
            printMSG("2", "Turret ENC: " + std::to_string(m_turretRotateMotor.GetEncPosition()));
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
            if (m_pidState == PID)
            {
                m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
                m_turretRotateMotor.goDistance(power * 200, 0.5);

            }
            else
            {
                m_turretRotateMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                {
                    m_turretRotateMotor.Set(throttle);
                }
                else
                {
                    m_turretRotateMotor.Set(power);
                }
            }
            break;
        }

        case t_Climber: //Test Climber
        {
            printMSG("0", "Climber Testing Mode");
            printMSG("1", "Control Mode: " + std::to_string(m_pidState));
            printMSG("2", "Climber ENC: " + std::to_string(m_climberMotor.GetEncPosition()));
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getDistance()));
            printMSG("4", "Gyro Angle: " + std::to_string(m_expansionBoard.GetAngleX()));
            if (m_pidState == PID)
            {
                m_climberMotor.SetControlMode(CANSpeedController::kSpeed);
                m_climberMotor.goAt(power);
            }
            else if (m_pidState == VOLTAGE)
            {
                m_climberMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                m_climberMotor.Set(power);
            }
            break;
        }

        case t_Shooter: //Test all Shooter Components
        {

            /* for shooter calibration, flywheels is left bumper, feeder is x, indexer is y*/
            printMSG("0", "All Shooter Test Mode");
            printMSG("1", "Control Mode: " + std::to_string(m_pidState));
            printMSG("4", "EncoderShR: " + std::to_string(m_lowerFlyWheelMotor.GetEncPosition()));
            printMSG("5", "EncoderShL: " + std::to_string(m_topFlyWheelMotor.GetEncPosition()));
//            printMSG("6", "EncoderF: " + std::to_string(m_feederMotor.GetEncPosition()));
//            printMSG("7", "Throttle: " + std::to_string(((throttle - 1) / 2)));
//            printMSG("8", "EncoderI: " + std::to_string(m_feederMotor.GetEncPosition()));
            printMSG("9", "Distance: " + std::to_string(m_lidar.getDistance()));

            printMSG("6", "VelLow: " + std::to_string(m_lowerFlyWheelMotor.GetEncVel()));
            printMSG("7", "VelTop: " + std::to_string(m_topFlyWheelMotor.GetEncVel()));
            printMSG("8", "LidarDistance: " + std::to_string(m_lidar.getDistance()));

            if ((m_pidState == VOLTAGE) && m_gamepad.GetRawButton(DriveStationConstants::buttonX))
            {
                m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
                m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
            }
            else if ((m_pidState == VOLTAGE))
            {
                m_feederMotor.Set((throttle - 1) / 2);
            }
            else if ((m_pidState == PID) && m_gamepad.GetRawButton(DriveStationConstants::buttonX))
            {
                m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
            }
            else {
             m_feederMotor.Set(0.0);
            }

            //indexer test
            if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonY)))
            {
                m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.Set(SmartDashboard::GetNumber("DB/Slider 3", 0.0));
            }
            else {
                m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.Set(0);

            }
            // Fly wheel Test
            if ((m_pidState == VOLTAGE) && (m_gamepad.GetRawButton(DriveStationConstants::buttonRB)))
            {
                m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
            }
            else if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonLB)))
            {
                m_lowerFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                m_topFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
            }
            else {
                m_lowerFlyWheelMotor.goAt(0.0);
                m_topFlyWheelMotor.goAt(0.0);

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
            if (m_pidState == PID)
            {
                m_FRDrive.SetControlMode(CANSpeedController::kSpeed);
                m_FLDrive.SetControlMode(CANSpeedController::kSpeed);
                m_BRDrive.SetControlMode(CANSpeedController::kSpeed);
                m_BLDrive.SetControlMode(CANSpeedController::kSpeed);
                m_FRDrive.goAt(power);
                m_FLDrive.goAt(power);
                m_BRDrive.goAt(power);
                m_BLDrive.goAt(power);
            }
            if (m_pidState == VOLTAGE)
            {
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

	//SmartDashboard::PutString("DB/String 6", mode);

	vector<shared_ptr<Action>>::iterator actionIterator;
	for(actionIterator = allActions.begin(); actionIterator != allActions.end(); actionIterator++)
	{
		if(actionIterator->get ()->getName () == mode)
		{
		      //  SmartDashboard::PutString("DB/String 7","auto init");
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
    double throttle = (((m_joystick.GetThrottle() + 1) / 2));
    double FB = 0;
    double LR = 0;
    double rot = 0;

    if(m_joystick.GetRawButton(12))
    {
        LR = fabs(m_joystick.GetY());
        FB = fabs(m_joystick.GetX());
        rot = m_joystick.GetZ();

        throttle = throttle * 3.67;
        throttle += 1;

        throttle = 1;

        if(LR > 0.1)
            LR = pow(LR, throttle) * (fabs(m_joystick.GetY()) / m_joystick.GetY());
        else
            LR = 0;

        if(FB > 0.05)
            FB = pow(FB, throttle) * (fabs(m_joystick.GetX()) / m_joystick.GetX());
        else
            FB = 0;

        if(fabs(rot) > (0.05 * 10))
            rot /= 8;
        else
            rot = 0;

        FB *= 0.8;
        LR *= 0.6;
    }
    else
    {
        LR = fabs(m_joystick.GetX());
        FB = fabs(m_joystick.GetY());
        rot = m_joystick.GetZ();

        throttle *= 4;
        throttle += 1;

        throttle = 1;

        if(LR > 0.05)
            LR = pow(LR, throttle) * (fabs(m_joystick.GetX()) / m_joystick.GetX());
        else
            LR = 0;

        if(FB > 0.1)
            FB = -pow(FB, throttle) * (fabs(m_joystick.GetY()) / m_joystick.GetY());
        else
            FB = 0;

        if(fabs(rot) > (0.05 * 5))
            rot /= 4;
        else
            rot = 0;
    }

    FB *= (((m_joystick.GetThrottle() - 1) / -2));
    LR *= (((m_joystick.GetThrottle() - 1) / -2));
    rot *= 0.97;

    if(m_joystick.GetRawButton(9))
    {
        m_drivetrain.moveRelativeVoltage(FB, LR, rot * 1.6);
    }
    else
    {
        m_drivetrain.moveRelative(FB, LR, rot);
    }

    printMSG("0", "FB: " + std::to_string(FB));
    printMSG("1", "LR: " + std::to_string(LR));
    printMSG("2", "rot: " + std::to_string(rot));
    printMSG("3", "throttle: " + std::to_string(throttle));
}

void Robot::setIndexerSpeed(double speed)
{
    m_indexer.setSpeed(speed);
}

void Robot::setFeederState(int state)
{
    if (state == 1 || state == 2 || state == 3)
    {
        this->m_feeder.setState(Feeder::State::ON);
    } else
    {
        this->m_feeder.setState(Feeder::State::OFF);
    }

}

void Robot::setFlywheelState(int state)
{
    if (state == 1)
    {
        this->m_flywheel.setState(FlyWheels::STATE::FLATRATE);
    }
    else if (state == 2)
    {
        this->m_flywheel.setState(FlyWheels::STATE::LIDARRATE);
    }
    else if (state == 3)
    {
        this->m_flywheel.setState(FlyWheels::STATE::JOYSTICKRATE);
    }
    else
    {
        this->m_flywheel.setState(FlyWheels::STATE::OFF);
        printMSG("4", "Flywheels OFF");
    }
}

void Robot::setIndexerState(int state)
{
    if (state == 0)
    {
        this->m_indexer.setState(Indexer::State::TELEOP);
    }
    else if (state == 1)
    {
        this->m_indexer.setState(Indexer::State::ON);
    }
    else
    {
        this->m_indexer.setState(Indexer::State::OFF);
    }
}

START_ROBOT_CLASS(Robot)
