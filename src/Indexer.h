/*
 * Indexer.h
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#ifndef SRC_INDEXER_H_
#define SRC_INDEXER_H_
#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"

//#include "Actions/AllActions.h"

class Indexer
{
public:
    Indexer(SmartTalon& indexerMotor, Joystick& gamepad);
    virtual ~Indexer();

    enum State {
        TELEOP,
        ON,
        OFF
    };

    //true is TELEOP, false is AUTO
    State getState();
    void setState(State state);
    void run();

    void setSpeed(double speed);

private:
    State m_state;
    SmartTalon& m_indexerMotor;
    Joystick& m_gamepad;
    double m_speed;
};

#endif /* SRC_INDEXER_H_ */
