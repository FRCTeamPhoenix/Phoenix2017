//
// Created by William Gebhardt on 1/15/17.
//

#ifndef PHOENIX2017_ACTIONMOTORDONEDISTANCE_H
#define PHOENIX2017_ACTIONMOTORDONEDISTANCE_H

#include "Action.h"
#include "../relativeMecanumDrivetrain.h"

class ActionMotorDoneDistance : public Action
{
public:
    ActionMotorDoneDistance(relativeMecanumDrivetrain& driveTrain, int allowedError);
    void init(void);
    bool execute(void);
    virtual ~ActionMotorDoneDistance();

private:
    relativeMecanumDrivetrain& m_driveTrain;
    int m_allowedError;
};


#endif //PHOENIX2017_ACTIONMOTORDONEDISTANCE_H
