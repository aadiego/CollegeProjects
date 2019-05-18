#include <algorithm>
#include "Game.h"
#include "Stack.h"
#include "City.h"
#include "Disease.h"
#include "Card.h"
#include "Deck.h"
#include "BasePlayer.h"
#include "MedicRole.h"

City* CityLinkedList = nullptr;
Deck<PlayerCard>* PlayerCardDeck;
Deck<InfectionCard>* InfectionCardDeck;
MedicRole* Player;

int SetupGame(GameOptions options)
{
	// Store the options parameter to a global variable.
	globalGameOptions = options;

	// Initialize random with the provided seed value or from the system time.
	srand(options.seed == 0 ? time(nullptr) : options.seed);
	
	// Set the game variables
	infectionRateIndex = 0;
	totalOutbreaks = 0;

	// Create the Disease objects
	Disease Blue = Disease(options.BlueDiseaseName, BLUE_TEXT, BLUE_DISEASE);
	Disease Yellow = Disease(options.YellowDiseaseName, YELLOW_TEXT, YELLOW_DISEASE);
	Disease Purple = Disease(options.PurpleDiseaseName, PURPLE_TEXT, PURPLE_DISEASE);
	Disease Red = Disease(options.RedDiseaseName, RED_TEXT, RED_DISEASE);

	// Create the City objects
	City SanFrancisco = City("San Francisco", BLUE_TEXT, &Blue, nullptr);
	City Chicago = City("Chicago", BLUE_TEXT, &Blue, &SanFrancisco);
	City Atlanta = City("Atlanta", BLUE_TEXT, &Blue, &Chicago);
	City Montreal = City("Montreal", BLUE_TEXT, &Blue, &Atlanta);
	City Washington = City("Washington", BLUE_TEXT, &Blue, &Montreal);
	City NewYork = City("New York", BLUE_TEXT, &Blue, &Washington);
	City London = City("London", BLUE_TEXT, &Blue, &NewYork);
	City Madrid = City("Madrid", BLUE_TEXT, &Blue, &London);
	City Paris = City("Paris", BLUE_TEXT, &Blue, &Madrid);
	City Essen = City("Essen", BLUE_TEXT, &Blue, &Paris);
	City Milan = City("Milan", BLUE_TEXT, &Blue, &Essen);
	City StPetersburg = City("St. Petersburg", BLUE_TEXT, &Blue, &Milan);

	City LosAngeles = City("Los Angeles", YELLOW_TEXT, &Yellow, &StPetersburg);
	City MexicoCity = City("Mexico City", YELLOW_TEXT, &Yellow, &LosAngeles);
	City Miami = City("Miami", YELLOW_TEXT, &Yellow, &MexicoCity);
	City Bogota = City("Bogota", YELLOW_TEXT, &Yellow, &Miami);
	City Lima = City("Lima", YELLOW_TEXT, &Yellow, &Bogota);
	City Santiago = City("Santiago", YELLOW_TEXT, &Yellow, &Lima);
	City SaoPaulo = City("Sao Paulo", YELLOW_TEXT, &Yellow, &Santiago);
	City BuenosAires = City("Buenos Aires", YELLOW_TEXT, &Yellow, &SaoPaulo);
	City Lagos = City("Lagos", YELLOW_TEXT, &Yellow, &BuenosAires);
	City Kinshasa = City("Kinshasa", YELLOW_TEXT, &Yellow, &Lagos);
	City Johannesburg = City("Johannesburg", YELLOW_TEXT, &Yellow, &Kinshasa);
	City Khartoum = City("Khartoum", YELLOW_TEXT, &Yellow, &Johannesburg);

	City Algiers = City("Algiers", PURPLE_TEXT, &Purple, &Khartoum);
	City Cairo = City("Cairo", PURPLE_TEXT, &Purple, &Algiers);
	City Istanbul = City("Istanbul", PURPLE_TEXT, &Purple, &Cairo);
	City Moscow = City("Moscow", PURPLE_TEXT, &Purple, &Istanbul);
	City Tehran = City("Tehran", PURPLE_TEXT, &Purple, &Moscow);
	City Baghdad = City("Baghdad", PURPLE_TEXT, &Purple, &Tehran);
	City Riyadh = City("Riyadh", PURPLE_TEXT, &Purple, &Baghdad);
	City Karachi = City("Karachi", PURPLE_TEXT, &Purple, &Riyadh);
	City Mumbai = City("Mumbai", PURPLE_TEXT, &Purple, &Karachi);
	City Delhi = City("Delhi", PURPLE_TEXT, &Purple, &Mumbai);
	City Chennai = City("Chennai", PURPLE_TEXT, &Purple, &Delhi);
	City Kolkata = City("Kolkata", PURPLE_TEXT, &Purple, &Chennai);

	City Beijing = City("Beijing", RED_TEXT, &Red, &Kolkata);
	City Seoul = City("Seoul", RED_TEXT, &Red, &Beijing);
	City Shanghai = City("Shanghai", RED_TEXT, &Red, &Seoul);
	City Tokyo = City("Tokyo", RED_TEXT, &Red, &Shanghai);
	City HongKong = City("Hong Kong", RED_TEXT, &Red, &Tokyo);
	City Taipei = City("Taipei", RED_TEXT, &Red, &HongKong);
	City Osaka = City("Osaka", RED_TEXT, &Red, &Taipei);
	City Bangkok = City("Bangkok", RED_TEXT, &Red, &Osaka);
	City Jakarta = City("Jakarta", RED_TEXT, &Red, &Bangkok);
	City HoChiMinhCity = City("Ho Chi Minh City", RED_TEXT, &Red, &Jakarta);
	City Manila = City("Manila", RED_TEXT, &Red, &HoChiMinhCity);
	City Sydney = City("Sydney", RED_TEXT, &Red, &Manila);
	CityLinkedList = &SanFrancisco;

	// Set Neighbors
	SanFrancisco.setNeighbors({ &Chicago, &LosAngeles, &Manila, &Tokyo });
	Chicago.setNeighbors({ &SanFrancisco, &Montreal, &Atlanta, &MexicoCity, &LosAngeles });
	Atlanta.setNeighbors({ &Chicago, &Washington, &Miami });
	Montreal.setNeighbors({ &Chicago, &NewYork, &Washington });
	Washington.setNeighbors({ &Atlanta, &Montreal, &NewYork, &Miami });
	NewYork.setNeighbors({ &Washington, &Montreal, &London, &Madrid });
	London.setNeighbors({ &NewYork, &Essen, &Paris, &Madrid });
	Madrid.setNeighbors({ &NewYork, &London, &Paris, &Algiers, &SaoPaulo });
	Paris.setNeighbors({ &Madrid, &London, &Essen, &Milan, &Algiers });
	Essen.setNeighbors({ &London, &Paris, &StPetersburg, &Milan });
	Milan.setNeighbors({ &Paris, &Essen, &Istanbul });
	StPetersburg.setNeighbors({ &Essen, &Moscow, &Istanbul });

	LosAngeles.setNeighbors({ &MexicoCity, &SanFrancisco, &Chicago, &Sydney });
	MexicoCity.setNeighbors({ &LosAngeles, &Miami, &Bogota, &Lima, &Chicago });
	Miami.setNeighbors({ &Bogota, &MexicoCity, &Atlanta, &Washington });
	Bogota.setNeighbors({ &MexicoCity, &Miami, &SaoPaulo, &BuenosAires, &Lima });
	Lima.setNeighbors({ &MexicoCity, &Bogota, &Santiago });
	Santiago.setNeighbors({ &Lima });
	SaoPaulo.setNeighbors({ &BuenosAires, &Bogota, &Lagos, &Madrid });
	BuenosAires.setNeighbors({ &Bogota, &SaoPaulo });
	Lagos.setNeighbors({ &SaoPaulo, &Kinshasa, &Khartoum });
	Kinshasa.setNeighbors({ &Lagos, &Khartoum, &Johannesburg });
	Johannesburg.setNeighbors({ &Kinshasa, &Khartoum });
	Khartoum.setNeighbors({ &Johannesburg, &Kinshasa, &Lagos, &Cairo });

	Algiers.setNeighbors({ &Istanbul, &Cairo, &Madrid, &Paris });
	Cairo.setNeighbors({ &Algiers, &Istanbul, &Baghdad, &Riyadh, &Khartoum });
	Istanbul.setNeighbors({ &Moscow, &Baghdad, &Cairo, &Algiers, &Milan, &StPetersburg });
	Moscow.setNeighbors({ &Tehran, &Istanbul, &StPetersburg });
	Tehran.setNeighbors({ &Delhi, &Karachi, &Baghdad, &Moscow });
	Baghdad.setNeighbors({ &Tehran, &Karachi, &Riyadh, &Cairo, &Istanbul });
	Riyadh.setNeighbors({ &Cairo, &Baghdad, &Karachi });
	Karachi.setNeighbors({ &Riyadh, &Baghdad, &Tehran, &Delhi, &Mumbai });
	Mumbai.setNeighbors({ &Karachi, &Delhi, &Chennai });
	Delhi.setNeighbors({ &Kolkata, &Chennai, &Mumbai, &Karachi, &Tehran });
	Chennai.setNeighbors({ &Mumbai, &Delhi, &Kolkata, &Bangkok, &Jakarta });
	Kolkata.setNeighbors({ &Delhi, &Chennai, &Bangkok, &HongKong });

	Beijing.setNeighbors({ &Seoul, &Shanghai });
	Seoul.setNeighbors({ &Beijing, &Shanghai, &Tokyo });
	Shanghai.setNeighbors({ &Beijing, &Seoul, &Tokyo, &Taipei, &HongKong });
	Tokyo.setNeighbors({ &Seoul, &Shanghai, &Osaka, &SanFrancisco });
	HongKong.setNeighbors({ &Shanghai, &Taipei, &Manila, &HoChiMinhCity, &Bangkok, &Kolkata });
	Taipei.setNeighbors({ &Manila, &HongKong, &Shanghai, &Osaka });
	Osaka.setNeighbors({ &Taipei, &Tokyo });
	Bangkok.setNeighbors({ &HongKong, &HoChiMinhCity, &Jakarta, &Chennai, &Kolkata });
	Jakarta.setNeighbors({ &Bangkok, &HoChiMinhCity, &Sydney, &Chennai });
	HoChiMinhCity.setNeighbors({ &Jakarta, &Bangkok, &HongKong, &Manila });
	Manila.setNeighbors({ &Sydney, &HoChiMinhCity, &HongKong, &Taipei, &SanFrancisco });
	Sydney.setNeighbors({ &Jakarta, &Manila, &LosAngeles });

	InfectionCardDeck = new Deck<InfectionCard>(CityLinkedList, GetInfectionRate());
	for(int initialInfection = 0; initialInfection < 9; ++initialInfection)
	{
		int infectionRate = 1;
		if (initialInfection < 3)
		{
			infectionRate = 3;
		}
		else if (initialInfection < 6)
		{
			infectionRate = 2;
		}

		InfectionCard Card = InfectionCardDeck->draw(true);
		Card.DrawAction(infectionRate);
		InfectionCardDeck->discard(Card);
	}

	Player = new MedicRole("Medic", &Atlanta);
	PlayerCardDeck = new Deck<PlayerCard>(CityLinkedList, 2);
	for (int initialHand = 0; initialHand < 5; ++initialHand)
	{
		Player->AddPlayerCardToHand(PlayerCardDeck->draw(true));
	}
	PlayerCard::PreparePlayerDeck(PlayerCardDeck);

	return PlayGame();
}

int PlayGame()
{
	return EXIT_SUCCESS;
}

int IncrementOutbreaks()
{
	return ++totalOutbreaks;
}

int IncrementInfectionRate()
{
	if (infectionRateIndex < INFECTIONRATESIZE)
	{
		++infectionRateIndex;
	}
	return GetInfectionRate();
}

int GetInfectionRate()
{
	return INFECTIONRATE[infectionRateIndex];
}

int GetResearchStationCount()
{
	int ret = 0;
	City* nodePtr = CityLinkedList;
	while(nodePtr != nullptr)
	{
		if(nodePtr->hasResearchStation())
		{
			++ret;
		}
		nodePtr = nodePtr->nextNode;
	}
	return ret;
}

City* DrawBottomInfectionCard()
{
	City* ret;
	InfectionCard Card = InfectionCardDeck->drawBottom(true);
	Card.DrawAction(3);
	ret = Card.getCity();
	InfectionCardDeck->discard(Card);
	return ret;
}

bool IntensifyInfectionDeck()
{
	bool ret = false;

	InfectionCardDeck->shuffle(Deck<InfectionCard>::Discard);

	while(!InfectionCardDeck->isEmpty(Deck<InfectionCard>::Discard))
	{
		InfectionCard card = InfectionCardDeck->draw(true, Deck<InfectionCard>::Discard);
		InfectionCardDeck->discard(card, Deck<InfectionCard>::Draw);
	}

	return ret;
}

PlayerCard DrawPlayerCard()
{
	return PlayerCardDeck->draw();
}

bool DiscardPlayerCard(PlayerCard card)
{
	return PlayerCardDeck->discard(card);
}


City* getCityLinkedList()
{
	return CityLinkedList;
}

string GetStringInput(string prompt)
{
	string userInput;
	cout << prompt << ": ";
	getline(cin, userInput);
	return userInput;
}

bool GetDestinationFromInputString(City* &destination, string &userInput)
{
	bool ret = false;
	userInput = GetStringInput("Please enter a destination");

	if (ToLower(userInput) != "back")
	{
		do
		{
			City* currentNode = CityLinkedList;
			while (currentNode != nullptr)
			{
				if (ToLower(currentNode->getName()) == ToLower(userInput))
				{
					destination = currentNode;
					ret = true;
					break;
				}
				currentNode = currentNode->nextNode;
			}

			if(ret == false)
			{
				userInput = GetStringInput("Please enter a destination");
			}
		} while (ret == false);
	}
	return ret;
}

vector<City*> GetCitiesContainingResearchStations(City* excludeCurrentCity)
{
	vector<City*> ret;
	City* currentCity = CityLinkedList;
	while (currentCity != nullptr)
	{
		if (currentCity->hasResearchStation() && currentCity != excludeCurrentCity)
		{
			ret.push_back(currentCity);
		}
		currentCity = currentCity->nextNode;
	}
	return ret;
}


int GetNumericInput(int minValue, int maxValue, bool NonNegative, bool ReturnZeroBased)
{
	int ret = 0;
	string userInput;
	do
	{
		cout << "Please enter a value" << (minValue == INT_MIN && maxValue == INT_MAX ? (NonNegative ? " [non-negative]: " : ": ") : " [" + to_string(minValue) + "-" + to_string(maxValue) + "]: ");
		getline(cin, userInput);
	} while (!(IsNumeric(userInput, ret, NonNegative) && (minValue == INT_MIN || ret >= minValue) && (maxValue == INT_MAX || ret <= maxValue)));
	return ReturnZeroBased ? ret - 1 : ret;
}

bool IsNumeric(string &input, int &output, bool NonNegative)
{
	bool ret = true;
	for(char character : input)
	{
		if(!isdigit(character) && (NonNegative || character != '-'))
		{
			ret = false;
		}
	}

	output = INT_MIN;
	if(ret)
	{
		output = stoi(input);
	}

	return ret;
}

string ToLower(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::tolower);
	return ret;
}