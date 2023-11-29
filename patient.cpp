#include "patient.h"

Patient::Patient(QString name, int age)
{
    this->name = name;
    this->age = age;
    qInfo("Patient %s is %d year(s) old.", qUtf8Printable(name), age);
}

bool Patient::isAnAdult()
{
    if(age >= 18)
    {
        return true;
    }
    return false;
}
