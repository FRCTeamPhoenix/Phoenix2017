/*
 * JSONFile.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: cooli
 */

#include <JSONFile.h>

JSONFile::JSONFile(string relativePath)
{
    ifstream i;
    i.open("/home/lvuser/" + relativePath);
    i >> m_json;
    i.close();
}

json JSONFile::get()
{
    return m_json;
}

JSONFile::~JSONFile()
{
    // TODO Auto-generated destructor stub
}

