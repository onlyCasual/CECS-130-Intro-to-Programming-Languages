/*
	Name: Robert Wickliffe
	Description: Create an ASCII-art table that shows currency conversions. ( 6 currencies minimum )
	Section: CECS 130-01A
	Date: Janauary 19, 2022
*/
#include <stdio.h>

// Exchange of currencies, in terms of 1 USD
const double USD = 1.000000;
const double GBP = 0.737571;
const double CAD = 1.255979;
const double EUR = 0.882373;
const double AUD = 1.392226;
const double JPY = 113.845183;

// Structure to hold currency conversions
typedef struct
{
	double usd;
	double gbp;
	double cad;
	double eur;
	double aud;
	double jpy;
} Conversions;

// Get exchange of a currency from another with a given multiplier
double Conversion(const double from, const double to, const double multiplier);

// Fill with conversions from the given currency
void GetConversions(const double from, const double multiplier, Conversions* out);

// Print a line of conversion to the console
void PrintConversion(const char* currency, Conversions* in);

double Conversion(const double from, const double to, const double multiplier) 
{
	return (multiplier * from) / to;
};

void GetConversions(const double from, const double multiplier, Conversions* out)
{
	out->usd = Conversion(from, USD, multiplier);
	out->gbp = Conversion(from, GBP, multiplier);
	out->cad = Conversion(from, CAD, multiplier);
	out->eur = Conversion(from, EUR, multiplier);
	out->aud = Conversion(from, AUD, multiplier);
	out->jpy = Conversion(from, JPY, multiplier);
};

void PrintConversion(const char* currency, Conversions* in)
{
	printf("| %s | %f | %f | %f | %f | %f | %f |\n", currency, in->usd, in->gbp, in->cad, in->eur, in->aud, in->jpy);
};

int main()
{	
	// Amount to convert
	double amount = 0.f;
	
	// Conversion storage
	Conversions conversions;
	
	// Request the user to enter an amount to convert
	printf("Enter the amount you would like to convert: ");
	scanf("%lf", &amount);
	
	// Print table headers
	printf("|     |    USD   |    GBP   |    CAD   |    EUR   |    AUD   |    JPY   |\n");
	
	// Print table rows for conversions
	GetConversions(USD, amount, &conversions);
	PrintConversion("USD", &conversions);
	
	GetConversions(GBP, amount, &conversions);
	PrintConversion("GBP", &conversions);
	
	GetConversions(CAD, amount, &conversions);
	PrintConversion("CAD", &conversions);
	
	GetConversions(EUR, amount, &conversions);
	PrintConversion("EUR", &conversions);
	
	GetConversions(AUD, amount, &conversions);
	PrintConversion("AUD", &conversions);
	
	GetConversions(JPY, amount, &conversions);
	PrintConversion("JPY", &conversions);
	
	return 0;
};
