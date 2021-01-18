#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include<string>
using namespace std;

class Player
{
private:
	//string to store player name
	string name;
	//int to store player id.
	int id;
	//store batting power of the player.
	int battingpower;
	//store bowling power of the player.
	int bowlingpower;
	//store player weakness
	string weakness;
	//store player Strongpoint
	string strongpoint;
public:
	//constructor to initialize data members from zero or null.
	Player();
	
	//setters for every data member
	void setPlayerName(string);
	void setPlayerId(int);
	void setPlayerBatPower(int);
	void setPlayerBallPower(int);
	void setPlayerWeakness(string);
	void setPlayerStrongPoint(string);

	//getter for every data member;
	string getPlayerName() const;
	int getPlayerId() const;
	int getPlayerBatPower() const;
	int getPlayerBallPower() const;
	string getPayerweakness() const;
	string getPlayerStrongPoint() const;

	//virtual functions to be implemented in each derived class,
	//because each type of player has its own function.
	virtual void setPlayerType(string) = 0;
	virtual void setPlayerScore(int) = 0;
	virtual void setPlayerWickets(int) = 0;
	virtual void setPlayerBowlScore(int) = 0;

	virtual void UpdatePlayerScore(int) = 0;
	virtual void UpdatePlayerWickets(int = 1) = 0;
	virtual void UpdatePlayerBowlScore(int = 1) = 0;

	virtual int getPlayerScore() const = 0;
	virtual int getPlayerWickets() const = 0;
	virtual int getPlayerBowlScore() const = 0;
	virtual string getPlayerAttType() const = 0;
	virtual string getPlayerType() const = 0;

	virtual void displayPlayer() = 0;
	virtual void displayPlayerBatStats() = 0;

	virtual void BOWL(int&, float&, string&, const bool&) = 0;
	virtual char BAT(const int&, const float&, const string&, const bool&) = 0;
};

#endif // !PLAYER_H
