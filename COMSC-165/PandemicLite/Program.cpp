#include "Game.h"
using namespace std;

// Function Prototypes
//void parseCmdLineArgs(int, char*[]);

GameOptions options = { 1234567890, "GAIDS", "Glitter", "CodA", "Applause", 4 };

int main(int argc, char *argv[])
{
	int exitCode = SetupGame(options);
	return exitCode;
}
