/*
 * LoggerController.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: connortess
 */

#include <LoggerController.h>

LoggerController::LoggerController()
{
    // TODO Auto-generated constructor stub

}

LoggerController::~LoggerController()
{
    // TODO Auto-generated destructor stub
}

void LoggerController::updateSeverity(){
    //int place = (int)SmartDashboard::GetNumber("Level of Severity", -1);
    int place = 1;
    plog::get()->setMaxSeverity((plog::Severity) place);
}
