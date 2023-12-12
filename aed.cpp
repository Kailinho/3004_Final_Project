
#include "aed.h"
#include "CPR.h"

#define DEAD 0
#define STABLE 1
#define V_FIB 2
#define V_TACH 3

AED::AED(QObject *parent) : QObject(parent){
    isOn = false;
    adultPads = qMakePair(false, false);
    childPads = qMakePair(false, false);
    batteryLevel = 100;
    shockCount = 0;

    qInfo("The AED object has been created."); // This line can be removed for the submission
}

AED::~AED(){
    if(patient == nullptr)
    {
        delete patient;
    }
}

// Getters
bool AED::getPower(){
    return isOn;
}

int AED::getBatteryLevel(){
    return batteryLevel;
}

// Setters

void AED::togglePower(){
    if(isOn){
        isOn = false;
        batteryLevel = 100;
        shockCount = 0;
        emit shockCountChanged(shockCount);
        emit displayHRSignal(6);
        qInfo("The AED has turned OFF.");
    } else {
        isOn = true;
        emit batteryLevelChanged(batteryLevel);
        qInfo("AED: INITIATING SELF TEST");
        QThread::sleep(3);
        qInfo("AED: UNIT OK");
        QThread::sleep(1);

        //Pre-CPR Procedure (We might not need this, could remove)
        qInfo("AED: STAY CALM");
        QThread::sleep(1);
        qInfo("AED: CHECK RESPONSIVENESS");
        QThread::sleep(1);
        qInfo("AED: CALL FOR HELP");
        QThread::sleep(1);

        qInfo("AED: ATTACH DEFIB PADS TO PATIENT’S BARE CHEST.");
        QThread::sleep(1);
    }
}

void AED::setPadsStatus(bool adultPad1, bool adultPad2, bool childPad1, bool childPad2){
    adultPads = qMakePair(adultPad1, adultPad2);
    childPads = qMakePair(childPad1, childPad2);
    QTimer::singleShot(500, this, &AED::checkPads);
}

void AED::checkPads(){
    if(patient->getIsAdult()){
        if(childPads.first || childPads.second){
            qInfo("AED: CHECK ELECTRODE PADS");
        }
        else if(adultPads.first && adultPads.second){
            qInfo("AED: ADULT PADS");
            QThread::sleep(1);
            monitorHeart();
        }
    }
    else
    {
        if(adultPads.first || adultPads.second){
            qInfo("AED: CHECK ELECTRODE PADS");
        }
        else if(childPads.first && childPads.second){
            qInfo("AED: PEDIATRIC PADS");
            QThread::sleep(1);
            monitorHeart();
        }
    }
}

void AED::monitorHeart(){
    qInfo("AED: DON’T TOUCH PATIENT, ANALYZING");
    QThread::sleep(3);
    switch(patient->getStatus()){
    case DEAD:
        emit displayHRSignal(1);
        qInfo("AED: The patient has flatlined."); //Might change
        break;
    case STABLE:
        emit displayHRSignal(2);
        qInfo("AED: PATIENT STABLE");
        break;
    case V_FIB:
        emit displayHRSignal(3);
        QCoreApplication::processEvents();
        qInfo("Graph: The patient is in V-FIB.");
        QThread::sleep(1);
        qInfo("AED: SHOCK ADVISED");
        QThread::sleep(1);
        deliverShock();
        break;
    case V_TACH:
        emit displayHRSignal(4);
        QCoreApplication::processEvents();
        qInfo("Graph: The patient is in V-Tach.");
        QThread::sleep(1);
        qInfo("AED: SHOCK ADVISED");
        QThread::sleep(1);
        deliverShock();
        break;
    }
}

void AED::deliverShock(){
    int chargeNeeded = 20;
    if (batteryLevel < chargeNeeded*2 && batteryLevel > chargeNeeded) {
        qInfo("AED: Low Battery Warning. This is the last shock the AED can generate before the batteries are replaced.");
    }
    if(batteryLevel < chargeNeeded) {
        qInfo("AED: CHANGE BATTERIES");
        return;
    }

    qInfo("AED: STAND CLEAR");
    QThread::sleep(1);
    qInfo("AED: SHOCK WILL BE DELIVERED IN THREE");
    QThread::sleep(1);
    qInfo("AED: TWO");
    QThread::sleep(1);
    qInfo("AED: ONE");
    QThread::sleep(1);
    qInfo("AED: SHOCK DELIVERED");

    batteryLevel -= chargeNeeded;
    emit batteryLevelChanged(batteryLevel);

    shockCount += 1;
    emit shockCountChanged(shockCount);
    cprFeedback(10000);// The real default time is 2 minutes - be sure the TA marking us knows we shortened the time for testing purposes
}

void AED::cprFeedback(int duration){
    emit enableButton(true);
    QCoreApplication::processEvents();
    switch(startCPR(this,duration)){
    case 0:
        patient->setStatus(DEAD);
        break;
    case 1:
        patient->setStatus(STABLE);
        break;
    default:
        break;
    }
    monitorHeart();
}

// Others
void AED::createPatient(bool isAdult, int status){
    patient = new Patient(isAdult, status);
}

void AED::badCPRClicked(){
    pushHarder(this);
}

void AED::okCPRClicked(){
    continueCPR(this);
}

void AED::goodCPRClicked(){
    goodCompressions(this);
}

void AED::releaseClicked(){
    Release(this);
}

