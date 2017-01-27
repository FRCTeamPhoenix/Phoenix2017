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
#include <sstream>

using namespace std;
using json=nlohmann::json;

/*
 * Given a SmartTalon, runs it forward and backward at 60% for 3 seconds and
 * outputs the encoder's initial, final, and delta values.
 * Outputs Lidar values to SmartDashboard at the same time.
 */
void testSmartTalon(SmartTalon* talon, const char* name, Lidar* lidar);
#define TEST_SMART_TALON(talon) testSmartTalon(&talon, #talon, &m_lidar)
/*
 * Given a Talon, runs it forward and backward at 60% for 3 seconds.
 * Outputs Lidar values to SmartDashboard at the same time.
 */
void testTalon(Talon* talon, const char* name, Lidar* lidar);
#define TEST_TALON(talon) testTalon(&talon, #talon, &m_lidar)
/*
 * Given a SmartTalon, waits for its upper/lower limit switch's input and logs
 * the event. Test can be canceled by pressing A button on gamepad.
 */
void testUpperLimitSwitch(SmartTalon* talon, const char* name, Joystick* gamepad);
#define TEST_UPPER_LIMIT_SWITCH(talon) testUpperLimitSwitch(&talon, #talon, &m_gamepad)
void testLowerLimitSwitch(SmartTalon* talon, const char* name, Joystick* gamepad);
#define TEST_LOWER_LIMIT_SWITCH(talon) testLowerLimitSwitch(&talon, #talon, &m_gamepad)

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
    SmartTalon m_indexer;
    Talon m_loader;
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
            m_indexer(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder),
            m_loader(PortAssign::loader),
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

                TEST_SMART_TALON(m_FRDrive);                    // LD1
                TEST_SMART_TALON(m_FLDrive);                    // LD2
                TEST_SMART_TALON(m_BRDrive);                    // RD1
                TEST_SMART_TALON(m_BLDrive);                    // RD2
                TEST_SMART_TALON(m_leftFlyWheelMotor);          // FW1
                TEST_SMART_TALON(m_rightFlyWheelMotor);         // FW2
                TEST_SMART_TALON(m_climberMotor);               // CMR
                // TEST_SMART_TALON(m_feeder);
                TEST_SMART_TALON(m_turretRotateMotor);          // TRT
                TEST_SMART_TALON(m_indexer);                    // INDX

                TEST_TALON(m_loader);                           // LOAD

                TEST_UPPER_LIMIT_SWITCH(m_climberMotor);        // CLIME
                TEST_UPPER_LIMIT_SWITCH(m_turretRotateMotor);   // CWRL
                TEST_LOWER_LIMIT_SWITCH(m_turretRotateMotor);   // CCWRL
                TEST_UPPER_LIMIT_SWITCH(m_indexer);             // INDXS

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

/*
 * Function that updates Lidar and outputs calculated
 * distances to SmartDashboard.
 */
void
lidarDebugUpdate(Lidar* lidar)
{
    lidar->run();

    std::stringstream slowAverage;
    slowAverage << "Lidar Slow Average: " << lidar->getSlowAverage();
    SmartDashboard::PutString("DB/String 8", slowAverage.str());

    std::stringstream fastAverage;
    slowAverage << "Lidar Fast Average: " << lidar->getFastAverage();
    SmartDashboard::PutString("DB/String 9", fastAverage.str());
}

void
testSmartTalon(SmartTalon* talon, const char* name, Lidar* lidar)
{
    int initialPos;
    int finalPos;
    Timer timer;

    LOGI << "Spinning SmartTalon " << name << " forward at 60% for 3 seconds.";
    initialPos = talon->Get();
    timer.Start();
    while (timer.Get() < 3)
    {
        talon->goAt(0.6);
        lidarDebugUpdate(lidar);
    }
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
    {
        talon->goAt(-0.6);
        lidarDebugUpdate(lidar);
    }
    timer.Stop();
    talon->goAt(0.0);
    LOGI << name << "'s initial encoder value: " << initialPos;
    LOGI << name << "'s final encoder value: " << finalPos;
    LOGI << name << "'s encoder delta: " << finalPos - initialPos;
}

void
testTalon(Talon* talon, const char* name, Lidar* lidar)
{
    Timer timer;

    LOGI << "Spinning Talon " << name << " forward at 60% for 3 seconds.";
    timer.Start();
    while (timer.Get() < 3)
    {
        talon->Set(0.6);
        lidarDebugUpdate(lidar);
    }
    timer.Stop();
    talon->Set(0.0);

    LOGI << "Spinning Talon " << name << " backward at 60% for 3 seconds.";
    timer.Reset();
    timer.Start();
    while (timer.Get() < 3)
    {
        talon->Set(-0.6);
        lidarDebugUpdate(lidar);
    }
    timer.Stop();
    talon->Set(0.0);
}

void
testUpperLimitSwitch(SmartTalon* talon, const char* name, Joystick* gamepad)
{
    std::stringstream db0, db1;

    LOGI << "Waiting on " << name << "'s upper limit switch input.";
    db0 << "Push " << name << "'s upper limit switch to continue.";
    db1 << "Push A button on gamepad to skip.";
    SmartDashboard::PutString("DB/String 0", db0.str());
    SmartDashboard::PutString("DB/String 1", db1.str());

    bool success; // Was limit switch pressed?
    /* Wait for either the limit switch or A button to be pressed. */
    while (!(success = talon->IsFwdLimitSwitchClosed()) && !gamepad->GetRawButton(DriveStationConstants::buttonA));

    if (success)
    {
        LOGI << name << "'s upper limit switch has been pressed.";
    }
    else
    {
        LOGI << name << "'s upper limit switch test has been skipped.";
        SmartDashboard::PutString("DB/String 0", "Release A button.");
        SmartDashboard::PutString("DB/String 1", "");
        /* Wait for A button to be released. */
        while (gamepad->GetRawButton(DriveStationConstants::buttonA));
    }
}

void
testLowerLimitSwitch(SmartTalon* talon, const char* name, Joystick* gamepad)
{
    std::stringstream db0, db1;

    LOGI << "Waiting on " << name << "'s lower limit switch input.";
    db0 << "Push " << name << "'s lower limit switch to continue.";
    db1 << "Push A button on gamepad to skip.";
    SmartDashboard::PutString("DB/String 0", db0.str());
    SmartDashboard::PutString("DB/String 1", db1.str());

    bool success; // Was limit switch pressed?
    /* Wait for either the limit switch or A button to be pressed. */
    while (!(success = talon->IsRevLimitSwitchClosed()) && !gamepad->GetRawButton(DriveStationConstants::buttonA));

    if (success)
    {
        LOGI << name << "'s lower limit switch has been pressed.";
    }
    else
    {
        LOGI << name << "'s lower limit switch test has been skipped.";
        SmartDashboard::PutString("DB/String 0", "Release A button.");
        SmartDashboard::PutString("DB/String 1", "");
        /* Wait for A button to be released. */
        while (gamepad->GetRawButton(DriveStationConstants::buttonA));
    }
}
