/*
 * Communications.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Ray
 */

#include "Communications.h"

Communications::Communications()
{
	m_table = NetworkTable::GetTable(JetsonComms::tableName);
};

Communications::~Communications(){

};


JetsonState Communications::getState(){
    if (!m_table->ContainsKey(JetsonComms::stateId))
        return JetsonState::POWERED_OFF;

    return (JetsonState) (int) m_table->GetNumber(JetsonComms::stateId, 4);
};

long long Communications::getStateTimestamp(){
    return getTimestampFor(JetsonComms::stateId);
};

VisionMode Communications::getMode(){
    return (VisionMode) (int) m_table->GetNumber(JetsonComms::modeId, VisionMode::NOT_YET_SET);
};

bool Communications::setMode(VisionMode mode){
    return m_table->PutNumber(JetsonComms::modeId, mode);
};

double Communications::getNumber(std::string key){
    return  m_table->ContainsKey(key) ?
            m_table->GetNumber(key, 0) :
            0;
};

bool Communications::setNumber(std::string key, double num){
    return m_table->PutNumber(key, num);
};

long long Communications::getTimestampFor(std::string key){
    key += "_time";

    return m_table->ContainsKey(key) ?
            m_table->GetNumber(key, 0) :
            0;
};
