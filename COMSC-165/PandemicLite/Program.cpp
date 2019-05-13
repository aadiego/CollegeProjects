#include "Game.h"
using namespace std;

// Function Prototypes
int parseCmdLineArgs(int, char*[]);
void displayHelpMessage(string);
string ToLower(string);

GameOptions options;

int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	try
	{
		if (!parseCmdLineArgs(argc, argv))
		{
			SetupGame(options);
		}
	}
	catch (exception ex)
	{
		cout << ex.what();
		ret = EXIT_FAILURE;
	}
	return ret;
}

int parseCmdLineArgs(int argc, char* argv[])
{
	int ret = 0;
	// Loop through each of the command line arguments, skipping 0 as it's the executable path and name.
	for (int count = 1; count < argc; ++count)
	{
		string key = ToLower(string(argv[count]));
		string value = "";
		if (count + 1 < argc)
		{
			value = string(argv[count + 1]);
		}
		if (key == "-seed")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'seed'; however, the argument value is empty.");
			}

			options.seed = stoul(value, nullptr, 0);
			++count;
		}
		else if(key == "-bluediseasename")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'bluediseasename'; however, the argument value is empty.");
			}

			options.BlueDiseaseName = value;
			++count;
		}
		else if (key == "-yellowdiseasename")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'yellowdiseasename'; however, the argument value is empty.");
			}

			options.YellowDiseaseName = value;
			++count;
		}
		else if (key == "-purplediseasename")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'purplediseasename'; however, the argument value is empty.");
			}

			options.PurpleDiseaseName = value;
			++count;
		}
		else if (key == "-reddiseasename")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'reddiseasename'; however, the argument value is empty.");
			}

			options.RedDiseaseName = value;
			++count;
		}
		else if (key == "-numberofepidemics")
		{
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'numberofepidemics'; however, the argument value is empty.");
			}

			const unsigned int epidemics = stoul(value, nullptr, 0);
			if (epidemics < 4 || epidemics > 6)
			{
				throw InvalidArgumentException("The number of Epidemics must be between 4 and 6.");
			}

			options.NumberOfEpidemics = epidemics;
			++count;
		}
		else
		{
			string ExecutablePathAndName = string(argv[0]);
			size_t pos = ExecutablePathAndName.rfind('\\', ExecutablePathAndName.length());
			if (pos != string::npos)
			{
				ExecutablePathAndName = ExecutablePathAndName.substr(pos + 1, ExecutablePathAndName.length() - 1);
			}
			displayHelpMessage(ExecutablePathAndName);
			ret = 1;
		}
	}
	return ret;
}

void displayHelpMessage(string ExecutableName)
{
	cout << "Usage: " << ExecutableName << " [-help | -?] [-seed <unsigned_int>] [-bluediseasename <string>] [-yellowdiseasename <string>] [-purplediseasename <string>] [-reddiseasename <string>] [-numberofepidemics [4 | 5 | 6]]" << endl << endl;
	cout << "-help | -?" << "\t\t" << "Displays this help message" << endl;
	cout << "-seed" << "\t\t\t" << "Sets the seed used by the random number generator. (optional)" << endl;
	cout << "-bluediseasename" << "\t" << "Sets the name for the Blue disease. (optional)" << endl;
	cout << "-yellowdiseasename" << "\t" << "Sets the name for the Yellow disease. (optional)" << endl;
	cout << "-purplediseasename" << "\t" << "Sets the name for the Purple disease. (optional)" << endl;
	cout << "-reddiseasename" << "\t\t" << "Sets the name for the Red disease. (optional)" << endl;
	cout << "-numberofepidemics" << "\t" << "Sets the number of epidemics in the Player deck. [4 =  Introductory (default) | 5 = Standard | 6 = Heroic] (optional)" << endl;
}

string ToLower(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::tolower);
	return ret;
}