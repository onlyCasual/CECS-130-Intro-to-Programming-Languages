/*
	Name: Robert Wickliffe
	Description: Create a calculator that supports 5 basic operations, primality testing, and 3 additional operations.
	Section: CECS 130-01A
	Date: February 7, 2022
*/
#include <stdio.h>

// Valid operation types
enum Operations
{
	NONE = 0,
	ADD = 1,
	SUB = 2,
	MULT = 3,
	DIVIDE = 4,
	MOD = 5,
	PRIME = 6,
	FACTOR = 7,
	POWER = 8,
	FIBONACCI = 9,
	EXIT = 10,
	MAX_OPERATIONS = 11
};

// Print the calculator menu to console
void PrintMenu();

// Check if operation is a valid operation
int IsValidOperation(int operation);

// Requesting float and interger from user
int GetInt();
float GetFloat();

// Recursive factorial function
int Factor(int num);

// Recurive power function
float Pow(float num1, int num2);

// Recursive fibonacci function
int Fib(int num, int* results);

// Calculator functions
void Add();
void Subtract();
void Multiply();
void Divide();
void Modulus();
void Primality();
void Factorial();
void Power();
void Fibonnaci();

void PrintMenu()
{
	printf("Calculator Menu:\n");
	printf("[1] Addition\n");
	printf("[2] Subtraction\n");
	printf("[3] Multiplication\n");
	printf("[4] Division\n");
	printf("[5] Modulus ( Intergers Only )\n");
	printf("[6] Primality Test ( Intergers Only )\n");
	printf("[7] Factorial ( Intergers Only )\n");
	printf("[8] Power\n");
	printf("[9] Fibonacci ( Intergers Only )\n");
	printf("[10] Exit\n\n");
	printf("Please enter an operation: ");
};

int IsValidOperation(int operation)
{
	return (operation > NONE) && (operation < MAX_OPERATIONS);
};

int GetInt()
{
	int num = 0;
	
	printf("Please enter a number (Interger): ");
	scanf("%d", &num);
	
	return num;
};

float GetFloat()
{
	float num = 0.f;
	
	printf("Please enter a number: ");
	scanf("%f", &num);
	
	return num;
};

int Factor(int num)
{
	if(num <= 1)
		return num;
		
	return num * Factor(num - 1);
};

float Pow(float num1, int num2)
{
	if(num2 <= 1)
		return num1;
	
	return num1 * Pow(num1, num2 - 1);
};

int Fib(int num, int* results)
{
	if(num <= 1)	
	{
		results[num - 1] = num;
		return results[num - 1];
	};
	
	results[num - 1] = Fib(num - 1, results) + Fib(num - 2, results);
	return results[num - 1];
};

void Add()
{
	float num1 = GetFloat();
	float num2 = GetFloat();	
	
	printf("%g + %g = %g\n\n", num1, num2, (num1 + num2));
};

void Subtract()
{
	float num1 = GetFloat();
	float num2 = GetFloat();
	
	printf("%g - %g = %g\n\n", num1, num2, (num1 - num2));
};

void Multiply()
{
	float num1 = GetFloat();
	float num2 = GetFloat();
	
	printf("%g * %g = %g\n\n", num1, num2, (num1 * num2));
};

void Divide()
{
	float num1 = GetFloat();
	float num2 = GetFloat();
	
	// Ensure there is no division by 0
	if(num2 == 0)
	{
		printf("%g / %g = Undefined\n\n", num1, num2);
		return;
	};
	
	printf("%g / %g = %g\n\n", num1, num2, (num1 / num2));
};

void Modulus()
{
	int num1 = GetInt();
	int num2 = GetInt();
	
	// Ensure there is no division by 0
	if(num2 == 0)
	{
		printf("%d %% %d = Undefined\n\n", num1, num2);
		return;
	};
	
	printf("%d %% %d = %d\n\n", num1, num2, (num1 % num2));
};

void Primality()
{
	int num = GetInt();
	
	int n1, n2, divisors = 0;
	
	// Loop through searching for divisors
	for(n1 = 2; n1 < num; ++n1)
	{
		for(n2 = 2; n2 <= n1; ++n2)
		{
			if(n1 * n2 == num)
			{
				printf("%d is not prime: %d * %d = %d\n", num, n1, n2, num);
				divisors++;
			};
		};
	};
	
	// Print a new line
	if(divisors > 0)
	{
		printf("\n");
		return;
	}
	
	// Print number is prime
	printf("%d is prime\n\n", num);	
};

void Factorial()
{
	int num = GetInt();	
	
	printf("%d! = %d\n\n", num, Factor(num));
};

void Power()
{
	float num1 = GetFloat();
	int num2 = GetInt();
	
	printf("%g ^ %d = %g\n\n", num1, num2, Pow(num1, num2));	
};

void Fibonacci()
{
	int num = GetInt();
	
	while(num > 256)
	{
		printf("Please enter a smaller number ( < 256 ): ");
		scanf("%d", &num);	
	};
	
	int results[256];
	
	int i = 0;
	
	printf("Fibonacci to the %d = %d\n", num, Fib(num, results));	
	printf("Fibonacci sequence: ");
	
	for(i = 0; i < num; ++i)
		printf("%d ", results[i]);
		
	printf("\n\n");
};

int main()
{
	// Where the current operation will be stored
	int operation = NONE;
	
	// Don't exit loop until operation is EXIT
	while(operation != EXIT)
	{
		// Print menu if no current operation, otherwise ask for valid operation
		if(operation == NONE)
		{
			PrintMenu();
			scanf("%d", &operation);
			continue;
		}
		else if(!IsValidOperation(operation))
		{
			printf("Please enter a valid operation: ");
			scanf("%d", &operation);
			continue;
		};
		
		switch(operation)
		{
			// Add two floating point numbers
			case ADD:
				Add();
			break;
			
			// Subtract two floating point numbers
			case SUB:
				Subtract();
			break;
			
			// Multiply two floating point numbers
			case MULT:
				Multiply();
			break;
			
			// Divide two floating point numbers
			case DIVIDE:
				Divide();
			break;
			
			// Remainder of division between two intergers
			case MOD:
				Modulus();
			break;
			
			// Test if number has divisiors beside 1 and itself
			case PRIME:
				Primality();
			break;
			
			// Factorial of an interger
			case FACTOR:
				Factorial();
			break;
			
			// Power of an interger to another interger
			case POWER:
				Power();	
			break;
			
			// Get the nth number in the fibonacci sequence and print the sequence
			case FIBONACCI:
				Fibonacci();
			break;
		};
		
		// Reset operation to NONE
		operation = NONE;
	};
	
	// Exit message
	printf("Goodbye!");
	
	return 0;
};
