/*
	Name: Robert Wickliffe
	Description: Create an Illness Symptoms Checker
	Section: CECS 130-01A
	Date: April 22, 2022
*/

#pragma once
#include "Report.h"

namespace Symptoms
{
	// Values of whether a symptom is present or not
	const char* values[] = { "Present", "Absent" };

	// Values of Symptoms
	const int symptoms[] = { FEVER, COUGH, SHORT_BREATH, RUNNY_NOSE, HEADACHE, SNEEZE, FATIGUE };
};

int Random(int max)
{
	return rand() % max;
};

void Report::Check()
{
	// If report has no Patients
	if (this->People() < 1)
		return;

	// If a previous report was made, reset report
	if (this->cold || this->flu || this->covid)
		this->Reset();

	// Generate an illness for each patient
	for (int i = 0; i < this->People(); ++i)
	{
		// Illness of the current patient
		int illness = 0;

		// Generate symptoms for current patient
		for (int i = 0; i < Symptoms::MAX; ++i)
		{
			// Random symptom
			int symptom = Symptoms::symptoms[Random(Symptoms::MAX)];
			
			// If symptom is present
			const char* isPresent = Symptoms::values[Random(2)];

			// Check if the symptom is present
			if (!strcmp(isPresent, "Present"))
				illness |= symptom;
		};

		// Increment respective illness based off symptoms
		if ((illness & Illnesses::COLD) == Illnesses::COLD)
			this->cold++;
		else if ((illness & Illnesses::COVID) == Illnesses::COVID)
			this->covid++;
		else if ((illness & Illnesses::FLU) == Illnesses::FLU)
			this->flu++;
		else
			this->other++;
	};
};

int* Report::Generate()
{
	// Print # of Patients for Respective Illnesses
	std::cout << "- = Symptoms Report = -" << std::endl
		<< std::endl
		<< this->covid << " Patient(s) have symptoms of Covid-19" << std::endl
		<< this->cold << " Patient(s) have symptoms of Cold" << std::endl
		<< this->flu << " Patient(s) have symptoms of Flu" << std::endl
		<< this->other << " Patient(s) have some other illness" << std::endl
		<< std::endl
		<< "=========================================================" << std::endl
		<< std::endl
		<< "- = Percentage of each Illness = -" << std::endl
		<< std::endl;

	// Print Report Percentage for Covid-19
	std::cout << "Covid-19: [ " << (this->covid / (this->People() / 100.f)) << "% ] ";

	for (int i = 0; i < this->covid; ++i)
		std::cout << '+';

	// Print Report Percentage for Cold
	std::cout << std::endl
		<< "Cold:     [ " << (this->cold / (this->People() / 100.f)) << "% ] ";

	for (int i = 0; i < this->cold; ++i)
		std::cout << '+';

	// Print Report Percentage for Flu
	std::cout << std::endl
		<< "Flu:      [ " << (this->flu / (this->People() / 100.f)) << "% ] ";

	for (int i = 0; i < this->flu; ++i)
		std::cout << '+';

	// Print Report Percentage for Other Illness
	std::cout << std::endl
		<< "Other:    [ " << (this->other / (this->People() / 100.f)) << "% ] ";

	for (int i = 0; i < this->other; ++i)
		std::cout << '+';

	// Set respective indexes in report
	this->report[0] = this->covid;
	this->report[1] = this->cold;
	this->report[2] = this->flu;
	this->report[3] = this->other;

	return this->report;
};

void Report::Reset()
{
	this->cold = 0;
	this->flu = 0;
	this->covid = 0;
	this->other = 0;

	for (int i = 0; i < 4; ++i)
		this->report[i] = 0;
};