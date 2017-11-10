#include "Player.h"
#include "Dice.h"
#include "Time.h"
#include <algorithm>
#include <iostream>
using namespace std;

Player::Player(int newId) {
	strategy = NULL;
	dice = new Dice();
	id = newId;
	//cout << "\nDice object for player id: " << id << " created." << endl;//debug
	/*diceRolled = 0;
	diceDistribution[0] = 0;
	diceDistribution[1] = 0;
	diceDistribution[2] = 0;
	diceDistribution[3] = 0;
	diceDistribution[4] = 0;
	diceDistribution[5] = 0;*/
	cout << "Player id: " << id << " created." << endl; //debug
}

Player::~Player() {
}

Dice Player::getDice() {
	return *dice;
}

int Player::getId() {
	return id;
}

void Player::setId(int newId) {
	id = newId;
}

int Player::getDiceRolled() {
	return diceRolled;
}

void Player::setDiceRolled(int dice) {
	diceRolled = dice;
}

//Executes the turn
void Player::executeTurn(Map *map, Deck* deck, vector<Player*> playerVector, Game* game) {
	game->Notify();
	//strategy->reinforce(map, deck);
	/*strategy->attack(map, playerVector);
	if (conquered) {
		game->Notify();
		conquered = false;
	}*/
	strategy->fortify();
}

void Player::setStrategy(Strategy* strat) {
	this->strategy = strat;
}

void Player::showStats(Deck* deck) {
	//double nominator;
	//double denominator;
	cout << "\nPlayer ID: " << getId() << endl;
	cout << "Player hand: " << endl;
	deck->showCardsInHand(getId(), deck);
	getDice().showStats();
}


Player*::Player::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
			return playerVector.at(i);
		}
	}
	cout << "Player not found, error! Program will exit." << endl;
	exit(1);
}


void Player::setTurnNumber(int t) {
	turnNumber = t;
}

int Player::getTurnNumber() {
	return turnNumber;
}
