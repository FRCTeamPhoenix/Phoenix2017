/*
 * GearTargeting.h
 *
 *  Created on: Feb 21, 2017
 *      Author: Ray
 */

#ifndef SRC_GEARTARGETING_H_
#define SRC_GEARTARGETING_H_


#include "relativeMecanumDrivetrain.h"
#include "Communications.h"

#include "constants.h"



class GearTargeting {
public:
    enum STATE {
        IDLE,
        SEARCHING,
        DISCONNECTED,
        ALIGNING,
        ROTATING,
        SHIFTING,
        APPROACHING,
        DEPOSITING
    };

    GearTargeting(Communications& comms, relativeMecanumDrivetrain& train);
    ~GearTargeting();

    void run();

private:
    STATE m_state;
    Communications& m_comms;
    relativeMecanumDrivetrain& m_train;

    Timer m_timer;

    double m_rotation, m_horizontal, m_forward;

    double getRotation();
    double getHorizontal();
    double getForward();
    bool getTargetFound();
};


#endif /* SRC_GEARTARGETING_H_ */
