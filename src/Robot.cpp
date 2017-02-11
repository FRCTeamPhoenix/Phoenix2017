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
        string mode = SmartDashboard::GetString("Auto Selector", "None");
    	SmartDashboard::PutString("DB/String 7", mode);
    }
}

void Robot::Test()
{

        LOGI << "Start Test Mode";

        m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
        m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);

        m_topFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
        m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);


        while (IsEnabled() && IsTest())
        {
            //A = indexer quarter rotation
            //B = feeder run of dashboard from slider 0 input
            //joystick throttle = run feeder
            //joystick Y = run flywheels
            //gamepad Y -= run indexer
            // X = run flywheels off driverstation from slider 1 and 2 input


           // FEEDER
           // B: Run feeder off dashboard from slider 0 input
           // Joystick throttle: Run feeder
           if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
              m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0",0.0));

           }
           else
           {
               m_feederMotor.Set((m_joystick.GetThrottle()-1) / 2);
           }
            std::ostringstream throttleValue;
            throttleValue << "Throttle: ";
            throttleValue << ((m_joystick.GetThrottle()-1) / 2);
            SmartDashboard::PutString("DB/String 7", throttleValue.str());

            std::ostringstream feederEncoderValue;
            feederEncoderValue << "EncoderF: ";
            feederEncoderValue << m_feederMotor.GetEncPosition();
            SmartDashboard::PutString("DB/String 6", feederEncoderValue.str());



            // INDEXER
            // A: Indexer quarter rotation
            // Gamepad Y: Run indexer
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)){
                m_indexerMotor.goDistance(250,0.5);

           }
            else{
                m_indexerMotor.Set(m_gamepad.GetY());
            }

           std::ostringstream indexerEncoderValue;
           indexerEncoderValue << "EncoderI: ";
           indexerEncoderValue << m_feederMotor.GetEncPosition();
           SmartDashboard::PutString("DB/String 8", indexerEncoderValue.str());

           // FLYWHEELS
           // X: Run flywheels off driverstation from slider 1 and 2 input
           // Joystick Y: Run flywheels
           if (m_gamepad.GetRawButton(DriveStationConstants::buttonX)){

               // Power-based
//               m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1",0.0));
//               m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2",0.0));

               // Velocity-based (implement only after PID tuning of flywheel motors)

               m_topFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1",0.0));
               m_lowerFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2",0.0));


           }
           else
           {
               m_topFlyWheelMotor.Set(-m_joystick.GetY());
               m_lowerFlyWheelMotor.Set(-m_joystick.GetY());
           }



           std::ostringstream shooterRightEncoderString;
           shooterRightEncoderString << "EncoderTop: ";
           shooterRightEncoderString << m_topFlyWheelMotor.GetEncPosition();
           SmartDashboard::PutString("DB/String 4", shooterRightEncoderString.str());

           std::ostringstream shooterLeftEncoderString;
           shooterLeftEncoderString << "EncoderLow: ";
           shooterLeftEncoderString << m_lowerFlyWheelMotor.GetEncPosition();
           SmartDashboard::PutString("DB/String 5", shooterLeftEncoderString.str());

           std::ostringstream lidarString;
           lidarString << "Distance: ";
           lidarString << m_lidar.getFastAverage();
           SmartDashboard::PutString("DB/String 9", lidarString.str());

           std::ostringstream shooterTopVel;
           shooterTopVel << "VelTop: ";
           shooterTopVel << m_topFlyWheelMotor.GetEncVel();
           //shooterTopVel << SmartDashboard::GetNumber("DB/Slider 1", 0.0);
           SmartDashboard::PutString("DB/String 10", shooterTopVel.str());

           std::ostringstream shooterLowVel;
           shooterLowVel << "VelLow: ";
           shooterLowVel << m_lowerFlyWheelMotor.GetEncVel();
           //shooterLowVel << SmartDashboard::GetNumber("DB/Slider 2", 0.0);
           SmartDashboard::PutString("DB/String 11", shooterLowVel.str());


           m_configEditor.update();



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
