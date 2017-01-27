#include "WPILib.h"
#include "constants.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "LoggerController.h"
#include "ConfigEditor.h"
#include "SmartTalon.h"
#include "Climber.h"
#include "Gatherer.h"

using namespace std;

class Robot: public SampleRobot
{
        Talon m_FRDrive;
        Talon m_FLDrive;
        Talon m_BRDrive;
        Talon m_BLDrive;
        LoggerController m_loggerController;
        SmartTalon m_climberMotor;
        Joystick m_gamepad;
        Climber m_climber;
        //Talon m_gatherMotor;
        //sGatherer m_gatherer;


    public:
        Robot():
            m_FRDrive(PortAssign::frontRightWheelMotor),
            m_FLDrive(PortAssign::frontLeftWheelMotor),
            m_BRDrive(PortAssign::backRightWheelMotor),
            m_BLDrive(PortAssign::backLeftWheelMotor),
            m_loggerController(),
			m_climberMotor(2, CANTalon::FeedbackDevice::QuadEncoder),
			m_gamepad(PortAssign::gamepad),
			m_climber(m_climberMotor, m_gamepad)
			/* m_gatherMotor(1),
			m_gatherer(m_gatherMotor, m_gamepad) */
    {
    }
        void RobotInit() override {
            LOGI << "Start Robot Init";

        }

        void Autonomous() {
            LOGI << "Start Auto";

        }

        void OperatorControl() {
            LOGI << "Start Teleop";

        }

        void Test() {
            LOGI << "Start Test Mode";
            while (IsEnabled() && IsTest()) {
            	m_climber.move(2000.0);
            	Wait(1);
            	LOGI << "Gatherer Motor";
            	m_climber.stop();
            	Wait(1);
        	}
        }
};

START_ROBOT_CLASS(Robot)
