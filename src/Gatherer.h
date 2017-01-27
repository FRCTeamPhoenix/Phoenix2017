/*
 * Gatherer.h
 *
 *  Created on: Jan 14, 2017
 *      Author: cbadu
 */

#ifndef SRC_Gatherer_H_
#define SRC_Gatherer_H_
#include "WPILib.h"
#include "constants.h"

class Gatherer
{
    public:
        Gatherer(Talon* GathererMotor, Joystick* gamepad);
        virtual ~Gatherer();

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
        Talon*  m_GathererMotor;
        Joystick* m_gamepad;
};

#endif /* SRC_Gatherer_H_ */
