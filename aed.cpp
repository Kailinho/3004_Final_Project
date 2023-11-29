#include "aed.h"

AED::AED()
{
    deviceStatus = 0;
    areAdultPadsApplied = 0;
    areChildPadsApplied = 0;
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

}

void AED::setDeviceOff()
{
    deviceStatus = 0;
    qInfo("The AED has turned OFF.");
}

void AED::createPatient(QString name, int age)
{
    patient = new Patient(name, age);
}

void AED::setAdultPads()
{

}

void AED::setChildPads()
{

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
