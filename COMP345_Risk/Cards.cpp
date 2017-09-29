#include "Cards.h"
#include "GameConstants.h"
#include <iostream>
using namespace std;

Cards::Cards() {
}

Cards::Cards(int type, int id, int location) {
	this->type = type;
	this->cardID = id;
	this->location = location;
}

int Cards::getId() {
	return this->cardID;
}

int Cards::getType() {
	return this->type;
}

int Cards::getCardLocation() {
	return this->location;
}

void Cards::setCardLocation(int handId) {
	this->location = handId;
}

Deck::Deck() {
	for (size_t i = 0; i < DECK_SIZE; i++) {
		if (i < CARDS_PER_TYPE) {
			cards[i] = Cards(1, i + 1, 0);
		}
		else if (i < 2 * CARDS_PER_TYPE) {
			cards[i] = Cards(2, i + 1, 0);
		}
		else if (i < 3 * CARDS_PER_TYPE) {
			cards[i] = Cards(3, i + 1, 0);
		}
	}
	//debug display deck array
	showCardsInDeck();
}

void Deck::showCardsInDeck() {
	cout << "Deck card content:" << endl;
	for (size_t i = 0; i < DECK_SIZE; i++) {
		if (this->cards[i].getCardLocation() == 0) {
			cout << "Card ID at position " << i << " (TYPE-ID): " << this->cards[i].getType() << this->cards[i].getId() << endl;
		}
	}
}

void Hand::showCardsInHand(int handId, Deck deck) {
	cout << "Player " << handId << "'s hand:" << endl;
	for (size_t i = 0; i < 42; i++) {
		if (deck.cards[i].getCardLocation() == handId) {
			cout << "Card ID at position " << i << " (TYPE-ID): " << deck.cards[i].getType() << deck.cards[i].getId() << endl;
		}
	}
}

void Deck::draw(int handId) {
	cout << "Drawing cards for player " << handId << endl;
	for (int i = 0; i < DECK_SIZE; i++) {
		if (this->cards[i].getCardLocation() == 0) {
			this->cards[i].setCardLocation(handId);
			break;
		}
	}
}

Hand::Hand(int id) {
	this->id = id;
}
