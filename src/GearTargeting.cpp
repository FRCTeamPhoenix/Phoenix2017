/*
 * GearTargeting.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Ray
 */

#include "GearTargeting.h"

GearTargeting::GearTargeting(Communications& comms, relativeMecanumDrivetrain& train):
    m_state(IDLE),
    m_comms(comms),
    m_train(train),
    m_timer()
{
};

GearTargeting::~GearTargeting(){

};

void GearTargeting::run(){
    double angle, distance, threshold;

    switch (m_state){
        case IDLE:
            //Remove gears from jetson mode
            switch (m_comms.getMode()){
                //We could have neither mode run here
                case GEARS:
                    break;
                case BOTH:
                    m_comms.setMode(VisionMode::HIGH_GOAL);
                default:
                    break;
            }

            break;
        case SEARCHING:
            //Keep gears in jetson mode
            //if target found, switch to aligning
            if (getTargetFound()){
                m_state = ALIGNING;
            }
            break;
        case DISCONNECTED:
            //Report error
            break;
        case ALIGNING:
            //move according to getAngle and getDistance
            //Don't rotate all the way, or we will end up skewed relative to the target.
            angle = getAngle();
            distance = getDistance();

            //If we are close enough, switch to depositing
            threshold = 10.0;// Make into an instance variable
            if (distance < threshold){
                m_timer.Reset();
                m_state = DEPOSITING;
            }

            //Make an instance variable for speed
            m_train.moveDistance(distance, angle, 0.1);

            if (!getTargetFound()){
                m_state = SEARCHING;
            }
            break;
        case DEPOSITING:
            //Do nothing, unless time is up (2 sec or so), then switch to idle and give control to next auto section
            if (m_timer.Get() > 2000){
                m_state = IDLE;
            }
            break;
    }
}

double GearTargeting::getAngle(){
    return m_comms.getNumber(JetsonComms::gearAngleId);
};

double GearTargeting::getDistance(){
    return m_comms.getNumber(JetsonComms::gearDistanceId);
};

bool GearTargeting::getTargetFound(){
    return m_comms.getState() == JetsonState::TARGET_FOUND;
};

