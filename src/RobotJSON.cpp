/*
 * RobotJSON.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: cooli
 */

#include <RobotJSON.h>

RobotJSON::RobotJSON(string path)
{
    ifstream i;
    i.open("/home/lvuser/" + path);
    i >> m_json;
    i.close();
}

json RobotJSON::getJSON() {
    return m_json;
}

RobotJSON::~RobotJSON()
{
    // TODO Auto-generated destructor stub
}

