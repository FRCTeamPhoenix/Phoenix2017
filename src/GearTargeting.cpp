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
    m_timer(),
    m_rotation(0),
    m_horizontal(0),
    m_forward(0)
{
};

GearTargeting::~GearTargeting(){

};

void GearTargeting::run(){
    //double rotation, horizontal, forward;
    //double speed = 0.2;
    std::stringstream dist;

    switch (m_state){
        case IDLE:
            dist << "IDLE";
            SmartDashboard::PutString("DB/String 5", dist.str());
            //Remove gears from jetson mode
            switch (m_comms.getMode()){
                //We could have neither mode run here
                case GEARS:
                    break;
                case BOTH:
                    m_comms.setMode(VisionMode::HIGH_GOAL);
                    break;
                default:
                    break;
            }

            break;
        case SEARCHING:
            dist << "SEARCHING";
            SmartDashboard::PutString("DB/String 5", dist.str());
            //Keep gears in jetson mode
            //if target found, switch to aligning
            if (getTargetFound()){
                m_state = ALIGNING;
            }
            break;
        case DISCONNECTED:
            dist << "DISCONNECTED";
            SmartDashboard::PutString("DB/String 5", dist.str());
            //Report error
            break;
        case ALIGNING:
            dist << "ALIGNING";
            SmartDashboard::PutString("DB/String 5", dist.str());
            /*//move according to getAngle and getDistance
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
            */

            /*rotation = getRotation();
            horizontal = getHorizontal();
            forward = getForward();
            

            if (rotation > 10){
               m_train.rotate(rotation, speed);
            }
            else if (horizontal > 2 || horizontal < -2){
                int angle = ((horizontal > 0) - (horizontal < 0)) * 90
                m_train.moveDistance(horizontal, angle);
            }
            else if (ver)
            */
            if (!getTargetFound()){
                m_state = SEARCHING;
            }
            else{
                //m_state = ROTATING;
                m_state = SHIFTING;

                //m_rotation = getRotation();
                //m_horizontal = getHorizontal();
                //m_forward = getForward();
                //m_train.moveDistance(0, 0, 0.3, m_rotation);
                //m_horizontal = getHorizontal();
                //m_forward = getForward();
                //int angle = ((m_horizontal >= 0) - (m_horizontal < 0)) * (-90);
                //m_train.moveDistance(fabs(m_horizontal) * 4000.0 / 12.0, angle, 0.1);
            }
            break;
        case ROTATING:
            dist << "ROTATING";
            SmartDashboard::PutString("DB/String 5", dist.str());

            if (getTargetFound()){
                m_rotation = getRotation();
                m_horizontal = getHorizontal();
                m_forward = getForward();
                m_train.moveDistance(0, 0, 0.3, m_rotation);
            }

            if (m_train.doneMove(0.05)){
                //m_state = SHIFTING;
                m_state = IDLE;
                if (getTargetFound()){
                    m_horizontal = getHorizontal();
                    m_forward = getForward();
                }
                //int angle = ((m_horizontal > 0) - (m_horizontal < 0)) * 90;
                //m_train.moveDistance(fabs(m_horizontal) * 4000.0 / 12.0, angle, speed);
            }
            break;
        case SHIFTING:
            dist << "SHIFTING";
            SmartDashboard::PutString("DB/String 5", dist.str());

            if (getTargetFound()){
                m_horizontal = getHorizontal();
                m_forward = getForward();
                int angle = ((m_horizontal >= 0) - (m_horizontal < 0)) * (-90);
                m_train.moveDistance(fabs(m_horizontal) * 4000.0 / 12.0, angle, 0.15);
            }

            if (m_train.doneMoveAbsolute(2.0)){
                m_state = IDLE;
//                m_state = APPROACHING;
//                if (getTargetFound()) {
//                    m_forward = getForward();
//                }
//                m_state = APPROACHING;
//                m_train.moveDistance(m_forward * 4000 / 12.0, 0, 0.15);
            }
            break;
        case APPROACHING:
            dist << "APPROACHING";
            SmartDashboard::PutString("DB/String 5", dist.str());
            if (m_train.doneMoveAbsolute(2.0)){
                m_state = DEPOSITING;
            }
            break;
        case DEPOSITING:
            dist << "DEPOSITING";
            SmartDashboard::PutString("DB/String 5", dist.str());
            //Do nothing, unless time is up (2 sec or so), then switch to idle and give control to next auto section
            if (m_timer.Get() > 2.0){
                m_state = IDLE;
            }
            break;
    }
}

void GearTargeting::setState(STATE state){
    m_state = state;
};

double GearTargeting::getRotation(){
    return m_comms.getNumber(JetsonComms::gearsRotation);
};

double GearTargeting::getHorizontal(){
    return m_comms.getNumber(JetsonComms::gearsHorizontal);
};

double GearTargeting::getForward(){
    return m_comms.getNumber(JetsonComms::gearsForward);
};

bool GearTargeting::getTargetFound(){
    return m_comms.getState(JetsonComms::gearState) == JetsonState::TARGET_FOUND;
};

