/*
 * RLogger.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: joshc
 */

#include "RLogger.h"

RLogger::RLogger(
		SmartTalon & FRwheel,
		SmartTalon & FLwheel,
		SmartTalon & BRwheel,
		SmartTalon & BLwheel,
//		SmartTalon & topFlyWheel,
//		SmartTalon & lowerFlyWheel,
		Lidar & lidar):
		m_FRwheel(FRwheel),
		m_FLwheel(FLwheel),
		m_BRwheel(BRwheel),
		m_BLwheel(BLwheel),
//		m_topFlyWheel(topFlyWheel),
//		m_lowerFlyWheel(lowerFlyWheel),
		m_lidar(lidar)
{
	m_timer.Start();
	static plog::RollingFileAppender<plog::UndecoratedFormatter> fileAppender("/home/lvuser/Shooter_Log.csv");
	plog::init<LoggerFiles::LogFile>(plog::debug, &fileAppender);
	outputTalonHeaders("Front Right Wheel");
	outputTalonHeaders("Front Left Wheel");
	outputTalonHeaders("Back Right Wheel");
	outputTalonHeaders("Back Left Wheel");
//	outputTalonHeaders("TOP FLY Wheel");
//	outputTalonHeaders("Lower FLY Wheel");
	outputLidarHeaders("Lidar");
	printLogMSG(m_stringValues);
	m_stringValues.clear();
}

void RLogger::outputTalonHeaders(string talonName) {
	addLogMSG(talonName + "Enc Pos");
	addLogMSG(talonName + "Enc OutVol");
	addLogMSG(talonName + "Enc StPt");
	addLogMSG(talonName + "Enc Spd");
	addLogMSG(talonName + "Closed Loop Error");
}

void RLogger::outputTalonValues(SmartTalon & talon) {
	addLogMSG(std::to_string(talon.GetEncPosition()));
	addLogMSG(std::to_string(talon.GetOutputVoltage()));
	addLogMSG(std::to_string(talon.GetSetpoint()));
	addLogMSG(std::to_string(talon.GetEncVel()));
	addLogMSG(std::to_string(talon.GetClosedLoopError()));
}

void RLogger::outputLidarHeaders(string lidarName) {
	addLogMSG(lidarName + "Lidar Avg");
	addLogMSG(lidarName + "Lidar Dst");
}

void RLogger::outputLidarValues(Lidar & lidar) {
	addLogMSG(std::to_string(lidar.getAverage()));
	addLogMSG(std::to_string(lidar.getDistance()));
}

void RLogger::run() {
	//  After each Second it logs those values
	if (m_timer.Get() >= 1) {
		outputTalonValues(m_FRwheel);
		outputTalonValues(m_FLwheel);
		outputTalonValues(m_BRwheel);
		outputTalonValues(m_BLwheel);
//		outputTalonValues(m_topFlyWheel);
//		outputTalonValues(m_lowerFlyWheel);
		outputLidarValues(m_lidar);
		printLogMSG(m_stringValues);
		m_stringValues.clear();
		m_timer.Reset();
	}
}

void RLogger::addLogMSG(string values) {
	m_stringValues.push_back(values);
}

void RLogger::stop() {
	m_timer.Stop();
}

void RLogger::printLogMSG(std::list<std::string> &values) {
	std::list<std::string>::iterator iter;
	string msg;
	for (iter = values.begin(); iter!=values.end(); iter++) {

		msg = msg + (iter == values.begin() ? "" : ",") + *iter;
	}
	LOGI_(LoggerFiles::LogFile) << msg;
}

RLogger::~RLogger() {
	// TODO Auto-generated destructor stub
}

