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

class Indexer
{
    public:
        Indexer(Talon* IndexerMotor, Joystick* gamepad);
        virtual ~Indexer();

        enum state
        {
            ON,
            OFF,
            QuarterTurn
        };

        void run();
        void start();
        void stop();

    private:
        state m_state;
        Talon* m_IndexerMotor;
        Joystick* m_gamepad;
};

#endif /* SRC_INDEXER_H_ */
