/*
 * GearHandler.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: joshc
 */

#include <GearHandler.h>

GearHandler::GearHandler(DigitalInput & sensor):
m_sensor(sensor)
{
	// TODO Auto-generated constructor stub

}

bool GearHandler::getState() {
	return m_sensor.Get();
}

GearHandler::~GearHandler() {
	// TODO Auto-generated destructor stub
}

