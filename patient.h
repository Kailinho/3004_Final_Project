#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient
{
public:
    Patient();
private:
    std::string name;
    int age;
    bool isAlive;
    bool isShockable;
    int chestCompressionLevelNeeded;
};

#endif // PATIENT_H
