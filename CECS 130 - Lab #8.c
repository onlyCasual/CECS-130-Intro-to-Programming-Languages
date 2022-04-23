/*
	Name: Robert Wickliffe
	Description: Create a phone book to store the contacts of all your friends. ( Use an array of structures )
	Section: CECS 130-01A
	Date: March 25, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Valid Menu Operations
enum Operations
{
	NONE = 0,
	ADD = 1,
	REMOVE = 2,
	DISPLAY = 3,
	FIND = 4,
	RANDOM = 5,
	CLEAR = 6,
	SAVE = 7,
	EXIT = 8,
	MAX_OPERATIONS = 9
};

// Contact Structure
typedef struct
{
	char first[32];
	char last[32];
	char phone[9];
} Contact;

// Phone Book Structure
typedef struct
{
	unsigned int length;
	Contact* contacts;
} PhoneBook;

// Check if is a valid operation
int IsValidOperation(int operation);

// Generate a psuedo-random number ( 0 <= num < max )
int Random(int max);

// Phone Book array element modification
void Insert(Contact* arr, Contact* contact, int index, unsigned int length);

// Print menu to console
void PrintMenu();

// Add a Contact to a Phone Book
int AddContact(PhoneBook* book, Contact contact);

// Remove a Contact to a Phone Book
int RemoveContact(PhoneBook* book, unsigned int index);

// Display Contacts in a Phone Book
void DisplayContacts(PhoneBook* book);

// Get a contact in Phone Book, given first or last name
Contact* GetContact(PhoneBook* book, const char* name);

// Alphabetically sort list by last name
void SortContacts(PhoneBook* book);

// File IO
int SaveBook(PhoneBook* book, const char* path);
void LoadBook(PhoneBook* book, const char* path);

// Operation Functions
void Add(PhoneBook* book);
void Remove(PhoneBook* book);
void Display(PhoneBook* book);
void RandomContact(PhoneBook* book);
void ClearContacts(PhoneBook* book);
void FindContact(PhoneBook* book);
void Save(PhoneBook* book);

int IsValidOperation(int operation)
{
	return (operation > NONE) && (operation < MAX_OPERATIONS);
};

int Random(int max)
{
	return rand() % max;
};

void Insert(Contact* arr, Contact* contact, int index, unsigned int length)
{
	// Index out of range
	if (index > (length - 1))
		return;

	// Allocate space for modified array
	Contact* new_arr = calloc(length, sizeof(Contact));

	// Loop throgh array and add previous elements to new array
	unsigned int i = 0;

	if (new_arr == NULL)
		return;

	for (i = 0; i < length; ++i)
	{
		if (i < index)
			new_arr[i] = arr[i];
		else if (i > index)
			new_arr[i] = arr[i - 1];
	};

	// Add new element to array
	new_arr[index] = *contact;
	
	// Copy modified array to original array
	memcpy(arr, new_arr, sizeof(Contact) * length);

	// Free modified array
	free(new_arr);
};

void PrintMenu()
{
	printf("Phone Book\n");
	printf("[1] Add Contact\n");
	printf("[2] Remove Contact\n");
	printf("[3] Display Contacts\n");
	printf("[4] Find Contact\n");
	printf("[5] Random Contact\n");
	printf("[6] Clear Contacts\n");
	printf("[7] Save\n");
	printf("[8] Exit\n\n");
	printf("Please choose an option: ");
};

int AddContact(PhoneBook* book, Contact contact)
{
	// Alocate space for current contacts + new contact
	Contact* contacts = calloc(book->length + 1, sizeof(Contact));

	// If allocation failed
	if (contacts == NULL)
		return 0;

	// Add current contacts to array	
	unsigned int i = 0;

	for (i = 0; i < book->length; ++i)
		contacts[i] = book->contacts[i];

	// Add new contact to array
	contacts[book->length] = contact;

	// Free previous array of contacts
	free(book->contacts);

	// Set new pointer to contacts and increment length
	book->contacts = contacts;
	book->length++;

	return 1;
};

int RemoveContact(PhoneBook* book, unsigned int index)
{
	// If index is out of range
	if ((index < 0) || (index >= book->length))
		return 0;

	// Allocate space for current contacts - removed contact
	Contact* contacts = calloc(book->length - 1, sizeof(Contact));

	// If memory allocation failed
	if (contacts == NULL)
		return 0;

	// Add current contacts to array, ignoring removed contact
	unsigned int i = 0;
	int added = 0;

	for (i = 0; i < book->length; ++i)
	{
		if (i != index)
		{
			contacts[added] = book->contacts[i];
			added++;
		};
	};

	// Free previous array of contacts
	free(book->contacts);

	// Set new pointer to contacts and decrement length
	book->contacts = contacts;
	book->length--;

	return 1;
};

void DisplayContacts(PhoneBook* book)
{
	// Loop through contacts array and print each contact information
	unsigned int i = 0;
	Contact* contacts = book->contacts;

	for (i = 0; i < book->length; ++i)
		printf("[%d] %s, %s ( %s )\n", (i + 1), contacts[i].last, contacts[i].first, contacts[i].phone);

	printf("\n");
};

Contact* GetContact(PhoneBook* book, const char* name)
{
	// Loop through contacts and find corresponding contact
	unsigned int i = 0;

	for (i = 0; i < book->length; ++i)
	{
		Contact* contact = &book->contacts[i];

		if (!strcmp(tolower(contact->last), tolower(name)) ||
			!strcmp(tolower(contact->first), tolower(name)))
		{
			return contact;
		};
	};

	return NULL;
};

void SortContacts(PhoneBook* book)
{
	// If no contacts or only a single contact are added to the phone book
	if (book->length < 2)
		return;

	// Allocate space for sorted contacts
	Contact* contacts = calloc(book->length, sizeof(Contact));

	// Loop through contacts and sort alphabetically by last ( Ascending )
	unsigned int i = 0;
	unsigned int v = 0;
	int length = 2;

	for (i = 0; i < book->length; ++i)
	{
		if (i < 1)
			contacts[i] = book->contacts[i];
		else
		{
			for (v = 0; v < i; ++v)
			{
				int comaparison = strcoll(book->contacts[i].last, contacts[v].last);

				if (comaparison < 0)
				{
					Insert(contacts, &book->contacts[i], v, length);
					break;
				}
				else if (comaparison > 0)
				{
					if (v == (i - 1))
					{
						Insert(contacts, &book->contacts[i], v + 1, length);
						break;
					}
					else
						continue;
				}
				else
				{
					Insert(contacts, &book->contacts[i], v, length);
					break;
				};
			};

			length++;
		};
	};
	
	// Free previous array of contacts
	free(book->contacts);

	// Set phone book contacts pointer to sorted array
	book->contacts = contacts;
};

int SaveBook(PhoneBook* book, const char* path)
{
	FILE* file;
	file = fopen(path, "w+");

	if (file == NULL)
		return 0;

	// Writing data to file
	unsigned int i = 0;

	for (i = 0; i < book->length; ++i)
	{
		Contact* contact = &book->contacts[i];

		fputs(contact->first, file);
		fputs("\n", file);
		fputs(contact->last, file);
		fputs("\n", file);
		fputs(contact->phone, file);
		fputs("\n", file);
	};

	fclose(file);

	return 1;
};

void LoadBook(PhoneBook* book, const char* path)
{

};

void Add(PhoneBook* book)
{
	// Create new contact structure
	Contact contact;

	// Request user to enter contact information
	printf("Contact's First Name: ");
	scanf("%31s", &contact.first);

	printf("Contact's Last Name: ");
	scanf("%31s", &contact.last);

	printf("Contact's Phone Number ( XXX-XXXX ): ");
	scanf("%8s", &contact.phone);

	// Attempt to add the contact and display result
	if (AddContact(book, contact))
		printf("+ Added new contact: %s, %s ( %s )\n\n", contact.last, contact.first, contact.phone);
	else
		printf("- Failed to add contact\n\n");
};

void Remove(PhoneBook* book)
{
	// Index of contact to remove
	unsigned int index = 0;

	// If there are no contacts
	if (book->length < 1)
	{
		printf("There are no contacts to remove\n\n");
		return;
	};

	// Display contacts, for user to choose from
	DisplayContacts(book);

	// Request user to enter an index
	printf("Contact to remove ( Integer ): ");
	scanf("%d", &index);

	// While index is not valid ask for another
	while ((index < 1) || (index > book->length))
	{
		printf("Please enter a valid contact: ");
		scanf("%d", &index);
	};

	// Store info of contact to be removed
	Contact contact = book->contacts[index - 1];

	// Attempt to remove the contact and display result
	if (RemoveContact(book, (index - 1)))
		printf("+ Removed contact: %s, %s ( %s )\n\n", contact.last, contact.first, contact.phone);
	else
		printf("- Failed to remove contact\n\n");
};

void Display(PhoneBook* book)
{
	// If there are no contacts to display
	if (book->length < 1)
	{
		printf("There are no contacts to display\n\n");
		return;
	};

	// Display the contacts
	DisplayContacts(book);
};

void RandomContact(PhoneBook* book)
{
	// If there are no contacts in bool
	if (book->length < 1)
	{
		printf("There are no contacts to choose from\n\n");
		return;
	};
	
	// Retreive a random contact from array
	Contact contact = book->contacts[Random(book->length)];

	printf("%s, %s ( %s )\n\n", contact.last, contact.first, contact.phone);
};

void ClearContacts(PhoneBook* book)
{
	// If there are no contacts to remove
	if (book->length < 1)
	{
		printf("There are no contacts to remove\n\n");
		return;
	};

	// Free previous array of contacts
	free(book->contacts);
	
	// Reset PhoneBook member variables
	book->contacts = NULL;
	book->length = 0;

	printf("All contacts have been removed\n\n");
};

void FindContact(PhoneBook* book)
{
	// Where search name will be stored
	char name[32];

	// Request the user to enter a name
	printf("Contact's First or Last Name: ");
	scanf("%31s", name);

	// Get contact with corrsponding name
	Contact* contact = GetContact(book, name);

	// See if contact was found and display result
	if (contact != NULL)
		printf("+ Contact: %s, %s ( %s )\n\n", contact->last, contact->first, contact->phone);
	else
		printf("- Failed to find contact\n\n");
};

void Save(PhoneBook* book)
{
	char path[128];

	// Request the user to enter a name
	printf("Please enter a path to save the book: ");
	scanf("%127s", path);

	if(SaveBook(book, path))
		printf("+ Successfully saved book\n\n");
	else
		printf("- Failed to save book\n\n");
};

int main()
{
	// Seed rand
	srand(time(NULL));

	// Create a new PhoneBook structure
	PhoneBook book;

	// Reset PhoneBook member variables
	book.length = 0;
	book.contacts = NULL;

	int operation = NONE;

	// While the user does not want to exit
	while (operation != EXIT)
	{
		if (operation == NONE)
		{
			PrintMenu();
			scanf("%d", &operation);
			continue;
		}
		else if (!IsValidOperation(operation))
		{
			printf("Please enter a valid option: ");
			scanf("%d", &operation);
			continue;
		};

		switch (operation)
		{
			// Add a new contact
			case ADD:
				Add(&book);
			break;

			// Remove a contact
			case REMOVE:
				Remove(&book);
			break;

			// Display all contacts
			case DISPLAY:
				Display(&book);
			break;

			// Find a contact
			case FIND:
				FindContact(&book);
			break;
			
			// Get a random contact
			case RANDOM:
				RandomContact(&book);
			break;

			// Clear all contacts
			case CLEAR:
				ClearContacts(&book);
			break;

			case SAVE:
				Save(&book);
			break;
		};

		// Reset operation to NONE
		operation = NONE;

		// Sort contact list ( Ascending )
		SortContacts(&book);
	};

	// Free array of contacts
	free(book.contacts);

	printf("Goodbye!");

	return 0;
};
