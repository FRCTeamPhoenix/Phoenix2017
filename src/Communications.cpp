/*
 * Communications.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Ray
 */

#include "Communications.h"

Communications::Communications()
{
	m_table = NetworkTable::GetTable("datatable");
};

Communications::~Communications(){

};

float Communications::getAngle(){
    if (!m_table->ContainsKey("target_angle")) return 0;

	std::string angle_str = m_table->GetString("target_angle", "0;0");

	int semi_pos = angle_str.find_first_of(';');
	angle_str = angle_str.substr(semi_pos + 1);

	float angle = std::stof(angle_str);

	return angle;
};

long long int Communications::getAngleTimestamp(){
    if (!m_table->ContainsKey("target_angle")) return 0;

    std::string time_str = m_table->GetString("target_angle", "0;0");
    return getTimestamp(time_str);
};

JetsonState Communications::getState(){
    if (!m_table->ContainsKey("jetson_state")) return POWERED_OFF;

	std::string state_str = m_table->GetString("jetson_state", "0;4");

	int semi_pos = state_str.find_first_of(';');
	state_str = state_str.substr(semi_pos + 1);
	//std::cout << state_str << std::endl;



	int state_num = std::stoi(state_str);

	return JetsonState(state_num);

	/*switch (state_num){
		case 0://"Powered on":
			return JetsonState::POWERED_ON;
		case 1://"Camera error":
			return JetsonState::CAMERA_ERROR;
		case 2://"Target found":
			return JetsonState::TARGET_FOUND;
		case 3://"Target not found":
			return JetsonState::TARGET_NOT_FOUND;
		default:
			return JetsonState::POWERED_OFF;
	}
	return JetsonState::POWERED_OFF;*/
};

long long int Communications::getStateTimestamp(){
    if (!m_table->ContainsKey("jetson_state")) return 0;

    std::string time_str = m_table->GetString("jetson_state", "0;0");
    return getTimestamp(time_str);
};

long long int Communications::getTimestamp(std::string time_str){
    int semi_pos = time_str.find_first_of(';');
    time_str = time_str.substr(0, semi_pos);
    //std::cout << time_str << std::endl;
    long long int time = std::stoll(time_str);

    return time;
};






