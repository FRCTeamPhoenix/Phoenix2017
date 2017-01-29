/*
 * JSONFile.h
 *
 *  Created on: Jan 29, 2017
 *      Author: cooli
 */

#ifndef SRC_JSONFILE_H_
#define SRC_JSONFILE_H_

#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class JSONFile
{
    public:
        JSONFile(string relativePath);
        virtual ~JSONFile();
        json get();
    private:
        json m_json;
};

#endif /* SRC_JSONFILE_H_ */
