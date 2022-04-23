/*
	Name: Robert Wickliffe
	Description: Create a calculator that supports 5 basic operations and primality testing.
	Section: CECS 130-01A
	Date: February 4, 2022
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
	EXIT = 7,
	MAX_OPERATIONS = 8
};

// Print the calculator menu to console
void PrintMenu();

// Check if operation is a valid operation
int IsValidOperation(int operation);

void PrintMenu()
{
	printf("Calculator Menu:\n");
	printf("[1] Addition\n");
	printf("[2] Subtraction\n");
	printf("[3] Multiplication\n");
	printf("[4] Division\n");
	printf("[5] Modulus ( Intergers Only )\n");
	printf("[6] Primality Test ( Intergers Only )\n");
	printf("[7] Exit\n\n");
	printf("Please enter an operation: ");
};

int IsValidOperation(int operation)
{
	return (operation > NONE) && (operation < MAX_OPERATIONS);
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
			{
				float num1 = 0.f;
				float num2 = 0.f;
				
				printf("Please enter a number: ");
				scanf("%f", &num1);
				
				printf("Please enter another number: ");
				scanf("%f", &num2);
				
				printf("%g + %g = %g\n\n", num1, num2, (num1 + num2));
			}
			break;
			
			// Subtract two floating point numbers
			case SUB:
			{
				float num1 = 0.f;
				float num2 = 0.f;
				
				printf("Please enter a number: ");
				scanf("%f", &num1);
				
				printf("Please enter another number: ");
				scanf("%f", &num2);
				
				printf("%g - %g = %g\n\n", num1, num2, (num1 - num2));
			}
			break;
			
			// Multiply two floating point numbers
			case MULT:
			{
				float num1 = 0.f;
				float num2 = 0.f;
				
				printf("Please enter a number: ");
				scanf("%f", &num1);
				
				printf("Please enter another number: ");
				scanf("%f", &num2);
				
				printf("%g * %g = %g\n\n", num1, num2, (num1 * num2));
			}
			break;
			
			// Divide two floating point numbers
			case DIVIDE:
			{
				float num1 = 0.f;
				float num2 = 0.f;
				
				printf("Please enter a number: ");
				scanf("%f", &num1);
				
				printf("Please enter another number: ");
				scanf("%f", &num2);
				
				printf("%g / %g = %g\n\n", num1, num2, (num1 / num2));
			}
			break;
			
			// Remainder of division between two intergers
			case MOD:
			{
				int num1 = 0;
				int num2 = 0;
				
				printf("Please enter a number ( Interger ): ");
				scanf("%d", &num1);
				
				printf("Please enter another number ( Interger ): ");
				scanf("%d", &num2);
				
				printf("%d %% %d = %d\n\n", num1, num2, (num1 % num2));
			}
			break;
			
			// Test if number had divisiors beside 1 and itself
			case PRIME:
			{
				int num = 0;
				
				printf("Please enter a number ( Interger ): ");
				scanf("%d", &num);
				
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
				
				// Print a new line and break from case
				if(divisors > 0)
				{
					printf("\n");
					break;
				}
				
				// Print number is prime
				printf("%d is prime\n\n", num);
			}
			break;
		};
		
		// Reset operation to NONE
		operation = NONE;
	};
	
	// Exit message
	printf("Goodbye!");
	
	return 0;
};
