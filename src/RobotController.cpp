/*
 * Shooter.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "RobotController.h"

RobotController::RobotController(
        FlyWheels& flywheel,
        Turret& turret,
        Feeder& feeder,
        Indexer& indexer,
        Joystick& customBox,
        Climber& climber,
        Gatherer& gatherer):

        m_flywheels(flywheel),
        m_turret(turret),
        m_feeder(feeder),
        m_indexer(indexer),
        m_controlBox(customBox),
        m_climber(climber),
        m_gatherer(gatherer)

{
    m_state = TELEOP;
}

RobotController::~RobotController()
{

}

void RobotController::run()
{
    //Run functions of FlyWheels and Turret
    m_flywheels.run();
    m_turret.run();
    m_feeder.run();
    m_indexer.run();
//    m_gatherer.run();
    m_climber.run();

    switch(m_state){


    /*
     * Controls:
     * Button A held: Feeder and Flywheels on, flywheels at joystick rate or lidar rate
     * Button B pressed: turret auto on
     * Button X pressed: turret auto off
     * Button Y held: indexer on
     * Button LB held: climber on
     * Button RB held: Gatherer on
     * Gamepad left joystick: turret Control
     */
    case TELEOP:


        //Flywheels and Feeder
        if(m_controlBox.GetRawButton(DriveStationConstants::buttonFeeder)){
            m_feeder.setState(Feeder::ON);
        }
		else{
            m_feeder.setState(Feeder::OFF);
		}
        if(m_controlBox.GetRawButton(DriveStationConstants::buttonFlywheelAuto))
        {
            m_flywheels.setState(FlyWheels::LIDARRATE); //TODO set to lidarRate when lidar tuning is done
        }
        else if(m_controlBox.GetRawButton(DriveStationConstants::buttonFlywheelManual))
        {
            m_flywheels.setState(FlyWheels::JOYSTICKRATE); //TODO set to lidarRate when lidar tuning is done
        }
        else
        {
            m_flywheels.setState(FlyWheels::OFF); //TODO set to lidarRate when lidar tuning is done
        }

        //Turret
        if (m_controlBox.GetRawButton(DriveStationConstants::buttonAutoStart)){
            m_turret.setState(Turret::AUTO);
        }
        else if (m_controlBox.GetRawButton(DriveStationConstants::buttonAutoStop))
        {
            m_turret.setState(Turret::IDLE);
        }

        //Indexer
//        if((m_flywheels.getState() == FlyWheels::LIDARRATE) && (!m_flywheels.inRange()))
//        {
//            m_indexer.setState(Indexer::OFF);
//
//        }
//        else
//        {
        if(m_controlBox.GetRawButton(DriveStationConstants::buttonIndexer)){
            m_indexer.setState(Indexer::ON);
            m_indexer.setSpeed(0.3);
        }
        else if(m_controlBox.GetRawButton(7))
        {
            m_indexer.setState(Indexer::ON);
            m_indexer.setSpeed(-0.3);
        }
        else{
            m_indexer.setState(Indexer::OFF);
        }
//        }





        //Climber
        if(m_controlBox.GetRawButton(DriveStationConstants::buttonClimberUP)){
            m_climber.setState(Climber::ON);
        }
        else{
            m_climber.setState(Climber::OFF);
        }

        //Gatherer
        if(m_controlBox.GetRawButton(DriveStationConstants::buttonRB)){
            m_gatherer.setState(Gatherer::ON);
        }
        else{
            m_gatherer.setState(Gatherer::OFF);
        }
        break;
    case AUTO:
        break;

    }

}

//Gets the current state of the ShooterController state machine
RobotController::STATE RobotController::getState()
{
    return m_state;
}

//Sets the state when there is a change in the ShooterController state machine
void RobotController::setState(STATE state)
{
    m_state = state;
}
