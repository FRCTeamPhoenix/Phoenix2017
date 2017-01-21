/*
 * RobotJSON.h
 *
 *  Created on: Jan 21, 2017
 *      Author: cooli
 */

#ifndef SRC_ROBOTJSON_H_
#define SRC_ROBOTJSON_H_

#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class RobotJSON
{
    public:
        RobotJSON(string path);
        virtual ~RobotJSON();
        json getJSON();
    private:
        json m_json;
};

#endif /* SRC_ROBOTJSON_H_ */
