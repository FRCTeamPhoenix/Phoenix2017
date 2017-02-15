//
// Created by William Gebhardt on 10/27/16.
//

#include "SmartTalon.h"

SmartTalon::SmartTalon (int deviceNumber, FeedbackDevice device) :
    CANTalon(deviceNumber),
    m_goal(0),
    m_tuneTimer(),
    m_distanceGains(),
    m_speedGains()


{
    SetFeedbackDevice(device);
    stringstream ss;
    ss << deviceNumber;
    string deviceNumberStr = ss.str();

	ifstream json_file;
	json_file.open("/home/lvuser/config/talons.json");
	json talons;
	json_file >> talons;
	json_file.close();
	m_distanceGains.set (talons[deviceNumberStr]["distance"]["p"],
                         talons[deviceNumberStr]["distance"]["i"],
                         talons[deviceNumberStr]["distance"]["d"],
                         talons[deviceNumberStr]["distance"]["izone"],
                         talons[deviceNumberStr]["distance"]["ff"]);

	m_speedGains.set (talons[deviceNumberStr]["speed"]["p"],
                      talons[deviceNumberStr]["speed"]["i"],
                      talons[deviceNumberStr]["speed"]["d"],
                      talons[deviceNumberStr]["speed"]["izone"],
                      talons[deviceNumberStr]["speed"]["ff"]);

	m_maxForwardSpeed = talons[deviceNumberStr]["maxfvel"];
	m_maxReverseSpeed = talons[deviceNumberStr]["maxrvel"];

//    m_inverted = true;
    m_inverted = talons[deviceNumberStr]["inverted"];

	SetSafetyEnabled(false);
}

double SmartTalon::getGoal ()
{
	return m_goal;
}

void SmartTalon::switchToGain (PIDGains gains)
{
	SetP (gains.getP ());
	SetI (gains.getI ());
	SetD (gains.getD ());
	SetIzone (gains.getIZone ());
	SetF (gains.getFeedForward ());
}

void SmartTalon::goTo (double position, double speed)
{
    switchToGain (m_distanceGains);
    SetControlMode (CANSpeedController::kPosition);
	ConfigMaxOutputVoltage(speed * 12);
    if(m_inverted)
	    Set (-position);
    else
        Set (position);

}

void SmartTalon::goAt (double speed)
{
    speed = (speed > 1) ? 1 : speed;
    speed = (speed < -1) ? -1 : speed;

    speed = (speed > 0) ? speed * m_maxForwardSpeed : speed * m_maxReverseSpeed;

    switchToGain (m_speedGains);
	SetControlMode (CANSpeedController::kSpeed);
	ConfigMaxOutputVoltage(12);
//	SetEncPosition(0);
    if(m_inverted)
        SetSetpoint(-speed);
    else
        SetSetpoint(speed);


}

void SmartTalon::goDistance (double distance, double speed)
{

    double cPos = GetPosition ();

    double fPos = cPos + distance;

    switchToGain (m_distanceGains);
    SetControlMode (CANSpeedController::kPosition);
    ConfigMaxOutputVoltage(12 * speed);
    //SetEncPosition(0);
	//Set(0);
    if(m_inverted)
        SetSetpoint(-fPos);
    else
        SetSetpoint(fPos);

}

/*
 * DO NOT CALL IN ANY CASE WHERE YOU NEED ROBOT CONTROL
 * TAKES CONTROL OF SYSTEM AND DOES NOT RETURN IT TILL DONE
 */
void SmartTalon::tunePosition (double pInit, double tuneDistance, double F)
{
	SmartDashboard::PutString ("DB/String 5", "Not Tuned");
	double speed = GetSpeed ();
	while(speed < -0.01 || speed > 0.01){
		speed = GetSpeed ();
	}

	SetP (pInit);
	SetI (0);
	SetD (0);
	SetF (F);
	bool notTuned = true;
	bool ocillation = false;

	while(notTuned){
		SetControlMode (CANSpeedController::kPosition);
		SetPosition (0.0);
		Set(tuneDistance);
		tuneDistance *= -1;

		m_tuneTimer.Reset ();
		m_tuneTimer.Start ();

		bool forward = true;
		int changeCount = 0;

		//        Wait(2);
		std::ostringstream outputP;
		outputP << "P: ";
		outputP << (GetP ());
		SmartDashboard::PutString("DB/String 2", outputP.str());

		std::ostringstream outputD;
		outputD << "D: ";
		outputD << (GetD ());
		SmartDashboard::PutString("DB/String 3", outputD.str());

		while (m_tuneTimer.Get () < 5)
		{
			speed = GetSpeed ();
			if(speed > 0 && !forward)
			{
				changeCount++;
			}

			if(speed < 0 && forward)
			{
				changeCount++;
			}

			forward = speed > 0;

			Wait(0.1);
			std::ostringstream outputL;
			outputL << "Time: ";
			outputL << (5 - m_tuneTimer.Get ());
			SmartDashboard::PutString("DB/String 0", outputL.str());

			std::ostringstream outputO;
			outputO << "Occilation: ";
			outputO << (changeCount);
			SmartDashboard::PutString("DB/String 1", outputO.str());
		}

		m_tuneTimer.Stop ();

		if (changeCount <= 15  && !ocillation)
		{
			SetP (GetP () + 0.1 * pInit);
		}
		else if (changeCount > 1)
		{
			ocillation = true;
			SetD (GetD () + GetP ());
		}
		else
		{
			notTuned = false;
		}
	}
	SmartDashboard::PutString ("DB/String 5", "Tuned");

	m_distanceGains.set (GetP(), GetI (), GetD (), 0, GetF ());

	return;
}



//Still in development dont call
void SmartTalon::tuneRate (double pInit, double goalRate, int IZone, double F)
{
	SmartDashboard::PutString ("DB/String 3", "Not Tuned");
	double speed = GetSpeed ();
	while(speed < -0.01 || speed > 0.01){
		speed = GetSpeed ();
	}

	SetP (pInit);
	SetI (0);
	SetD (0);
	SetF (F);
	SetIzone (IZone);

	int phase = 1;
	bool notTuned = true;

	SetControlMode (CANSpeedController::kSpeed);


	while (notTuned)
	{
		std::ostringstream outputG;
		outputG << "Goal Speed: ";
		outputG << (goalRate);
		SmartDashboard::PutString("DB/String 5", outputG.str());

		std::ostringstream outputP;
		outputP << "P: ";
		outputP << (GetP ());
		SmartDashboard::PutString("DB/String 1", outputP.str());

		std::ostringstream outputD;
		outputD << "I: ";
		outputD << (GetI ());
		SmartDashboard::PutString("DB/String 2", outputD.str());

		std::ostringstream outputPhase;
		outputPhase << "Phase: ";
		outputPhase << (phase);
		SmartDashboard::PutString("DB/String 4", outputPhase.str());

		int sum = 0;
		int count = 0;
		double avgSpeed = 0;
		double maxSpeed = 0;

		if (phase == 1)
		{




			Wait(.5);
			m_tuneTimer.Reset ();
			m_tuneTimer.Start ();

			Set(goalRate);
			while (m_tuneTimer.Get () < 3)
			{
				speed = GetSpeed ();

				maxSpeed = (speed > maxSpeed) ? speed : maxSpeed;

				Wait(0.1);
				std::ostringstream outputL;
				outputL << "Time: ";
				outputL << (3 - m_tuneTimer.Get ());
				SmartDashboard::PutString("DB/String 0", outputL.str());

				std::ostringstream outputO;
				outputO << "Max Speed: ";
				outputO << (maxSpeed);
				SmartDashboard::PutString("DB/String 6", outputO.str());

				std::ostringstream outputA;
				outputA << "AVG Speed: ";
				outputA << (avgSpeed);
				SmartDashboard::PutString("DB/String 7", outputA.str());

				std::ostringstream outputC;
				outputC << "Current Speed: ";
				outputC << (speed);
				SmartDashboard::PutString("DB/String 8", outputC.str());

				sum += speed;
				count ++;
				avgSpeed = sum / count;
			}

			m_tuneTimer.Stop ();


			Set(0);

			if (maxSpeed > fabs(1.2 * goalRate))
				phase = 2;
			else
				SetP (GetP () + 0.05 * pInit);

		}
		else if(phase == 2)
		{
			Wait (5);

			m_tuneTimer.Reset ();
			m_tuneTimer.Start ();

			Set(goalRate);
			while (m_tuneTimer.Get () < 5)
			{
				speed = GetSpeed ();

				maxSpeed = (speed > maxSpeed) ? speed : maxSpeed;

				Wait(0.1);
				std::ostringstream outputL;
				outputL << "Time: ";
				outputL << (5 - m_tuneTimer.Get ());
				SmartDashboard::PutString("DB/String 0", outputL.str());

				std::ostringstream outputO;
				outputO << "Max Speed: ";
				outputO << (maxSpeed);
				SmartDashboard::PutString("DB/String 6", outputO.str());

				std::ostringstream outputA;
				outputA << "AVG Speed: ";
				outputA << (avgSpeed);
				SmartDashboard::PutString("DB/String 7", outputA.str());

				std::ostringstream outputC;
				outputC << "Current Speed: ";
				outputC << (speed);
				SmartDashboard::PutString("DB/String 8", outputC.str());

				sum += speed;
				count ++;
				avgSpeed = sum / count;
			}

			m_tuneTimer.Stop ();

			Set(0);

			if (avgSpeed > fabs (0.9 * goalRate))
			{
				phase = 3;
			}
			else
			{
				SetI (GetI () + GetP() * 0.00001);
			}
		}
		else if(phase == 3)
		{
			SetP (GetP () * 0.8);

			std::ostringstream outputP;
			outputP << "P: ";
			outputP << (GetP ());
			SmartDashboard::PutString("DB/String 1", outputP.str());

			std::ostringstream outputD;
			outputD << "I: ";
			outputD << (GetI ());
			SmartDashboard::PutString("DB/String 2", outputD.str());

			Wait(5);

			m_tuneTimer.Reset ();
			m_tuneTimer.Start ();

			Set(goalRate);

			while (m_tuneTimer.Get () < 5)
			{
				speed = GetSpeed ();

				maxSpeed = (speed > maxSpeed) ? speed : maxSpeed;

				Wait(0.1);
				std::ostringstream outputL;
				outputL << "Time: ";
				outputL << (5 - m_tuneTimer.Get ());
				SmartDashboard::PutString("DB/String 0", outputL.str());

				std::ostringstream outputO;
				outputO << "Max Speed: ";
				outputO << (maxSpeed);
				SmartDashboard::PutString("DB/String 6", outputO.str());

				std::ostringstream outputA;
				outputA << "AVG Speed: ";
				outputA << (avgSpeed);
				SmartDashboard::PutString("DB/String 7", outputA.str());

				std::ostringstream outputC;
				outputC << "Current Speed: ";
				outputC << (speed);
				SmartDashboard::PutString("DB/String 8", outputC.str());

				sum += speed;
				count ++;
				avgSpeed = sum / count;
			}

			m_tuneTimer.Stop ();

			Set(0);
			notTuned = false;
		}
	}

	m_speedGains.set (GetP(), GetI (), GetD (), GetIzone (), GetF ());

	SmartDashboard::PutString ("DB/String 3", "Tuned");
	return;


}














































