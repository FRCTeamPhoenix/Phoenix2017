/*
 * GearHandler.h
 *
 *  Created on: Mar 13, 2017
 *      Author: joshc
 */

#include "WPILib.h"
#include "constants.h"

#ifndef SRC_GEARHANDLER_H_
#define SRC_GEARHANDLER_H_

class GearHandler {
public:
	GearHandler(DigitalInput & sensor);
	virtual ~GearHandler();
	bool getState();
	// Awating for other uses other than getting an input sensor


private:
	DigitalInput & m_sensor;

};

#endif /* SRC_GEARHANDLER_H_ */
