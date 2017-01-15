/*
 * ActionRotate.h
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#ifndef SRC_ACTIONS_ACTIONROTATE_H_
#define SRC_ACTIONS_ACTIONROTATE_H_

#include <Actions/Action.h>

class ActionRotate: public Action
{
    public:
        ActionRotate(relativeMecanumDrivetrain * driveTrain, double speed, double angle);
        void init(void);
        bool execute(void);
        virtual ~ActionRotate();

    private:
        relativeMecanumDrivetrain * m_driveTrain;
        double m_angle;
        double m_speed;
};

#endif /* SRC_ACTIONS_ACTIONROTATE_H_ */
