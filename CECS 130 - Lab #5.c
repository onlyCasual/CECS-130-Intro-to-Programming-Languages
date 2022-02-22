/*
	Name: Robert Wickliffe
	Description: Ask the user questions and create a psuedo-random short story with their answers.
	Section: CECS 130-01A
	Date: February 13, 2022
*/
#include <stdio.h>
#include <time.h>

// Structure options
const int MAX_STRUCTURES = 3;

const char* structures[] =
{
	"Pyramid",
	"Temple",
	"Abandoned Building"
};

// Weapon Options
const int MAX_WEAPONS = 6;

const char* weapons[] =
{
	"Katana",
	"Harpoon",
	"Scythe",
	"Hatchet",
	"Machete",
	"Gun"
};

// Enemy Options
const int MAX_ENEMIES = 6;

const char* enemies[] =
{
	"Spider",
	"Worm",
	"Zombie",
	"Pirate",
	"Ghost",
	"Shark"
};

// Treasure Options
const int MAX_TREASURE = 6;

const char* treasure[] =
{
	"Gold Necklace",
	"Emerald",
	"Diamond",
	"Sapphire",
	"Map",
	"Chalice"
};

// Trap options
const int MAX_TRAPS = 4;

const char* traps[] =
{
	"Shot with Poison Darts",
	"Crushed By A Boulder",
	"Impaled by A Spear",
	"Engulfed by An Endless Hole"
};

// Beginning options
const int MAX_INTRO = 3;

const char* introductions[] = 
{
	"It was %s at %s. ",
	"On %s at %s an expedition had begun. ",
	"%s at %s would begin the ending of this story. "
};

// Beginning options
const int MAX_BEGIN = 3;

const char* beginnings[] = 
{
	"%s travelled to %s and ventured into a(n) %s. With no clue of what was inside they proceeded. ",
	"While %s was exploring in %s, they stumbled upon a(n) %s. They decided to cautiously enter. ",
	"%s, while in %s, discovered a(n) %s. Hesitant at first they decided to venture inside. "
};

// Middle options
const int MAX_MIDDLE = 2;

const char* middles[] = 
{
	"Upon arriving inside they dicovered a gang of %s. They turned quickly and found a(n) %s laying on the ground and used it to fend them off. They then proceeded to a dimly lit room. ",
	"Once they arrived inside, They were attacked by %s\'s. Running to safety they opened a chest and found a %s. Using there newly acquired weapon, they fended off the enemies and entered a dark room. "
};

// Middle options
const int MAX_END = 2;

const char* endings[] = 
{
	"Inside the room they found a chest. Upon opening the chest they found a %s. When removed from the chest, they were %s abruptly ending their adeveture. ",
	"A safe lied in the corner of the room. When opened a %s lied inside. On attempt to removed it from the safe, they were %s. "
};

// Where the users answers will be stored
typedef struct
{
	char name[128];
	char location[128];
	char date[128];
	char time[128];
} Answers;

// Where portions of the story will be stored
typedef struct
{
	char* intro;
	char* begin;
	char* middle;
	char* end;
	
	char* structure;
	char* weapon;
	char* enemy;
	char* treasure;
	char* trap;
} Story;

// Generate a psuedo-random number ( 0 <= num < max )
int Random(int max)
{
	srand(time(NULL));
	return rand() % max;
};

// Geneare the story and print to console
void GenerateStory(Answers* answers)
{
	// Story parts
	Story story;
	
	// Pick random parts of the story
	story.intro = introductions[Random(MAX_INTRO)];
	story.begin = beginnings[Random(MAX_BEGIN)];
	story.middle = middles[Random(MAX_MIDDLE)];
	story.end = endings[Random(MAX_END)];
	
	// Pick random subjects of the story
	story.structure = structures[Random(MAX_STRUCTURES)];
	story.weapon = weapons[Random(MAX_WEAPONS)];
	story.enemy = enemies[Random(MAX_ENEMIES)];
	story.treasure = treasure[Random(MAX_TREASURE)];
	story.trap = traps[Random(MAX_TRAPS)];
	
	// Print out the story
	printf(story.intro, answers->date, answers->time);
	printf(story.begin, answers->name, answers->location, story.structure);
	printf(story.middle, story.enemy, story.weapon);
	printf(story.end, story.treasure, story.trap);
};

int main()
{	
	// User answers
	Answers answers;

	// Ask and store user name
	printf("Please enter your name: ");
	gets(&answers.name);
	
	// Ask and store user travel location
	printf("Where would you like to travel: ");
	gets(&answers.location);
	
	// Ask and store user date
	printf("What date will this take place: ");
	gets(&answers.date);
	
	// Ask and store user time
	printf("What time will this take place: ");
	gets(&answers.time);
	
	printf("\n");
	
	// Generate and output story
	GenerateStory(&answers);

	return 0;
	
};
