#include "Robot.h"
#include "Actions/ActionFactory.h"

using namespace std;
using json=nlohmann::json;

Robot::Robot() :
        		m_FRDrive(PortAssign::frontRightWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_FLDrive(PortAssign::frontLeftWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_BRDrive(PortAssign::backRightWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_BLDrive(PortAssign::backLeftWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_mainAutoGroup(new ActionGroup()),
				m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_expansionBoard, HeadingControl::GyroAxes::x),
				m_topFlyWheelMotor(PortAssign::topFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_lowerFlyWheelMotor(PortAssign::lowerFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
				m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
				m_leftLimitSwitch(PortAssign::leftLimitSwitch),
				m_rightLimitSwitch( PortAssign::rightLimitSwitch),
				m_joystick(PortAssign::joystick),
				m_gamepad(PortAssign::gamepad),
				//        m_controlBox(PortAssign::controlBox),
				m_lidar(PortAssign::lidarTriggerPin, PortAssign::lidarMonitorPin, 0),
				m_expansionBoard(),
				m_visionComs(),
				m_shooterCalibrator(),
				m_flywheel(m_lowerFlyWheelMotor, m_topFlyWheelMotor, m_shooterCalibrator, m_lidar, m_gamepad),
				m_turret(m_turretRotateMotor,m_visionComs, m_gamepad),
				m_loggerController(),
				m_configEditor(),
				m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
				m_climber(m_climberMotor, m_gamepad),
				m_gathererMotor(PortAssign::loader),
				m_feederMotor(PortAssign::feeder, CANTalon::FeedbackDevice::QuadEncoder),
				m_indexerMotor(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder),
				m_indexer(m_indexerMotor, m_gamepad),
				m_feeder(m_feederMotor, m_gamepad),
				m_gatherer(m_gathererMotor, m_gamepad),
				m_robotController(m_flywheel, m_turret, m_feeder, m_indexer, m_gamepad, m_climber, m_gatherer)
{

}

void Robot::RobotInit()
{
	cout << "In Robot INIT" << endl;
	initMainActionGroup();
	SmartDashboard::PutStringArray("Test List", testModes);
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
	//int count = 0;

	while (IsEnabled() && IsOperatorControl())
	{


		/*
		 * Robot Teleop Controls:
		 * Button A held: Feeder and Flywheels on, flywheels at joystick rate or lidar rate
		 * Button B pressed: turret auto on
		 * Button X pressed: turret auto off
		 * Button Y held: indexer on
		 * Button LB held: climber on
		 * Button RB held: Gatherer on
		 * Gamepad left joystick: turret Control
		 * Joystick: Control drivetrain
		 *
		 */

		m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
		m_robotController.run();
		m_climber.run();

	}
}

// Print the Message on the Drive Station For Test Mode
void printMSG(string place, string msg) {
	std::ostringstream stream;
	stream << msg;
	SmartDashboard::PutString("DB/String " + place, stream.str());
	stream.clear();
}

void Robot::Test()
{
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
        switch (m_pidState)
        {
        case PID:
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonB))
            {
                m_pidState = VOLTAGE;
                break;
            }
            break;
        case VOLTAGE:
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA))
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
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
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
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
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
                    m_feederMotor.Set(throttle);
                }
                else
                {
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
            if (m_pidState == PID)
            {
                m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
                m_turretRotateMotor.goDistance(power * 25, 0.5);

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
            printMSG("3", "Lidar: " + std::to_string(m_lidar.getFastAverage()));
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
            printMSG("0", "All Shooter Test Mode");
            printMSG("1", "Control Mode: " + std::to_string(m_pidState));
            printMSG("4", "EncoderShR: " + std::to_string(m_lowerFlyWheelMotor.GetEncPosition()));
            printMSG("5", "EncoderShL: " + std::to_string(m_topFlyWheelMotor.GetEncPosition()));
            printMSG("6", "EncoderF: " + std::to_string(m_feederMotor.GetEncPosition()));
            printMSG("7", "Throttle: " + std::to_string(((throttle - 1) / 2)));
            printMSG("8", "EncoderI: " + std::to_string(m_feederMotor.GetEncPosition()));
            printMSG("9", "Distance: " + std::to_string(m_lidar.getFastAverage()));
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
                m_feederMotor.goAt(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
                m_feederMotor.goAt(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
            }
            else if ((m_pidState == PID))
            {
                m_feederMotor.goAt((throttle - 1) / 2);
            }

            //indexer test
            if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonY)))
            {
                m_indexerMotor.goDistance(250, 0.5);
            }
            // Shooter Test
            else if ((m_pidState == PID))
            {
                m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
                m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
                m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                m_topFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                m_indexerMotor.goAt(power / 5);
                m_lowerFlyWheelMotor.goAt(m_gamepad.GetY());
                m_topFlyWheelMotor.goAt(m_gamepad.GetY());
            }
            else if (m_pidState == VOLTAGE)
            {
                m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_topFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.Set(power / 5);
                m_lowerFlyWheelMotor.Set(m_gamepad.GetY());
                m_topFlyWheelMotor.Set(m_gamepad.GetY());
            }
            // Fly wheel Test
            if ((m_pidState == VOLTAGE) && (m_gamepad.GetRawButton(DriveStationConstants::buttonRB)))
            {
                m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
            }
            else if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonRB)))
            {
                m_lowerFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                m_topFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
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
	bool validJson = true;
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
			actionIterator->get ()->reset ();
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

START_ROBOT_CLASS(Robot)
