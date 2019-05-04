#include "Game.h"
using namespace std;

// Function Prototypes
//void parseCmdLineArgs(int, char*[]);

//struct GameOptions
//{
//	unsigned int seed = 0;
//	string BlueDiseaseName = "Blue";
//	string YellowDiseaseName = "Yellow";
//	string PurpleDiseaseName = "Purple";
//	string RedDiseaseName = "Red";
//};

unsigned int seed = 123456789;

int main(int argc, char *argv[])
{
	SetupGame(seed);
	return 0;
}
