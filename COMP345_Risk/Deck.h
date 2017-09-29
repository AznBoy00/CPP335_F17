#pragma once
#include <string>
#include <vector>
using namespace std;

class Deck
{
public:
	Deck();
	~Deck();

	int numberOfCards;
	vector<Card> cardDeck;
	
	string print();
	string hand();
	Card draw();
	string exchange();
	string driver();
	void printdeck();
	void shuffle();
};

class Card
{
public:
	Card();
	Card(string c, string t);
	string getType(int card);

private:
	string country;
	string type;

};

