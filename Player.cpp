#include<iostream>
#include<string>
#include"Player.h"

using namespace std;

//Constructor to initialize data memebers to zero .
Player::Player()
{
	this->name = "";
	this->id = 0;
	this->battingpower = 0;
	this->bowlingpower = 0;
	this->weakness = "";
	this->strongpoint = "";
}
//set Name of the player
void Player::setPlayerName(string name)
{
	this->name = name;
}
//set ID of the player
void Player::setPlayerId(int id)
{
	this->id = (id >= 0) ? id : 0;
}
//set Batting power of the player
void Player::setPlayerBatPower(int power)
{
	this->battingpower = (power >= 0 && power <= 100) ? power : 0;
}
//set Bowling power of the player
void Player::setPlayerBallPower(int power)
{
	this->bowlingpower = (power >= 0 && power <= 100) ? power : 0;
}
//set player weakness
void Player::setPlayerWeakness(string weakness)
{
	this->weakness = weakness;
}
//set Player strongpoint .
void Player::setPlayerStrongPoint(string strong)
{
	this->strongpoint = strong;
}
//get Player name.
string Player::getPlayerName() const
{
	return this->name;
}
//gey Player ID.
int Player::getPlayerId() const
{
	return this->id;
}
//get Player batting power.
int Player::getPlayerBatPower() const
{
	return this->battingpower;
}
//get Player Bowling power.
int Player::getPlayerBallPower() const
{
	return this->bowlingpower;
}
//get Player Weakness
string Player::getPayerweakness() const
{
	return this->weakness;
}
//get Player strongpoint
string Player::getPlayerStrongPoint() const
{
	return this->strongpoint;
}