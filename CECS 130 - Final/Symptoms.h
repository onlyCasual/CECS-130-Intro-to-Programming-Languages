/*
	Name: Robert Wickliffe
	Description: Create an Illness Symptoms Checker
	Section: CECS 130-01A
	Date: April 22, 2022
*/

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

// Generate a random number ( 0 <= num < max )
int Random(int max);

namespace Symptoms
{
	// Symptoms Patients can have
	enum
	{
		NONE = 0,
		FEVER = 1,
		COUGH = 2,
		SHORT_BREATH = 4,
		RUNNY_NOSE = 8,
		HEADACHE = 16,
		SNEEZE = 32,
		FATIGUE = 64,
		MAX = 8
	};
};

namespace Illnesses
{
	// Illnesses with their respective symptoms
	enum
	{
		COVID = Symptoms::FEVER | Symptoms::COUGH | Symptoms::SHORT_BREATH,
		COLD = Symptoms::SNEEZE | Symptoms::RUNNY_NOSE,
		FLU = Symptoms::FEVER | Symptoms::COUGH | Symptoms::HEADACHE | Symptoms::FATIGUE,
		ALL = Symptoms::FEVER | Symptoms::COUGH | Symptoms::SHORT_BREATH | Symptoms::RUNNY_NOSE | Symptoms::HEADACHE | Symptoms::SNEEZE | Symptoms::FATIGUE
	};
};