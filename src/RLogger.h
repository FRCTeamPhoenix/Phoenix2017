/*
 * RLogger.h
 *
 *  Created on: Feb 21, 2017
 *      Author: joshc
 */
#pragma once
#include "plog/Log.h"
#include "plog/Formatters/UndecoratedFormatter.h"
#include "WPILib.h"
#include "SmartTalon.h"
#include "Lidar.h"
#ifndef SRC_RLOGGER_H_
#define SRC_RLOGGER_H_



class RLogger {
public:
	RLogger(SmartTalon & FRwheel,
			SmartTalon & FLwheel,
			SmartTalon & BRwheel,
			SmartTalon & BLwheel,
//			SmartTalon & topFlyWheel,
//			SmartTalon & lowerFlyWheel,
			Lidar & lidar
	);
	virtual ~RLogger();
	void run();
	void stop();
	void outputTalonHeaders(string talonName); // Talon Header for the RLogger's CSV format of headers
	void outputTalonValues(SmartTalon & talon); // Talon Values for grabbing values of the encoders
	void outputLidarHeaders(string lidarName); // Lidar Header for RLogger's CSV format of headers
	void outputLidarValues(Lidar & lidar); // Lidar Values that is being processed
	void addLogMSG(string values); // Adds mesages to a List Array That you can grab
	void printLogMSG(std::list<std::string> &values); // Prints out the Message to the File

private:
	//	SmartTalon& m_topFlyWheel;
	//	SmartTalon& m_lowerFlyWheel;
	SmartTalon& m_FRwheel;
	SmartTalon& m_FLwheel;
	SmartTalon& m_BRwheel;
	SmartTalon& m_BLwheel;
	Lidar & m_lidar;
	Timer m_timer;

	std::list<std::string> m_stringValues;
	enum LoggerFiles
	{
		LogFile = 1
	};
};

#endif /* SRC_RLOGGER_H_ */
