#ifndef AED_H
#define AED_H

#include <QString>
#include <QtGlobal>
#include <QThread>
#include "patient.h"

class AED
{
public:
    AED();
    ~AED();
    void createPatient(QString name, int age, int healthStatus);
    bool getDeviceStatus();
    void setDeviceOn();
    void setDeviceOff();
    void checkIfPadsAreOn();
    void setPadsStatus(bool adultPad1status, bool adultPad2status, bool childPad1status, bool childPad2status);
    void monitorHeart();
    void deliverShock();
    void cprFeedback();
private:
    bool deviceStatus;
    bool isAdultPad1Applied;
    bool isAdultPad2Applied;
    bool isChildPad1Applied;
    bool isChildPad2Applied;
    int chargeDeliveredCount;
    Patient* patient;
};

#endif // AED_H
