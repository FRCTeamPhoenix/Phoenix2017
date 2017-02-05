#include "Robot.h"
#include "Actions/ActionFactory.h"


Robot::Robot() :
        m_FRDrive(7, CANTalon::FeedbackDevice::QuadEncoder),
        m_FLDrive(8, CANTalon::FeedbackDevice::QuadEncoder),
        m_BRDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
        m_BLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
        m_mainAutoGroup(new ActionGroup),
		m_expansionBoard(),
        m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_expansionBoard, HeadingControl::GyroAxes::x),
        //            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        //            m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        //            m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
        //            m_leftLimitSwitch(PortAssign::leftLimitSwitch),
        //            m_rightLimitSwitch( PortAssign::rightLimitSwitch),
        m_joystick(PortAssign::joystick),
        //            m_gamepad(PortAssign::gamepad),

        //            m_flywheel(m_rightFlyWheelMotor, m_leftFlyWheelMotor, m_gamepad),
        //            m_turret(m_turretRotateMotor,m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
        m_loggerController()
//            m_shooterController(m_flywheel, m_turret),
//            m_configEditor(),
//            m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
//			m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
//			m_climber(m_climberMotor, m_joystick)
{

}


void Robot::RobotInit()
{
    ifstream json_file;
    json_file.open("/home/lvuser/actions.json");
    try
    {
        json actionsJson;
        json_file >> actionsJson;
        json_file.close ();

        shared_ptr<Robot> m_bot(this);

        m_mainAutoGroup->initActionGroup (actionsJson, m_bot);
    }
    catch (std::domain_error(e))
    {
        cout << "Failed: ";
    }

    cout << "Done With Loading Actions" << endl;

    LOGI << "Start Robot Init";

}

void Robot::Autonomous()
{

//    bool init = false;

    LOGI << "Start Auto";
    while (IsEnabled() && IsAutonomous())
    {
        m_mainAutoGroup->execute (m_mainAutoGroup->getContainedActions ());
    }

}

void Robot::OperatorControl()
{

    LOGI << "Start Teleop";
    //int count = 0;

    while (IsEnabled() && IsOperatorControl())
    {

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
