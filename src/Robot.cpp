#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"
#include "SmartTalon.h"
#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "ADIS16448_IMU.h"
#include "ConfigEditor.h"
#include "LoggerController.h"
#include "FlyWheels.h"
#include "Turret.h"
#include "ShooterController.h"
#include "ConfigEditor.h"
#include "AutoController.h"
#include "Actions/Actions.h"
#include <fstream>
#include "json.hpp"
#include "Lidar.h"
#include "Climber.h"

using namespace std;
using json=nlohmann::json;

void testSmartTalon(SmartTalon* talon, const char* name);
#define TEST_SMART_TALON(talon) testSmartTalon(&talon, #talon)
void testTalon(Talon* talon, const char* name);
#define TEST_TALON(talon) testTalon(&talon, #talon)

class Robot: public SampleRobot
{
    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;
    relativeMecanumDrivetrain m_drivetrain;
    SmartTalon m_rightFlyWheelMotor;
    SmartTalon m_leftFlyWheelMotor;
    SmartTalon m_turretRotateMotor;
    Talon m_loader;
    Talon m_indexer;
    DigitalInput m_leftLimitSwitch;
    DigitalInput m_rightLimitSwitch;
    Joystick m_joystick;
    Joystick m_gamepad;
    ADIS16448_IMU m_expansionBoard;
    FlyWheels m_flywheel;
    Turret m_turret;
    LoggerController m_loggerController;
    ShooterController m_shooterController;
    ConfigEditor m_configEditor;
    AutoController m_autoController;
    Lidar m_lidar;
    SmartTalon m_climberMotor;
    Climber m_climber;

    const bool m_debug = true; // Set this to false unless you want debug feature

public:
    Robot() :
            m_FRDrive(3, CANTalon::FeedbackDevice::QuadEncoder),
            m_FLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
            m_BRDrive(4, CANTalon::FeedbackDevice::QuadEncoder),
            m_BLDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
            m_loader(0),
            m_indexer(1),
            m_leftLimitSwitch(PortAssign::leftLimitSwitch),
            m_rightLimitSwitch( PortAssign::rightLimitSwitch),
            m_joystick(PortAssign::joystick),
            m_gamepad(PortAssign::gamepad),
            m_expansionBoard(),
            m_flywheel(m_rightFlyWheelMotor, m_leftFlyWheelMotor, m_gamepad),
            m_turret(m_turretRotateMotor,m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
            m_loggerController(),
            m_shooterController(m_flywheel, m_turret),
            m_configEditor(),
            m_autoController(),
            m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
			m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
			m_climber(m_climberMotor, m_joystick)
    {
    }

    void RobotInit() override
    {
        LOGI << "Start Robot Init";

    }

    void Autonomous()
    {

        bool init = false;

        LOGI << "Start Auto";
        while (IsEnabled() && IsAutonomous())
        {
            if (!init)
            {
                init = true;
            }

            m_autoController.run();
        }

    }
    void OperatorControl()
    {

        m_expansionBoard.Reset();
        LOGI << "Start Teleop";
        //int count = 0;

        while (IsEnabled() && IsOperatorControl())
        {

        }

    }

    void Test()
    {
        LOGI << "Start Test Mode";
        if (IsEnabled())
        {
            if (m_debug)
            {
                LOGD << "Entering Debug Test Mode";

                TEST_SMART_TALON(m_FRDrive);
                TEST_SMART_TALON(m_FLDrive);
                TEST_SMART_TALON(m_BRDrive);
                TEST_SMART_TALON(m_BLDrive);
                TEST_SMART_TALON(m_leftFlyWheelMotor);
                TEST_SMART_TALON(m_rightFlyWheelMotor);
                // TEST_SMART_TALON(m_climber);
                // TEST_SMART_TALON(m_feeder);
                TEST_SMART_TALON(m_turretRotateMotor);

                TEST_TALON(m_loader);
                TEST_TALON(m_indexer);

                LOGD << "Leaving Debug Test Mode";
            }
            while (IsTest())
            {
                // m_rightFlyWheelMotor.goAt(m_joystick.GetY());
                // m_leftFlyWheelMotor.goAt(m_joystick.GetY());
        	m_climber.run();
                m_configEditor.update();
            }
        }
    }

};

START_ROBOT_CLASS(Robot)

void
testSmartTalon(SmartTalon* talon, const char* name)
{
    int initialPos;
    int finalPos;
    Timer timer;

    LOGI << "Spinning SmartTalon " << name << " forward at 60% for 3 seconds.";
    initialPos = talon->Get();
    timer.Start();
    while (timer.Get() < 3)
        talon->goAt(0.6);
    timer.Stop();
    talon->goAt(0.0);
    finalPos = talon->Get();
    LOGI << name << "'s initial encoder value: " << initialPos;
    LOGI << name << "'s final encoder value: " << finalPos;
    LOGI << name << "'s encoder delta: " << finalPos - initialPos;

    LOGI << "Spinning SmartTalon " << name << " backward at 60% for 3 seconds.";
    initialPos = talon->Get();
    timer.Reset();
    timer.Start();
    while (timer.Get() < 3)
        talon->goAt(-0.6);
    timer.Stop();
    talon->goAt(0.0);
    LOGI << name << "'s encoder delta: " << talon->Get() - initialPos;
}

void
testTalon(Talon* talon, const char* name)
{
    Timer timer;

    LOGI << "Spinning Talon " << name << " forward at 60% for 3 seconds.";
    timer.Start();
    while (timer.Get() < 3)
        talon->Set(0.6);
    timer.Stop();
    talon->Set(0.0);

    LOGI << "Spinning Talon " << name << " backward at 60% for 3 seconds.";
    timer.Reset();
    timer.Start();
    while (timer.Get() < 3)
        talon->Set(-0.6);
    timer.Stop();
    talon->Set(0.0);
}
