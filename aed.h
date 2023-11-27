#ifndef AED_H
#define AED_H

#include <QtGlobal>
#include <QString>
#include "patient.h"

class AED
{
public:
    AED();
    ~AED();
    bool getDeviceStatus();
    void setDeviceOn();
    void setDeviceOff();
    void createPatient(QString name, int age);
    void setAdultPads();
    void setChildPads();
    void monitorHeart();
    void deliverShock();
    void cprFeedback();
private:
    bool deviceStatus;
    bool areAdultPadsApplied;
    bool areChildPadsApplied;
    int chargeDeliveredCount;
    Patient* patient;
};

#endif // AED_H
