/*
 * Communications.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Ray
 */

#ifndef SRC_COMMUNICATIONS_H_
#define SRC_COMMUNICATIONS_H_

#include <string>
#include "WPILib.h"


enum JetsonState {
	POWERED_ON,
	CAMERA_ERROR,
	TARGET_FOUND,
	TARGET_NOT_FOUND,
	POWERED_OFF
};


class Communications {
public:
	Communications();
	~Communications();

	JetsonState getState();
	long long int getStateTimestamp();

	float getAngle();
	long long int getAngleTimestamp();

private:

	long long getTimestamp(std::string);

	std::shared_ptr<NetworkTable> m_table;

};


#endif /* SRC_COMMUNICATIONS_H_ */
