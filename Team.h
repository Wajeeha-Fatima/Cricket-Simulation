#pragma once
#ifndef TEAM_H
#define TEAM_H

#include<string>
#include"Player.h"
using namespace std;

class Team
{
	//store team name
	string name;
	//store team total score
	int team_score;
	//store team total wickets
	int team_wickets;
public:
	//A team has a player(composition relationship)
	Player *playing[11];
	//Initialize variables by 0
	Team();
	~Team();
	//setters
	//set the name of the team
	void SetTeamName(string);
	//set the score scored by the team
	void SetTeamScore(int);
	//set the wickets of the team
	void SetTeamWickets(int);
	//set the player attributes 
	//::int at last will be the index of the player...
	void SetPlayer(string, int, string, string, int, int, string, string, int);

	//getters
	//return the name of the team.
	string getTeamName() const;
	//return the total score scored by the team.
	int getTeamScore() const;
	//return the wickets of the team.
	int getTeamWickets() const;


	//a function which will automatically calculates the total team score
	//by adding their player scores
	void AutoTeamScore();

	//display the team and player names...
	void displayTeam();

	//display team stats.
	void displayTeamBatStats();
};

#endif // !TEAM_H
