#pragma once
#ifndef BOWLER_H
#define BOWLER_H

#include<iostream>
#include<string>
#include"Player.h"
#include"ClassesFunction.h"

using namespace std;
//Inheriting Player class...
class Bowler : public virtual Player
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
	Bowler()
	{
		this->type = "";
		this->wickets = 0;
		this->score = 0;
		this->bowl_score = 0;
	}
	//set Bowler type (Fast, Medium).
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
	//set bowler wickets.
	virtual void setPlayerWickets(int wickets)
	{
		this->wickets = (wickets >= 0 && wickets <= 10) ? wickets : 0;
	}
	//set bowler score he get
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
	//get bowler score.
	virtual int getPlayerScore() const
	{
		return this->score;
	}
	//get bowler wickets.
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
		return "BOWLER";
	}
	//return bowler type (Fast, Medium)
	virtual string getPlayerAttType() const
	{
		return this->type;
	}
	//display bowler name with id and type of player.
	virtual void displayPlayer()
	{
		cout << this->getPlayerName() << "\t\t" << this->getPlayerId() << "\t\t" << this->getPlayerType() << endl;
	}
	//display bowler name and score he run.
	virtual void displayPlayerBatStats()
	{
		cout << this->getPlayerName() << "\t\t" << this->score << "\t\t" << endl;
	}
	//a function of Bowler that will change the length where he bowl according to the power of the bowler.
	//good bowling power bowler will get less change but low power will get high deflection.
	void varyLength(int& length)
	{
		if (getPlayerBallPower() > 80)
		{
			length = length;
		}
		else if (getPlayerBallPower() > 70 && getPlayerBallPower() <= 80)
		{
			length += rand() % 3;
		}
		else if (getPlayerBallPower() > 60 && getPlayerBallPower() <= 70)
		{
			length += rand() % 5;
		}
		else if (getPlayerBallPower() > 50 && getPlayerBallPower() <= 60)
		{
			length += rand() % 6;
		}
		else
		{
			length += rand() % 9;
		}
	}
	//Fast bowler function that will swing the ball according to power.
	//more power will get more swing.
	void SWING(float& width)
	{
		if (getPlayerBallPower() <= 60)
		{
			width = width;
			return;
		}

		int random;
		if (getPlayerBallPower() > 80)
		{
			random = rand() % 10;
		}
		else if (getPlayerBallPower() > 70 && getPlayerBallPower() <= 80)
		{
			random = rand() % 6;
		}
		else if (getPlayerBallPower() > 60 && getPlayerBallPower() <= 70)
		{
			random = rand() % 3;
		}
		else
		{
			random = 0;
		}
		//if bowler bowl off side, then in swing, else out swing.
		if (width >= 1.5)
		{
			width -= (static_cast<float>(random) / 10);
		}
		else
		{
			width += (static_cast<float>(random) / 10);
		}
	}
	//bowler BOWL function.
	virtual void BOWL(int& length, float& width, string& bowlType, const bool& playerBat) override
	{
		int random;
		srand(time(0));
		//check if its not player batting
		if (!playerBat)
		{
			//if player bowling, then ask for length and width.
			cout << "\n\nEnter the distance(0-50) of the bowl you want to deliver... ";
			cin >> length;
			cout << "Enter the width(0-3.0) from the wicket... ";
			cin >> width;

		}
		else
		{
			//if CPU bowling, then randomly generate number 
			//length from 0-50.
			//width from 0.0-3.0(float)
			length = rand() % 51;
			//randomm number cannot generate float value, so randomly generate 30.
			//divide it 10 will give us point value.
			random = rand() % 30;
			//like if random is 24, then width would be 2.4.
			width = (static_cast<float>(random) / 10);
		}
		//change the length according with power.
		varyLength(length);
		//display the type of bowl 
		//(OFF SIDE, ON BODY, BOUNCER, YORKER, GOOD LENGTH).
		DisplayBowlType(length, width, bowlType);
		//if bowler is a fast bowler, then swing the ball.
		if(type == "FAST")
			SWING(width);

	}
	//BOWLER BATTING FUNCTION.
	virtual char BAT(const int& length, const float& width, const string& bowlType, const bool& playerBat) override
	{
		int choice;
		int randScore;
		bool strike = false;
		string looktype;

		srand(time(0));
		//store bowltype in simple term.
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
		//check if its player batting
		if (playerBat)
		{
			//if player bat, then ask if he wants to strike or not.
			cout << "\nSTRIKE?" << endl;
			cout << "\t\t1. Yes. \t\t2. No." << endl;
			cin >> choice;

			while (choice < 1 && choice > 2)
			{
				cin >> choice;
			}
			//if want to strike then, turn strike variable to true.
			if (choice == 1)	strike = true;
		}
		else
		{
			//if CPU batting.

			//if bowltype is wide, then leave the ball.
			if (bowlType == "WIDE")
			{
				strike == false;
			}
			else
			{
				//else check the bowl width and bowler strongpoint.
				if ((width >= 0 && width <= 1.0) || (getPlayerStrongPoint() == looktype))
				{
					//if bowl gets to hit the wickets or its bowler strongpoint, then strike the ball.
					strike = true;
				}
				else
				{
					//else generate randomly.
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
		//if bowler strikes the ball.
		if (strike)
		{
			//check batting power and then decide score.
			//if its bowler strong point.
			if (getPlayerStrongPoint() == looktype)
			{
				//randomly generate number
				randScore = rand() % 10;
				//if random number is greater than 7 (8,9), then it would be out, else generate score.
				if (randScore <= 7)
				{
					this->score += randScore % 5;
					//return int to char value.
					return scoreIntToChar(randScore % 5);
				}
				else
				{
					return scoreIntToChar(7);
				}
			}
			//if its player weakpoint, then chances of out would increase.
			else if (getPayerweakness() == looktype)
			{
				randScore = rand() % 50;
				//random number is less than 30.
				if (randScore < 30)
				{
					//in weakpoint, player would maximum get 1 score.
					//as says it is his weakpoint.
					this->score += (randScore % 2);
					return scoreIntToChar(randScore % 2);
				}
				else
				{
					//else return 'W' as wicket.
					return scoreIntToChar(7);
				}
			}
			//if the ball is a no ball, then there will be no out and he get random score.
			else if (looktype == "NOBALL")
			{
				randScore = rand() % 5;
				this->score += randScore;
				return scoreIntToChar(randScore);
			}
			else
			{
				//if none of the above, then common chances of out.
				randScore = rand() % 50;
				if (randScore < 35)
				{
					this->score += (randScore % 5);
					return scoreIntToChar(randScore % 5);
				}
				else
				{
					return scoreIntToChar(7);
				}
			}
		}
		//if bowler does not strike the ball.
		else
		{
			if (looktype == "WIDE")
			{
				return 'w';
			}
			else if (looktype == "NOBALL")
			{
				//leave no ball will result in zero score.
				return '0';
			}
			else if (looktype == "YORKER" && (width >= 0 && width <= 1.0))
			{
				//'W' as wickets as ball will hit the wicket if he leave the ball.
				return 'W';
			}
			else
			{
				return '0';
			}
		}
	}
};

#endif // !BOWLER_H
