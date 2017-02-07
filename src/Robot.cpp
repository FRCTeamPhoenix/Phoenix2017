#include "Robot.h"
#include "Actions/ActionFactory.h"

Robot::Robot() :
        m_FRDrive(7, CANTalon::FeedbackDevice::QuadEncoder),
        m_FLDrive(8, CANTalon::FeedbackDevice::QuadEncoder),
        m_BRDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
        m_BLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
        m_mainAutoGroup(),
        m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
        m_topFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        m_lowerFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
        m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
        m_joystick(PortAssign::joystick),
        m_gamepad(PortAssign::gamepad),
        m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
        m_expansionBoard(),
        m_visionComs(),
        m_shooterCalibrator(),
        m_flywheel(m_topFlyWheelMotor, m_lowerFlyWheelMotor, m_shooterCalibrator, m_lidar, m_gamepad, m_joystick),
        m_turret(m_turretRotateMotor, m_visionComs, m_gamepad),
        m_loggerController(),
        m_shooterController(m_flywheel, m_turret),
        m_configEditor(),
	    m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
	    m_climber(m_climberMotor, m_joystick)
	    
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

        m_mainAutoGroup->initActionGroup (actionsJson, this);
    }
    catch (std::domain_error(e))
    {
        cout << "Failed: ";
    }


    LOGI << "Start Robot Init";

}

void Robot::Autonomous()
{

    bool init = false;

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

void Robot::driveAt(double speed, double angle){
    m_drivetrain.moveAt (speed, angle);
}


START_ROBOT_CLASS(Robot)
