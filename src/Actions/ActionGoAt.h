/*
 * ActionGoAt.h
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#ifndef SRC_ACTIONS_ACTIONGOAT_H_
#define SRC_ACTIONS_ACTIONGOAT_H_

#include "Action.h"
#include "../relativeMecanumDrivetrain.h"


class ActionGoAt: public Action
{
    public:
        ActionGoAt(relativeMecanumDrivetrain& driveTrain, double speed, double angle);
        virtual ~ActionGoAt();
        void init(void);
        bool execute(void);

    private:
        relativeMecanumDrivetrain& m_driveTrain;
        double m_speed;
        double m_angle;
};

#endif /* SRC_ACTIONS_ACTIONGOAT_H_ */
