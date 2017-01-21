/*
 * ActionGoDistance.h
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#ifndef SRC_ACTIONS_ACTIONGODISTANCE_H_
#define SRC_ACTIONS_ACTIONGODISTANCE_H_

#include "Action.h"
#include "../relativeMecanumDrivetrain.h"

class ActionGoDistance: public Action
{
    public:
        ActionGoDistance(relativeMecanumDrivetrain& driveTrain, double distance, double angle, double speed);
        virtual ~ActionGoDistance();
        void init(void);
        bool execute(void);

    private:
        relativeMecanumDrivetrain& m_driveTrain;
        double m_distance;
        double m_angle;
        double m_speed;
};

#endif /* SRC_ACTIONS_ACTIONGODISTANCE_H_ */
