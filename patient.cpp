#include "patient.h"

#define STABLE 1
#define SHOCKABLE 2
#define NOT_SHOCKABLE 3
#define DEAD 4

int Patient::p_count = 1;

Patient::Patient(bool isAdult, bool shockable, QObject *parent): QObject(parent){
    num = p_count;
    p_count++;

    this->isAdult = isAdult;

    if(shockable){
        status = SHOCKABLE;
    } else {
        status = NOT_SHOCKABLE;
    }

    // This can probably be removed once a dropdown menu has been created with multiple patients
    if(isAdult){
        qInfo("Patient %i is an adult.", num);
    } else {
        qInfo("Patient %i is a child.", num);
    }
}

Patient::~Patient(){}

//Getters
bool Patient::getIsAdult(){
    return isAdult;
}

int Patient::getStatus(){
    return status;
}

//Setters
void Patient::setStatus(int newStatus){
    status = newStatus;
}
