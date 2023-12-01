#include "aed.h"


// Constructor
AED::AED() : QObject()
{
    deviceStatus = 0;
    batteryLevel = 100;
    isAdultPad1Applied = 0;
    isAdultPad2Applied = 0;
    isChildPad1Applied = 0;
    isChildPad2Applied = 0;
    chargeDeliveredCount = 0;
    qInfo("The AED object has been created."); // This line can be removed for the submission
    updateBatteryStatus();
}

// Destructor
AED::~AED()
{
    if(patient == nullptr)
    {
        delete patient;
    }
}

// Getters
bool AED::getDeviceStatus()
{
    return deviceStatus;
}

int AED::getBatteryLevel(){
    return batteryLevel;
}

void AED::getPadsStatus()
{

    if(patient->getIsAdult())
    {
        if(isChildPad1Applied || isChildPad2Applied)
        {
            qInfo("AED: Please remove the child pads from the adult patient.");
        }
        else if(isAdultPad1Applied && isAdultPad2Applied)
        {
            monitorHeart();
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
            monitorHeart();
        }
    }
}

// Setters
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
    qInfo("AED: Turned OFF.");
    qInfo("The pads have been removed.");
}

void AED::setPadsStatus(bool adultPad1status, bool adultPad2status, bool childPad1status, bool childPad2status)
{
    isAdultPad1Applied = adultPad1status;
    isAdultPad2Applied = adultPad2status;
    isChildPad1Applied = childPad1status;
    isChildPad2Applied = childPad2status;

    QTimer::singleShot(500, this, &AED::getPadsStatus); //Delay calling getPadsStatus to give enough time to update the UI, as 2nd CheckBox would not appear to be checked otherwise.


}

// Main functions of the AED cycle
void AED::monitorHeart()
{
    qInfo("AED: Monitoring the patient's health...");
    QThread::sleep(3);
    switch(patient->getStatus())
    {
    case 0:
        qInfo("AED: The patient has flatlined.");
        break;
    case 1:
        qInfo("AED: The patient is stable.");
        break;
    case 2:
        qInfo("AED: The patient is in V-FIB.");
        cprFeedback();
        break;
    case 3:
        qInfo("AED: The patient is in V-Tach.");
        cprFeedback();
        break;
    }
}

void AED::cprFeedback()
{
    // need to do cpr before delivering a shock
    deliverShock();
}

void AED::deliverShock()
{
    int chargeNeeded = 20;
    if(batteryLevel < chargeNeeded)
    {
        qInfo("AED: Not enough battery power left to deliver a shock!");
        return;
    }

    qInfo("AED: Shock advised! Stand clear from the patient!");
    QThread::sleep(1);
    qInfo("AED: Delivering shock in 3");
    QThread::sleep(1);
    qInfo("AED: 2");
    QThread::sleep(1);
    qInfo("AED: 1");
    QThread::sleep(1);
    qInfo("AED: Delivering shock!");

    batteryLevel -= 20;
    updateBatteryStatus();

    chargeDeliveredCount += 1;
    monitorHeart();
}

//Battery Signal

void AED::updateBatteryStatus(){
    int newLevel = getBatteryLevel();
    // Emit the signal to notify about the battery level change
    emit batteryLevelChanged(newLevel);
}


// Other
void AED::createPatient(bool isAdult, int status)
{
    patient = new Patient(isAdult, status);
}
