/*
 * LoggerController.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: connortess
 */

#include "LoggerController.h"

LoggerController::LoggerController()
{
    initLogger();
}

LoggerController::~LoggerController()
{
    // TODO Auto-generated destructor stub
}

void LoggerController::initLogger()
{

    plog::init(plog::debug,"/home/lvuser/robot_log.txt",10000,2);

    static plog::RollingFileAppender<plog::UndecoratedFormatter> fileAppender("/home/lvuser/CAN_Speed_Tuning.csv"); // Create the 1st appender.

    plog::init<SpeedTuningLog>(plog::debug, &fileAppender);
    LOGI << "Log initialized at Debug";

}

void LoggerController::setSeverity(plog::Severity severity)
{

    /* Logger Severity Levels, displays all levels below set severity level
     *      none = 0,
     fatal = 1,
     error = 2,
     warning = 3,
     info = 4,
     debug = 5,
     verbose = 6
     */

    plog::get()->setMaxSeverity(severity);
    LOGF << "Severity Change: Severity changed to " << plog::severityToString(severity);
}

void LoggerController::updateSeverity()
{
    //Interfacing in labview on the driver station
    int place = (int) SmartDashboard::GetNumber("Level of Severity", -1);

    plog::Severity severity = (plog::Severity) place;

    if (severity != plog::get()->getMaxSeverity())
    {
        LOGF << "Severity Change: Severity changed to " << plog::severityToString(severity);
    }

    plog::get()->setMaxSeverity(severity);
}

string LoggerController::getSeverityString()
{
    return plog::severityToString(plog::get()->getMaxSeverity());

}

int LoggerController::getSeverityInt()
{
    return (int) plog::get()->getMaxSeverity();
}
