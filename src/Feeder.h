/*
 * Feeder.h
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#ifndef SRC_FEEDER_H_
#define SRC_FEEDER_H_
#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"

class Feeder
{
public:
    Feeder(SmartTalon* feederMotor, Joystick* gamepad);
    virtual ~Feeder();

    enum State
    {
        ON,
        OFF
    };

    State getState();
    void setState(State state);
    void run();

private:
    State m_state;
    SmartTalon* m_feederMotor;
    Joystick* m_gamepad;
};

#endif /* SRC_FEEDER_H_ */
