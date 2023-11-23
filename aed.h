#ifndef AED_H
#define AED_H

class AED
{
public:
    AED();
    void setDeviceOn();
    void setDeviceOff();
    void setAdultPads();
    void setChildPads();
    void monitorHeart();
    void deliverShock();
    void cprFeedback();
private:
    bool status;
    bool areAdultPadsApplied;
    bool areChildPadsApplied;
    int chargeDeliveredCount;
};

#endif // AED_H
