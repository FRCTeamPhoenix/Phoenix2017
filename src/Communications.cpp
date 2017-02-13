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

    return (JetsonState) m_table->GetNumber(JetsonComms::stateId);
};

long long Communications::getStateTimestamp(){
    return getTimestampFor(JetsonComms::stateId);
};

bool Communications::setMode(VisionMode mode){
    return m_table->PutNumber(JetsonComms::modeId, mode);
};

float Communications::getNumber(std::string key){
    return  m_table->ContainsKey(key) ?
            m_table->GetNumber(key) :
            0;
};

bool Communications::setNumber(std::string key, float num){
    return m_table->GetNumber(key, num);
};

long long Communications::getTimestampFor(std::string key){
    key += "_time";

    return m_table->ContainsKey(key) ?
            m_table->GetNumber(key) :
            0;
};
