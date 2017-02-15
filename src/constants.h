/*
 * constants.h
 *
 *  Created on: Jan 9, 2017
 *      Author: ben
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

struct PortAssign
{
    // CANTalon ID's
    const static uint32_t backLeftWheelMotor = 2; //updated values to reflect control boxes
    const static uint32_t frontLeftWheelMotor = 8;
    const static uint32_t frontRightWheelMotor = 7;
    const static uint32_t backRightWheelMotor = 1;
    const static uint32_t topFlyWheelMotor = 4;
    const static uint32_t lowerFlyWheelMotor = 3;
    const static uint32_t climber = 10;
    const static uint32_t feeder = 5;
    const static uint32_t turret = 9;
    const static uint32_t indexer = 6;

    // Talon Ports
    const static uint32_t loader = 0;

    // Controllers
    const static uint32_t joystick = 0;
    const static uint32_t gamepad = 1;

    // Limit Switches
    const static uint32_t rightLimitSwitch = 1;
    const static uint32_t leftLimitSwitch = 2;

    // Lidar Pins
    const static uint32_t lidarTriggerPin = 8;
    const static uint32_t lidarMonitorPin = 9;
};

struct RobotConstants
{
    constexpr static float turretDamp = 0.6f;
    constexpr static float degreesToTicks = 27.2727273f;
};

namespace ConfigVariables
{
    const static int numberOfVars = 5;
    const static std::string variables[numberOfVars] =
    {
        "PID_p",
        "PID_i",
        "PID_d",
        "PID_iz",
        "PID_f"
    };
    const static std::string types[numberOfVars] =
    {
        "double", // PID_p
        "double", // PID_i
        "double", // PID_d,
        "double", // PID_iz
        "double"  // PID_f
    };
    const static double protection[numberOfVars] =
    {
        true,
        true,
        true,
        true,
        true
    };
};

namespace DriveStationConstants
{
    enum buttonNames
    {
        buttonX = 1,
        buttonA = 2, // Start/Stop Climber
        buttonB = 3,
        buttonY = 4,
        buttonLB = 5,
        buttonRB = 6,
        triggerLT = 7, // Stop Shooter
        triggerRT = 8, // Start Shooter
        buttonBack = 9,
        buttonStart = 10,
        joystickLeftButton = 11,
        joystickRightButton = 12
    };
    const static std::string dashButtonNames[6] =
    {
        "New Name",
        "DB/Button 1",
        "DB/Button 2",
        "DB/Button 3",
        "Get Value",
        "Set Value"
    };
    const static std::string textBoxNames[13] =
    {
        "DB/String 0",
        "DB/String 1",
        "DB/String 2",
        "DB/String 3",
        "DB/String 4",
        "DB/String 5",
        "DB/String 6",
        "DB/String 7",
        "DB/String 8",
        "DB/String 9",
        "Key Name",
        "Key Value",
        "New Value"
    };
    const static uint32_t gamepadButtons = 12;
};

namespace JetsonComms {
    const static std::string tableName = "datatable";

    const static std::string stateId = "jetson_state";
    const static std::string modeId = "jetson_mode";

    const static std::string goalId = "high_goal";

    const static std::string gearRVecs = "gear_rvecs";
    const static std::string gearTVecs = "gear_tvecs";
};

#endif /* SRC_CONSTANTS_H_ */
