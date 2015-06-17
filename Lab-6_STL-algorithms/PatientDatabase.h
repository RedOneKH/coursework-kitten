/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the PatientDatabase singleton class. It combines a hash
table and a tree that both point to the patient data and are both used for
different types of searches.
*/

#ifndef PATIENT_DATABASE_H_
#define PATIENT_DATABASE_H_

#include "PatientList.h"
#include "PatientHash.h"
#include "PatientTree.h"

class PatientDatabase
{
private:
	static PatientList *plist;
	static PatientHash *phash;
	static PatientTree *ptree;

	static PatientDatabase *instance;

	PatientDatabase()
	{
		plist = PatientListSingleton::getInstance();
		phash = PatientHashSingleton::getInstance();
		ptree = PatientTreeSingleton::getInstance();
	}

	~PatientDatabase()
	{
		PatientListSingleton::resetInstance();
		PatientHashSingleton::resetInstance();
		PatientTreeSingleton::resetInstance();
	}
public:
	static PatientDatabase * getInstance();
	static void resetInstance()    { delete instance; instance = 0; }
	static bool exists()           { return (instance != 0); }
	static bool componentsExist()
	{
		return (PatientListSingleton::exists() && 
			PatientHashSingleton::exists() && 
			PatientTreeSingleton::exists());
	}

	PatientList * getPatientList() { return plist; }
	PatientHash * getPatientHash() { return phash; }
	PatientTree * getPatientTree() { return ptree; }
};

PatientHash * PatientDatabase::phash = 0;
PatientTree * PatientDatabase::ptree = 0;
PatientDatabase * PatientDatabase::instance = 0;

PatientDatabase * PatientDatabase::getInstance()
{
	if (!instance)
	{
		instance = new PatientDatabase();
	}

	return instance;
}

#endif // PATIENT_DATABASE_H_