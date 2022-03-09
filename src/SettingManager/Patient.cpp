/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	Patient.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Patient.hpp"

Patient::Patient(/* args */)
{
}


Patient::Patient(PATIENT pa)
{

    memcpy(reinterpret_cast<void*>(&patient), reinterpret_cast<void*>(&pa), sizeof(PATIENT));

}

Patient::~Patient()
{
}


INT16U Patient::getAge()
{
    return patient.age;
}

void Patient::setAge(const INT16U age)
{
    patient.age = age;
}

INT16U Patient::getGender()
{
    return patient.gender;
}

void Patient::setGender(const INT16U gender)
{
    patient.gender = gender;
}


INT16U Patient::getHeight()
{
    return patient.height;
}


void Patient::setHeight(const INT16U height)
{
    patient.height = height;
}


INT16U Patient::getWeight()
{
    return patient.weight;
}


void Patient::setWeight(const INT16U weight)
{
    patient.weight = weight;
}


void Patient::setPacemaker(const bool pacemaker)
{
    patient.pacemaker = pacemaker;
}


bool Patient::getPacemaker()
{
    return patient.pacemaker;
}


std::string Patient::getId()
{
    return patient.id;
}


void Patient::setId(const std::string id)
{
    patient.id = id;
}


void Patient::setName(const std::string familyName, const std::string firstName)
{
    patient.familyName = familyName;
    patient.firstName = firstName;
}


void Patient::getName(std::string &familyName, std::string firstName)
{
    familyName = patient.familyName;
    firstName = patient.firstName;
}


void Patient::setPatientInfo(const PATIENT patientinfo)
{
    patient.age = patientinfo.age;
    patient.id = patientinfo.id;
    patient.familyName = patientinfo.familyName;
    patient.firstName = patientinfo.firstName;
    patient.gender = patientinfo.gender;
    patient.height = patientinfo.height;
    patient.weight = patientinfo.weight;
    patient.pacemaker = patientinfo.pacemaker;
}


PATIENT Patient::getPatientInfo()
{
    return patient;
}


INT16 Patient::savePatient()
{

    return 0;
}


INT16 Patient::loadPatient()
{

    return 0;
}


INT8U Patient::clear()
{
    patient.age = 0;
    patient.gender = 0;
    patient.height = 0;
    patient.weight = 0;
    patient.pacemaker = false;

    patient.familyName = "";
    patient.firstName = "";
    patient.id = "";
}
