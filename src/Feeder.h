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

class Feeder
{
    public:
        Feeder(Talon* FeederMotor, Joystick* gamepad);
        virtual ~Feeder();

        enum state
        {
            ON,
            OFF
        };

        void run();
        void start();
        void stop();

    private:
        state m_state;
        Talon* m_FeederMotor;
        Joystick* m_gamepad;
};

#endif /* SRC_FEEDER_H_ */
