#include "aed.h"

AED::AED()
{
    deviceStatus = 0;
    isAdultPad1Applied = 0;
    isAdultPad2Applied = 0;
    isChildPad1Applied = 0;
    isChildPad2Applied = 0;
    chargeDeliveredCount = 0;
    qInfo("The AED object has been created."); // This line can be removed for the submission
}

AED::~AED()
{
    if(patient == nullptr)
    {
        delete patient;
    }
}

void AED::createPatient(bool isAdult, int status)
{
    patient = new Patient(isAdult, status);
}

bool AED::getDeviceStatus()
{
    return deviceStatus;
}

void AED::setDeviceOn()
{
    deviceStatus = 1;
    qInfo("AED: Turned ON.");
    qInfo("AED: Initiating self-test...");
    QThread::sleep(3);
    qInfo("AED: Now operational.");
    qInfo("AED: Please place the set of electrode pads on the patient's bare chest.");
}

void AED::setDeviceOff()
{
    deviceStatus = 0;
    qInfo("The AED has turned OFF.");
}

void AED::checkIfPadsAreOn()
{
    if(patient->getIsAdult())
    {
        if(isChildPad1Applied || isChildPad2Applied)
        {
            qInfo("AED: Please remove the child pads from the adult patient.");
        }
        else if(isAdultPad1Applied && isAdultPad2Applied)
        {
            qInfo("Next sequence in progress"); // to replace with the next function
        }
    }
    else
    {
        if(isAdultPad1Applied || isAdultPad2Applied)
        {
            qInfo("AED: Please remove the adult pads from the child patient.");
        }
        else if(isChildPad1Applied && isChildPad2Applied)
        {
            qInfo("Next sequence in progress"); // to replace with the next function
        }
    }
}

void AED::setPadsStatus(bool adultPad1status, bool adultPad2status, bool childPad1status, bool childPad2status)
{
    isAdultPad1Applied = adultPad1status;
    isAdultPad2Applied = adultPad2status;
    isChildPad1Applied = childPad1status;
    isChildPad2Applied = childPad2status;
    checkIfPadsAreOn();
}

void AED::monitorHeart()
{

}

void AED::deliverShock()
{

}

void AED::cprFeedback()
{

}
