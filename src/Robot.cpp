#include "WPILib.h"
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

//Test mode includes
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

enum pidState {
	PID,
	VOLTAGE
};

using namespace std;
using json=nlohmann::json;

class Robot: public SampleRobot
{
	// TODO NEED ALL OF THE ACTUAL PIN NUMBERS CHECKED AND NEEDS FIX.
	// CHECK CONSTANTS.H
	// TODO NEEDS TO BE TESTED
	SmartTalon m_FRDrive;
	SmartTalon m_FLDrive;
	SmartTalon m_BRDrive;
	SmartTalon m_BLDrive;
	relativeMecanumDrivetrain m_drivetrain;
	SmartTalon m_rightFlyWheelMotor;
	SmartTalon m_leftFlyWheelMotor;
	SmartTalon m_turretRotateMotor;
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
	SmartTalon m_feederMotor;
	SmartTalon m_indexerMotor;
	Talon m_gathererMotor;
	pidState m_pidState;

private:
	frc::SendableChooser<int*> m_testModeChooser;

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
		m_climber(m_climberMotor, m_joystick),
		m_feederMotor(PortAssign::feeder, CANTalon::FeedbackDevice::QuadEncoder),
		m_indexerMotor(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder),
		m_gathererMotor(PortAssign::gatherer)
{
}
	void RobotInit() override
			{
		LOGI << "Start Robot Init";
		m_testModeChooser.AddObject("All Talons", new int (1)); //Test all Talons on robot
		m_testModeChooser.AddObject("Shooter Head", new int (2)); //Test Shooter Head
		m_testModeChooser.AddObject("Feeder", new int (3)); //Test Feeder
		m_testModeChooser.AddObject("Indexer", new int (4)); //Test Indexer
		m_testModeChooser.AddObject("Gatherer", new int (5)); //Test Gather
		m_testModeChooser.AddObject("Turret", new int (6)); //Test Turret
		m_testModeChooser.AddObject("Climber", new int (7)); //Test Climber
		m_testModeChooser.AddObject("All of Shooter", new int (8)); //Test all Shooter Components
		m_testModeChooser.AddObject("Drive Train", new int (9)); //Test all 4 Drive Train Motors
		frc::SmartDashboard::PutData("Test Modes", &m_testModeChooser);
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

	void allTalonsText() {
		std::ostringstream mode;
		mode << "All Talons";
		SmartDashboard::PutString("DB/String 0", mode.str());

		std::ostringstream encoderDrive; // Encoder for all talons
		encoderDrive << m_FRDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 1", "FRD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_FLDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "FLD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_BRDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 3", "BRD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_BLDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 4", "BLD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_rightFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 5", "RFW ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_leftFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 6", "LFW ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_turretRotateMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 7", "TRM ENC: " + encoderDrive.str());
		encoderDrive.clear();
	}

	void shooterHeadText() {
		std::ostringstream mode;
		mode << "Shooter Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderFW; // Encoder for the Fly Wheels
		encoderFW << "RFW: " << m_rightFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "RFW ENC: " + encoderFW.str());
		encoderFW.clear();
		encoderFW << "LFW: " << m_leftFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 3", "LFW ENC: " + encoderFW.str());
		std::ostringstream encoderLG; // Encoder for the Lidar and the Gyro
		encoderLG << "Lidar Distance: " << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 4", "LFW ENC: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 5", "Gyro Angle: " + encoderLG.str());
		encoderLG.clear();
	}

	void climberText() {
		std::ostringstream mode;
		mode << "Climber Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderClimber; // Encoder for the Climber
		encoderClimber << m_climberMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "Climber ENC: " + encoderClimber.str());
		encoderClimber.clear();
		std::ostringstream encoderLG; // Encoder For Lidar and Gyro
		encoderLG << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 3", "Distance: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 4", "Gyro ENC: " + encoderLG.str());
		encoderLG.clear();
	}

	void feederText() {
		std::ostringstream mode;
		mode << "Feeder Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderFeeder;
		encoderFeeder << m_feederMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "Feeder ENC: " + encoderFeeder.str());
		std::ostringstream encoderLG; // Encoder for the Gyro and the Lidar
		encoderLG << "Lidar Distance: " << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 3", "Distance: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << "Gyro Angle: " << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 4", "Gyro ENC: " + encoderLG.str());
	}

	void indexerText() {
		std::ostringstream mode;
		mode << "Indexer Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderIndexer;
		encoderIndexer << m_indexerMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "Indexer ENC: " + encoderIndexer.str());
		std::ostringstream encoderLG; // Encoder for the Lidar and the Gyro
		encoderLG << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 3", "Distance: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 4", "Gyro ENC: " + encoderLG.str());
	}

	void gathererText() {
		std::ostringstream mode;
		mode << "Gather Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		std::ostringstream encoderGatherer;
		encoderGatherer << m_gathererMotor.GetSpeed();
		SmartDashboard::PutString("DB/String 1", "Gatherer Speed: " + encoderGatherer.str());
		std::ostringstream encoderLG; // Encoder for the Lidar and the Gyro
		encoderLG << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 2", "Distance: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 3", "Gyro ENC: " + encoderLG.str());
	}

	void turretText() {
		std::ostringstream mode;
		mode << "Turret Testing Mode";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderTurret;
		encoderTurret << m_turretRotateMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "Turret ENC: " + encoderTurret.str());
		std::ostringstream encoderLG; // Encoder for the Lidar and the Gyro
		encoderLG << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 3", "Distance: " + encoderLG.str());
		encoderLG.clear();
		encoderLG << m_expansionBoard.GetAngleX();
		SmartDashboard::PutString("DB/String 4", "Gyro ENC: " + encoderLG.str());
	}

	void allShooterText() {
		std::ostringstream encoder;
		encoder << "EncoderShR: ";
		encoder << m_rightFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 4", encoder.str());
		encoder.clear();
		encoder << "EncoderShL: ";
		encoder << m_leftFlyWheelMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 5", encoder.str());
		encoder.clear();
		encoder << "Throttle: ";
		encoder << ((m_joystick.GetThrottle()-1) / 2);
		SmartDashboard::PutString("DB/String 7", encoder.str());
		encoder.clear();
		encoder << "EncoderF: ";
		encoder << m_feederMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 6", encoder.str());
		encoder.clear();
		encoder << "EncoderI: ";
		encoder << m_feederMotor.GetEncPosition();
		SmartDashboard::PutString("DB/String 8", encoder.str());
		encoder.clear();
		encoder << "Distance: ";
		encoder << m_lidar.getFastAverage();
		SmartDashboard::PutString("DB/String 9", encoder.str());
	}

	void driveTrainText() {
		std::ostringstream mode;
		mode << "Drive Train Motors Test";
		SmartDashboard::PutString("DB/String 0", mode.str());
		mode.clear();
		mode << "Control Mode: " << m_pidState;
		SmartDashboard::PutString("DB/String 1", mode.str());
		std::ostringstream encoderDrive;
		encoderDrive << m_FRDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 2", "FRD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_FLDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 3", "FLD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_BRDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 4", "BRD ENC: " + encoderDrive.str());
		encoderDrive.clear();
		encoderDrive << m_BLDrive.GetEncPosition();
		SmartDashboard::PutString("DB/String 5", "BLD ENC: " + encoderDrive.str());
	}

	void Test()
	{
		LOGI << "Start Test Mode";
		m_pidState = PID;
		while (IsEnabled() && IsTest())
		{

			float power = m_joystick.GetY();
			if (fabs(power) < 0.05f){
				power = 0.0f;
			}
			else{
				power = m_joystick.GetY(); // You can get Full Power So BE CAREFUL!
			}

			switch(*m_testModeChooser.GetSelected())
			{
			case 1: //Test all Talons on robot
			{
				allTalonsText();
				m_FRDrive.goAt(power);
				m_FLDrive.goAt(power);
				m_BRDrive.goAt(power);
				m_BLDrive.goAt(power);
				m_rightFlyWheelMotor.goAt(power);
				m_leftFlyWheelMotor.goAt(power);
				m_turretRotateMotor.goAt(power);
				break;
			}

			case 2: //Test Shooter Head
			{
				switch(m_pidState) {
				case PID:
					m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
					m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_rightFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					m_leftFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				shooterHeadText();
				if (m_pidState == PID) {
					m_rightFlyWheelMotor.goAt(power);
					m_leftFlyWheelMotor.goAt(power);
				}
				else {
					m_rightFlyWheelMotor.Set(power);
					m_leftFlyWheelMotor.Set(power);
				}
				break;
			}

			case 3: //Test Feeder
			{
				switch(m_pidState) {
				case PID:
					m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_feederMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				feederText();
				if (m_pidState == PID) {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_feederMotor.Set(m_joystick.GetThrottle());
					}
					else {
						m_feederMotor.goAt(power);
					}
				}
				else {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_feederMotor.Set(m_joystick.GetThrottle());
					}
					else {
						m_feederMotor.Set(power);
					}
				}
				break;
			}

			case 4: //Test Indexer
			{
				switch(m_pidState) {
				case PID:
					m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_indexerMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				indexerText();
				if (m_pidState == PID) {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_feederMotor.goAt(m_joystick.GetThrottle());
					}
					else {
						m_feederMotor.goAt(power);
					}
				}
				else {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_feederMotor.Set(m_joystick.GetThrottle());
					}
					else {
						m_feederMotor.Set(power);
					}
				}
				break;
			}

			case 5: //Test Gather
			{
				gathererText();
				m_gathererMotor.Set(power);
				break;
			}

			case 6: //Test Turret
			{
				switch(m_pidState) {
				case PID:
					m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_turretRotateMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				turretText();
				if (m_pidState == PID) {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_turretRotateMotor.goAt(m_joystick.GetThrottle());
					}
					else {
						m_turretRotateMotor.goAt(power);
					}
				}
				else {
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonY)) {
						m_turretRotateMotor.Set(m_joystick.GetThrottle());
					}
					else {
						m_turretRotateMotor.Set(power);
					}
				}
				break;
			}

			case 7: //Test Climber
			{
				switch(m_pidState) {
				case PID:
					m_climberMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_climberMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				climberText();
				if (m_pidState == PID) {
					m_climberMotor.goAt(power);
				}
				else {
					m_climberMotor.Set(power);
				}
				break;
			}

			case 8: //Test all Shooter Components
			{

				switch(m_pidState) {
				case PID:
					m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
					m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
					m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
					m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonBack)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
					m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
					m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
					m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonStart)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				allShooterText();
				if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
					m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0",0.0));
					m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0",0.0));
				}
				else
				{
					m_feederMotor.Set((m_joystick.GetThrottle()-1) / 2);
				}
				//indexer test
				if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonA))){
					m_indexerMotor.goDistance(250,0.5);
				}
				else if ((m_pidState == PID)) {
					m_indexerMotor.goAt(power);
				}
				else if (m_pidState == VOLTAGE) {
					m_indexerMotor.Set(power);
				}
				// Fly wheel Test
				if ((m_pidState == VOLTAGE) && (m_gamepad.GetRawButton(DriveStationConstants::buttonX))){
					m_rightFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1",0.0));
					m_leftFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2",0.0));
				}
				else if ((m_pidState == PID) && (m_gamepad.GetRawButton(DriveStationConstants::buttonX))){
					m_rightFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1",0.0));
					m_leftFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2",0.0));
				}
				else if ((m_pidState == PID)){
					m_rightFlyWheelMotor.goAt(m_gamepad.GetY());
					m_leftFlyWheelMotor.goAt(m_gamepad.GetY());
				}
				else if (m_pidState == VOLTAGE)
				{
					m_rightFlyWheelMotor.Set(-m_gamepad.GetY());
					m_leftFlyWheelMotor.Set(-m_gamepad.GetY());
				}
				m_configEditor.update();
				break;
			}

			case 9: //Test all 4 Drive Train Motors
			{

				switch(m_pidState) {
				case PID:
					m_FRDrive.SetControlMode(CANSpeedController::kSpeed);
					m_FLDrive.SetControlMode(CANSpeedController::kSpeed);
					m_BRDrive.SetControlMode(CANSpeedController::kSpeed);
					m_BLDrive.SetControlMode(CANSpeedController::kSpeed);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)) {
						m_pidState = VOLTAGE;
						break;
					}
					break;
				case VOLTAGE:
					m_FRDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					m_FLDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					m_BRDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					m_BLDrive.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
					if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)) {
						m_pidState = PID;
						break;
					}
					break;
				}
				driveTrainText();
				if (m_pidState == PID) {
					m_FRDrive.goAt(power);
					m_FLDrive.goAt(power);
					m_BRDrive.goAt(power);
					m_BLDrive.goAt(power);
				}
				if (m_pidState == VOLTAGE) {
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
};

START_ROBOT_CLASS(Robot);
