/*
	Name: Robert Wickliffe
	Description: Create an Illness Symptoms Checker
	Section: CECS 130-01A
	Date: April 22, 2022
*/

#pragma once
#include "Illness.h"

class Report : public Illness
{
	// # of Patients with Covid
	int covid;

	// # of Patients with a Cold
	int cold;

	// # of Patients with the Flu
	int flu;

	// # of Patients with Another Illness
	int other;

	// Arry of Illness Variables ( returned from Generate )
	int report[4];

public:
	Report() : covid(0), cold(0), flu(0), other(0) {};
	Report(int p) : Illness(p), covid(0), cold(0), flu(0), other(0) {}

	// Check patients for Illnesses
	void Check();

	// Generate an Illness Report
	int* Generate();

	// Reset Illness Report Records
	void Reset();
};