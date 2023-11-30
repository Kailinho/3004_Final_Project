#include "patient.h"

map<int, string> Patient::healthCondition = {{0, "Dead"}, {1, "Healthy"}, {2, "V-Fib"}, {3, "V_Tach"}};

Patient::Patient(QString name, int age, int healthStatus)
{
    this->name = name;
    this->age = age;
    this->healthStatus = healthStatus;
    QString healthStatusString = QString::fromStdString(healthCondition.at(healthStatus));
    qInfo("Patient %s is %d year(s) old. Condition: %s", qUtf8Printable(name), age, qUtf8Printable(healthStatusString));
}

bool Patient::isAnAdult()
{
    if(age >= 18)
    {
        return true;
    }
    return false;
}
