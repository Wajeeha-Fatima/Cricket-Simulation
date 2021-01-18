#include"Team.h"
#include<iostream>
#include<string.h>
#include"Player.h"
#include"Bowler.h"
#include"Batsmen.h"
#include"Allrounder.h"

using namespace std;
//COnstructor
Team::Team()
{
	this->name = " ";
	this->team_score = 0;
	this->team_wickets = 0;
}
//destructor
Team::~Team()
{
	
}
//set team name
void Team::SetTeamName(string name)
{
	this->name = name;
}
//set team total score
void Team::SetTeamScore(int score)
{
	this->team_score = (score > 0) ? score : 0;
}
//set team total wickets
void Team::SetTeamWickets(int wickets)
{
	this->team_wickets = (wickets >= 0 && wickets <= 10) ? wickets : 0;
}
//set Player by index out of 11.
void Team::SetPlayer(string name, int id, string type, string p_type, int batpower, int ballpower, string weakness, string strongness, int playerNo)
{
	//check if index is 0-10
	if (playerNo >= 0 && playerNo < 11)
	{
		//point towards the type of the player
		//if type = "BOWLER", then it will inherit Bowler class
		if(type == "BOWLER")
			playing[playerNo] = new Bowler;
		else if(type == "BATSMEN")
			playing[playerNo] = new Batsmen;
		else
			playing[playerNo] = new AllRounder;

		//set player name, id, type, powers
		playing[playerNo]->setPlayerName(name);
		playing[playerNo]->setPlayerId(id);
		playing[playerNo]->setPlayerType(p_type);
		playing[playerNo]->setPlayerBatPower(batpower);
		playing[playerNo]->setPlayerBallPower(ballpower);
		playing[playerNo]->setPlayerWeakness(weakness);
		playing[playerNo]->setPlayerStrongPoint(strongness);
	}
}

string Team::getTeamName() const
{
	return this->name;
}

int Team::getTeamScore() const
{
	return this->team_score;
}

int Team::getTeamWickets() const
{
	return this->team_wickets;
}

void Team::displayTeam()
{
	cout << this->name << ": " << endl;
	for (int i = 0; i < 11; i++)
	{
		this->playing[i]->displayPlayer();
	}
}
//this function will add all player batting score and set it to team score, extras score will not be count.
void Team::AutoTeamScore()
{
	team_score = 0;
	for (int i = 0; i < 11; i++)
	{
		team_score += playing[i]->getPlayerScore();
	}
}

void Team::displayTeamBatStats()
{
	cout << this->name << ": " << endl;
	for (int i = 0; i < 11; i++)
	{
		this->playing[i]->displayPlayerBatStats();
	}
	AutoTeamScore();
	cout << "Score: \t\t" << this->team_score << "/" << this->team_wickets << endl;
}