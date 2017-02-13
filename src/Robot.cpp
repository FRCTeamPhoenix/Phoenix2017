#include "Robot.h"
#include "Actions/ActionFactory.h"

using namespace std;
using json=nlohmann::json;

Robot::Robot() :
        m_FRDrive(7, CANTalon::FeedbackDevice::QuadEncoder),
        m_FLDrive(8, CANTalon::FeedbackDevice::QuadEncoder),
        m_BRDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
        m_BLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
        m_mainAutoGroup(new ActionGroup()),
        m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_expansionBoard, HeadingControl::GyroAxes::x),
        m_topFlyWheelMotor(PortAssign::topFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        m_lowerFlyWheelMotor(PortAssign::lowerFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
        m_leftLimitSwitch(PortAssign::leftLimitSwitch),
        m_rightLimitSwitch( PortAssign::rightLimitSwitch),
        m_joystick(PortAssign::joystick),
        m_gamepad(PortAssign::gamepad),
        m_lidar(PortAssign::lidarTriggerPin, PortAssign::lidarMonitorPin, 0),
        m_expansionBoard(),
        m_visionComs(),
        m_shooterCalibrator(),
        m_flywheel(m_lowerFlyWheelMotor, m_topFlyWheelMotor, m_shooterCalibrator, m_lidar, m_gamepad, m_joystick),
        m_turret(m_turretRotateMotor,m_visionComs, m_gamepad),
        m_loggerController(),
        m_shooterController(m_flywheel, m_turret),
        m_configEditor(),
        m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
        m_climber(m_climberMotor, m_joystick),
        m_gathererMotor(PortAssign::loader),
        m_feederMotor(PortAssign::feeder, CANTalon::FeedbackDevice::QuadEncoder),
        m_indexerMotor(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder),
        m_indexer(m_indexerMotor, m_gamepad),
        m_feeder(m_feederMotor, m_gamepad),
        m_gatherer(m_gathererMotor, m_gamepad)
{

}

void Robot::RobotInit()
{
	cout << "In Robot INIT" << endl;
    initMainActionGroup();
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
        printf("HELLO\n");
        m_turret.run();
        m_visionComs.setNumber("debug", -1.0);
        string mode = SmartDashboard::GetString("Auto Selector", "None");
    	SmartDashboard::PutString("DB/String 7", mode);
    }
}

void Robot::Test()
{

    m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
    m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
    m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
    m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);

    LOGI << "Start Test Mode";
    while (IsEnabled() && IsTest())
    {
        if(m_joystick.GetRawButton (6))
            m_FRDrive.Set (0.2);
        else
            m_FRDrive.Set (0);

        if(m_joystick.GetRawButton (5))
            m_FLDrive.Set (0.2);
        else
            m_FLDrive.Set (0);

        if(m_joystick.GetRawButton (4))
            m_BRDrive.Set (0.2);
        else
            m_BRDrive.Set (0);

        if(m_joystick.GetRawButton (3))
            m_BLDrive.Set (0.2);
        else
            m_BLDrive.Set (0);
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
