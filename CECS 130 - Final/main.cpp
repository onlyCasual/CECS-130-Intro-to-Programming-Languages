/*
	Name: Robert Wickliffe
	Description: Create an Illness Symptoms Checker
	Section: CECS 130-01A
	Date: April 22, 2022
*/

#include "Report.h"

int main()
{
	// Seed rand()
	srand(time(NULL));

	// Create a new instance of Report
	Report report = Report(0);

	// If the user wants to generate a report
	char continueCheck = 'y';

	// Print out Welcome and Guide
	std::cout << "Welcome to Symptoms Checker" << std::endl << std::endl;

	std::cout << "Guide:     * Common     + Sometimes / Rerely     -No     " << std::endl
		<< "=========================================================" << std::endl
		<< "Symptoms            |   Covid-19   |   Cold   |   Flu   |" << std::endl
		<< "=========================================================" << std::endl
		<< "Fever               |       *      |     +    |    *    |" << std::endl
		<< "Cough               |       *      |     +    |    *    |" << std::endl
		<< "Shortness of Breath |       *      |     -    |    -    |" << std::endl
		<< "Runny Nose          |       +      |     *    |    +    |" << std::endl
		<< "Headaches           |       +      |     +    |    *    |" << std::endl
		<< "Sneezing            |       -      |     *    |    -    |" << std::endl
		<< "Fatigue             |       +      |     +    |    *    |" << std::endl
		<< "=========================================================" << std::endl 
		<< std::endl;

	// Loop Checker until user does not want to check more patients
	while (continueCheck == 'y')
	{
		// # of Patients to be checked
		int patients = 0;

		// Request the user to enter a # of patients to be checked
		std::cout << "Number of Patients: ";
		std::cin >> patients;

		std::cout << std::endl << "=========================================================" << std::endl << std::endl;

		// Set the # of Patients to be checked in Report instance
		report.SetPeople(patients);

		// Run Check on Patients
		report.Check();

		// Generate a Report on Patients and print to console
		report.Generate();

		std::cout << std::endl << std::endl << "=========================================================" << std::endl << std::endl;

		// Ask user if they would like to check more patients
		std::cout << "Would you like to check more patients? ( y/n ): ";
		std::cin >> continueCheck;

		std::cout << std::endl;
	};

	std::cout << "Goodbye!" << std::endl;

	return 0;
};