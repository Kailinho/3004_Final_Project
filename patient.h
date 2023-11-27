#ifndef PATIENT_H
#define PATIENT_H

#include <QtGlobal>
#include <QString>

using namespace std;

class Patient
{
public:
    Patient(QString name, int age);
    bool isAnAdult();
private:
    QString name;
    int age;
    bool isAlive;
    bool isShockable;
    int chestCompressionLevelNeeded;
};

#endif // PATIENT_H
