/*
	Name: Robert Wickliffe
	Description: Create an Illness Symptoms Checker
	Section: CECS 130-01A
	Date: April 22, 2022
*/

#pragma once
#include "Symptoms.h"

class Illness
{
	// # of People to check
	int people;

public:
	Illness() : people(0) {};
	Illness(int p) : people(p) {};

	// Get # of Patients to be checked
	inline int People() { return this->people; };
	
	// Set the # of Patients to be checked
	inline void SetPeople(int p) { this->people = p; };
};