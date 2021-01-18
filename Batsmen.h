#pragma once
#ifndef BATSMEN_H
#define BATSMEN_H

#include<iostream>
#include<string>
#include"Player.h"
#include"ClassesFunction.h"

using namespace std;

class Batsmen : public virtual Player
{
private:
	//string to store Bowler type (Fast, Medium)
	string type;
	//store wickets he get.
	int wickets;
	//store score.
	int score;
	//store score he get while bowling
	int bowl_score;
public:
	//Constructor to initialize members from zero.
	Batsmen()
	{
		this->type = "";
		this->score = 0;
		this->wickets = 0;
		this->bowl_score = 0;
	}

	//set BATSMEN type (HITTER, NORMAL).
	virtual void setPlayerType(string type)
	{
		this->type = type;
	}
	//set Score he run.
	virtual void setPlayerScore(int score)
	{
		//using ternary operator to store data.
		this->score = (score >= 0) ? score : 0;
	}
	//set batsmen wickets.
	virtual void setPlayerWickets(int wickets)
	{
		this->wickets = (wickets >= 0 && wickets <= 10) ? wickets : 0;
	}
	//set batsmen score he get
	virtual void setPlayerBowlScore(int bowl_score) override
	{
		this->bowl_score = (bowl_score >= 0) ? bowl_score : 0;
	}
	//update player score by a variable ranging 0-6;
	virtual void UpdatePlayerScore(int score)
	{
		this->score += (score >= 0 && score <= 6) ? score : 0;
	}
	//update player wickets by 1(default)
	virtual void UpdatePlayerWickets(int wickets = 1)
	{
		//check if wickets are in limits 0-10
		if (wickets >= 0 && wickets <= 10)
		{
			// a bowler can only take 10 wickets in a match(max).
			if (this->wickets + wickets < 11)
			{
				this->wickets += wickets;
			}
			else
			{
				this->wickets = 10;
			}
		}
	}
	//update bowl_score he get while bowling
	virtual void UpdatePlayerBowlScore(int score = 1) override
	{
		this->bowl_score += (score >= 0) ? score : 0;
	}
	//get batsmen score.
	virtual int getPlayerScore() const
	{
		return this->score;
	}
	//get batsmen wickets.
	virtual int getPlayerWickets() const
	{
		return this->wickets;
	}
	//get bowl_score
	virtual int getPlayerBowlScore() const override
	{
		return this->bowl_score;
	}
	//return player type to check if player is a Bowler, batsmen or allrounder
	virtual string getPlayerType() const
	{
		return "BATSMEN";
	}
	//return bastmen type (Hitter, Normal)
	virtual string getPlayerAttType() const
	{
		return this->type;
	}
	//display batsmen name with id and type of player.
	virtual void displayPlayer()
	{
		cout << this->getPlayerName() << "\t\t" << this->getPlayerId() << "\t\t" << this->getPlayerType() << endl;
	}
	//display batsmen name and score he run.
	virtual void displayPlayerBatStats()
	{
		cout << this->getPlayerName() << "\t\t" << this->score << "\t\t" << endl;
	}

	void varyLength(int& length)
	{
		srand(time(0));
		if (getPlayerBallPower() > 40 && getPlayerBallPower() <= 50)
		{
			length += rand() % 10;
		}
		else if (getPlayerBallPower() > 30 && getPlayerBallPower() <= 40)
		{
			length += rand() % 13;
		}
		else if (getPlayerBallPower() > 20 && getPlayerBallPower() <= 30)
		{
			length += rand() % 16;
		}
		else
		{
			length += rand() % 20;
		}
	}

	virtual void BOWL(int& length, float& width, string& bowlType, const bool& playerBat) override
	{
		int random;
		srand(time(0));
		if (!playerBat)
		{
			cout << "\n\nEnter the distance(0-50) of the bowl you want to deliver... ";
			cin >> length;
			cout << "Enter the width(0-3.0) from the wicket... ";
			cin >> width;

		}
		else
		{
			length = rand() % 60;
			random = rand() % 40;
			width = (static_cast<float>(random) / 10);
		}

		varyLength(length);

		DisplayBowlType(length, width, bowlType);
	}

	virtual char BAT(const int& length, const float& width, const string& bowlType, const bool& playerBat) override
	{
		int choice;
		int randScore;
		bool strike = false;
		string looktype;

		srand(time(0));

		if (bowlType == "OFF SIDE BOUNCER" || bowlType == "BOUNCER")
		{
			looktype = "BOUNCER";
		}
		else if (bowlType == "OFF SIDE GOODLENGTH" || bowlType == "GOODLENGTH")
		{
			looktype = "GOODLENGTH";
		}
		else if (bowlType == "WIDE YORKER" || bowlType == "TOE CRUSHER")
		{
			looktype = "YORKER";
		}
		else
		{
			looktype = bowlType;
		}

		if (playerBat)
		{
			cout << "\nSTRIKE?" << endl;
			cout << "\t\t1. Yes. \t\t2. No." << endl;
			cin >> choice;

			while (choice < 1 && choice > 2)
			{
				cin >> choice;
			}

			if (choice == 1)	strike = true;
		}
		else
		{
			if (bowlType == "WIDE")
			{
				strike == false;
			}
			else if (getPlayerBatPower() >= 60)
			{
				strike = true;
			}
			else
			{
				if ((width >= 0 && width <= 1.0) || (getPlayerStrongPoint() == looktype))
				{
					strike = true;
				}
				else
				{
					randScore = rand() % 2;
					if (randScore == 1)
					{
						strike = true;
					}
					else
					{
						strike = false;
					}
				}
			}
		}

		if (strike)
		{
			if (getPlayerBatPower() > 80)
			{
				if (getPlayerStrongPoint() == looktype)
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else if (getPayerweakness() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 46)
					{
						this->score += (randScore % 5);
						return scoreIntToChar(randScore % 5);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (looktype == "NOBALL")
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else
				{
					randScore = rand() % 100;
					if (randScore <= getPlayerBatPower())
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
			}
			else if (getPlayerBatPower() > 70 && getPlayerBatPower() <= 80)
			{
				if (getPlayerStrongPoint() == looktype)
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else if (getPayerweakness() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 44)
					{
						this->score += (randScore % 5);
						return scoreIntToChar(randScore % 5);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (looktype == "NOBALL")
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else
				{
					randScore = rand() % 100;
					if (randScore <= getPlayerBatPower())
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
			}
			else if (getPlayerBatPower() > 60 && getPlayerBatPower() <= 70)
			{
				if (getPlayerStrongPoint() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 47)
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (getPayerweakness() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 43)
					{
						this->score += (randScore % 4);
						return scoreIntToChar(randScore % 4);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (looktype == "NOBALL")
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else
				{
					randScore = rand() % 100;
					if (randScore <= getPlayerBatPower())
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
			}
			else if (getPlayerBatPower() > 50 && getPlayerBatPower() <= 60)
			{
				if (getPlayerStrongPoint() == looktype)
				{
					randScore = rand() % 9;
					if (randScore <= 7)
					{
						this->score += randScore % 7;
						return scoreIntToChar(randScore%7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (getPayerweakness() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 40)
					{
						this->score += (randScore % 3);
						return scoreIntToChar(randScore % 3);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (looktype == "NOBALL")
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else
				{
					randScore = rand() % 100;
					if (randScore <= getPlayerBatPower())
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
			}
			else
			{
				if (getPlayerStrongPoint() == looktype)
				{
					randScore = rand() % 10;
					if (randScore < 7)
					{
						this->score += randScore % 7;
						return scoreIntToChar(randScore%7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (getPayerweakness() == looktype)
				{
					randScore = rand() % 50;
					if (randScore < 38)
					{
						this->score += (randScore % 2);
						return scoreIntToChar(randScore % 2);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
				else if (looktype == "NOBALL")
				{
					randScore = rand() % 7;
					this->score += randScore;
					return scoreIntToChar(randScore);
				}
				else
				{
					randScore = rand() % 100;
					if (randScore <= getPlayerBatPower())
					{
						this->score += (randScore % 7);
						return scoreIntToChar(randScore % 7);
					}
					else
					{
						return scoreIntToChar(7);
					}
				}
			}
		}
		else
		{
			if (looktype == "WIDE")
			{
				return 'w';
			}
			else if (looktype == "NOBALL")
			{
				return '0';
			}
			else if (looktype == "YORKER" && (width >= 0 && width <= 1.0))
			{
				return 'W';
			}
			else
			{
				return '0';
			}
		}
	}
};

#endif // !BATSMEN_H
