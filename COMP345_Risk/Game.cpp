#include <iostream>
#include <vector>
#include "Game.h"
#include "Cards.h"
#include "time.h"
#include "UserStrategy.h"
#include <dirent.h>


Game::Game() {
	
	startGame();
}

void Game::selectMap() {
	// Initialize main data.
	
	
	struct dirent *directory;
	cout << "Select a map from the list: ";
	DIR* mapDir = opendir("./Map Files/");
	int mapNumber = 0;
	vector<string> mapList;

	// Initialize maps
	if (mapDir) {
		while ((directory = readdir(mapDir)) != NULL) {
			mapList.push_back(directory->d_name);
			cout << mapNumber + 1 << " - " << directory->d_name << endl;
			mapNumber++;
		}
		int mapChoice;
		cin >> mapChoice;
		loadedMap = new MapLoader(mapList.at(mapChoice - 1));
		closedir(mapDir);
	}
}

void Game::initializePlayers() {
	// Initialize player data.
	do {
cout << "How many players are in the game? (2-6)";
cin >> numOfPlayers;
if (numOfPlayers < 2 || numOfPlayers > 6) {
	cout << "Entered number of players not within accepted range." << endl;
}
	} while (numOfPlayers < 2 || numOfPlayers > 6);

	for (int i = 0; i < numOfPlayers; i++) {
		playerVector.push_back(new Player(i + 1));
	}
}

void Game::assignTurns() {
	//Turn assignment
	for (int i = 1; i <= numOfPlayers; i++) {
		int rando;
		rando = rand() % numOfPlayers; //generate random number
		while (playerVector.at(rando)->getTurnNumber() != 0) { //if that player has already been assigned a number, regenerate
			rando = rand() % numOfPlayers;
		}
		playerVector.at(rando)->setTurnNumber(i); //assign that turn number to the player
		cout << "Player " << rando + 1 << " with turn number " << i << endl;
	}

	cout << "Rearranging player order" << endl;
	for (int i = 0; i < numOfPlayers; i++) {
		for (int j = 0; j < numOfPlayers; j++) {
			if (playerVector.at(j)->getTurnNumber() == i + 1) {
				turnVector.push_back(playerVector[j]);
			}
		}

	}
}

void Game::assignCountries() {
	//country assignment
	int countryCount = 0;
	cout << "Number of countries is " << loadedMap->getMap()->getContainedCountriesInMap().size() << endl;
	//while all countries have not been allocated
	while (countryCount < loadedMap->getMap()->getContainedCountriesInMap().size()) {
		//allocating one country per player at a time (round-robin)
		for (int i = 0; i < numOfPlayers; i++) {
			int randomCountryNumber;
			randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size(); //generate random country number
			Country* assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			//if the country has already been allocated to someone, regenerate the number
			while (assignedCountry->getOwnerNumber() != 0) {
				randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size();
				assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			}
			assignedCountry->setOwnerNumber(i + 1); //set that country as owned by player i
			turnVector.at(i)->setOwnedCountry(assignedCountry); //add that country to list of owned countries
			countryCount++;
			cout << countryCount << " Country called " << assignedCountry->getNameOfCountry() << " is assigned to Player " << turnVector.at(i)->getId() << endl;
			if (countryCount == loadedMap->getMap()->getContainedCountriesInMap().size()) { //break out of loop when all countries have been allocated
				break;
			}
		}
	}
}

void Game::assignArmies() {
	//army assignment
	int numberOfArmies;
	numberOfArmies = 50 - (numOfPlayers * 5); //calculates number of armies per player
											  //for each player, add one army to each of their owned countries and all the remaining ones go to the last country
	for (int i = 0; i < numOfPlayers; i++) {
		int troopsPerPlayer = 0; //int to count how many armies each player has placed
		for (int j = 0; j < turnVector.at(i)->getOwnedCountries().size(); j++) {
			if (j == turnVector.at(i)->getOwnedCountries().size() - 1) {
				turnVector.at(i)->getOwnedCountries().at(j)->setNumberOfTroops(numberOfArmies - j);
				troopsPerPlayer += numberOfArmies - j;
				cout << "Country " << turnVector.at(i)->getOwnedCountries().at(j)->getNameOfCountry() << " has " << turnVector.at(i)->getOwnedCountries().at(j)->getNumberOfTroops() << endl;
			}
			else {
				turnVector.at(i)->getOwnedCountries().at(j)->setNumberOfTroops(1);
				troopsPerPlayer += 1;
				cout << "Country " << turnVector.at(i)->getOwnedCountries().at(j)->getNameOfCountry() << " has " << turnVector.at(i)->getOwnedCountries().at(j)->getNumberOfTroops() << endl;
			}
		}
		cout << "Player " << turnVector.at(i)->getId() << " has placed " << troopsPerPlayer << " troops." << endl;
	}
}

void Game::startGame() {

	srand(time(0));
	winnerId = -1;

	selectMap();
	initializePlayers();
	assignTurns();
	assignCountries();
	assignArmies();

	// Create deck and cards
	Deck* playDeck = new Deck();

	// Run every steps of the game here.
	for (int i = 0; i < turnVector.size(); i++){
	turnVector[i]->setStrategy(new UserStrategy(turnVector[i]));
}
	while (winnerId == -1) {

		for (int i = 0; i < turnVector.size(); i++) {
			int turnNumber = turnVector[i]->getId();
			cout << "------------------------------------------" << endl;
			cout << "IT'S PLAYER " << turnVector.at(i)->getId() << "'S TURN!" << endl;
			cout << "------------------------------------------" << endl;
			cout << "Reinforcement phase for player " << turnNumber << endl;
			/*turnVector.at(i)->reinforce(loadedMap->getMap(), playDeck);
			cout << "Attack phase for player " << turnNumber << endl;
			turnVector.at(i)->attack(loadedMap->getMap(), playerVector);
			cout << "Fortification phase for player " << turnNumber << endl;
			turnVector.at(i)->fortify();*/
			turnVector.at(i)->executeTurn(loadedMap->getMap(), playDeck, playerVector);
		}
		winnerId = 1;
	}

	cout << "\nThe winner is Player " << winnerId << ". Congratulations!" << endl;
}