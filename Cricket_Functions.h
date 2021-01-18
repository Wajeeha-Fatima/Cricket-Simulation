#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include"Team.h"
#include"Player.h"

using namespace std;

void CreatePlayer(const string&);

void to_upper(string& name)
{
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] >= 97 && name[i] <= 122)
		{
			name[i] -= 32;
		}
	}
}

bool isValidName(const string& name)
{
	bool check = false;
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] >= 65 && name[i] <= 90 || name[i] >= 97 && name[i] <= 122)
		{
			check = true;
		}
		else
		{
			check = false;
			break;
		}
	}
	return check;
}
//display menu on screen and get user input.
void menu(int& choice)
{
	cout << endl << endl ;
	cout << "\t\t\t**************************" << endl;
	cout << "\t\t\t1. Choose a Team." << endl;
	cout << "\t\t\t2. Create your own Team." << endl;
	cout << "\t\t\t3. Exit." << endl;
	cout << "\t\t\t";
	cin >> choice;
	//check if user input anything else 1,2,3
	while (choice < 1 || choice > 3)
	{
		cout << "\t\t\t";
		cin >> choice;
	}
}
//a complete Functionality on create team...
void CreateTeam(string& team_name)
{
	bool team_allocate;
	ifstream in;
	ofstream out;
	do
	{
		//bool value to check if user enter team name already exist or not...
		team_allocate = true;
		cout << "Please Enter your team name: ";
		cin >> team_name;	//ask user to enter team name...
		//check if team name is proper(Only alphabets...).
		while (!isValidName(team_name))
		{
			cout << "Team Name not Valid!!!" << endl;
			cout << "Enter Team Name: ";
			cin >> team_name;
		}
		//transform the team name to upper case.
		to_upper(team_name);
		//open file 'ALL_TEAM.txt' and add team name their.
		in.open("TEAMS/ALL_TEAMS.txt");
		//if fail to open file, then exit.
		if (in.fail())
		{
			cout << "ERROR IN DATABASE!!!" << endl;
			exit(0);
		}
		else
		{
			string temp;
			while (!in.eof())
			{
				in >> temp;
				//read name from file, if name already exist, then ask user to enter name again...
				if (temp == team_name)
				{
					cout << "TEAM ALREADY EXIST!!!" << endl;
					team_allocate = false;
					break;
				}
			}
			in.close();
		}
	} while (team_allocate == false);
	//open file to add name...
	out.open("TEAMS/ALL_TEAMS.txt", fstream::app);
	out << "\n";
	out<< team_name;
	out.close();

	int check = 0;

	//loop to ask user to add player in your team...
	do
	{
		system("cls");
		//CREATE PLAYER FUNCTIONALITY()....
		CreatePlayer(team_name);
		system("cls");
		cout << "1 Player added.\nYou want to create another one?." << endl;
		cout << "\t\t1. Yes.\t\t2. No." << endl;
		cin >> check;	//ask user if he again wants to add a player....

		while (check < 1 || check > 2)
		{
			cin >> check;
		}
	} while (check == 1);
}
//Create a player on a team given as team_name...
void CreatePlayer(const string& team_name)
{
	ofstream write;
	string name;
	int id;
	string ptype;
	string btype;
	int batpower;
	int ballpower;
	string weakness;
	string strongpoint;
	int check_counter;
	string filename = "TEAMS/" + team_name + ".txt";
	//ask for attributes of Player(name, id, type, bat/ball power, weak/strong point)...
	cout << "Fill these attributes..." << endl;
	cout << "Name: ";
	cin >> name;
	cout << "ID: ";
	cin >> id;
	
	cout << "1. Batsmen.\t\t2. Bowler.\t\t3. AllRounder." << endl;
	cin >> check_counter;
	//bound check
	while (check_counter < 1 || check_counter > 3)
	{
		cin >> check_counter;
	}
	
	if (check_counter == 1 || check_counter == 3)
	{
		if(check_counter == 1)	ptype = "BATSMEN";
		else					ptype = "ALLROUNDER";
		//batsmen and allrounder check. He can be a hitter or Normal player.
		cout << "\t\t1. Hitter.\t\t2. Normal." << endl;
		cin >> check_counter;
		//bound check
		while (check_counter < 1 || check_counter > 2)
		{
			cin >> check_counter;
		}
		
		if (check_counter == 1)		btype = "HITTER";
		else						btype = "NORMAL";
	}
	else if (check_counter == 2)
	{
		ptype = "BOWLER";
		//a bowler can be fast or medium.
		cout << "\t\t1. Fast.\t\t2. Medium." << endl;
		cin >> check_counter;
		//bound check.
		while (check_counter < 1 || check_counter > 2)
		{
			cin >> check_counter;
		}

		if (check_counter == 1)		btype = "FAST";
		else						btype = "MEDIUM";
	}
	//ask for powers.
	cout << "Batting Power: ";
	cin >> batpower;

	if (ptype == "BATSMEN")
	{
		//batsmen can have 50-100 bat power.
		while (batpower < 50 || batpower > 100)
		{
			cout << "Batsmen shoulld have 50-100 bat power: ";
			cin >> batpower;
		}
	}
	else if (ptype == "BOWLER")
	{
		//bowler can have 0-50 bat power.
		while (batpower < 0 || batpower > 50)
		{
			cout << "Bowler can have 0-50 bat power: ";
			cin >> batpower;
		}
	}
	else
	{
		//all rounder can have 30-80 batpower.
		while (batpower < 30 || batpower > 80)
		{
			cout << "Allrounder can have 30-80 bat power:";
			cin >> batpower;
		}
	}

	cout << "Balling Power: ";
	cin >> ballpower;

	if (ptype == "BATSMEN")
	{
		//batsmen can have 0-50 ball power.
		while (ballpower < 0 || ballpower > 50)
		{
			cout << "Batsmen should have 0-50 ball power: ";
			cin >> ballpower;
		}
	}
	else if (ptype == "BOWLER")
	{
		//bowler can have 50-100 ball power.
		while (ballpower < 50 || ballpower > 100)
		{
			cout << "Bowler can have 50-100 ball power: ";
			cin >> ballpower;
		}
	}
	else
	{
		//all rounder can have 30-80 ball power.
		while (ballpower < 30 || ballpower >80)
		{
			cout << "Allrounder can have 30-80 ball power:";
			cin >> ballpower;
		}
	}
	//run the loop until weakness != strongpoint.
	//means, a player cannot have same weak and strong point.
	do
	{
		cout << "WEAKNESS: " << endl;
		cout << "\t\t1. Yorker.\t\t2. Good Length. \t\t3. Bouncer.\t\t4.No Weakness" << endl;
		cin >> check_counter;
		while (check_counter < 1 || check_counter > 4)
		{
			cin >> check_counter;
		}

		if (check_counter == 1)			weakness = "YORKER";
		else if (check_counter == 2)	weakness = "GOODLENGTH";
		else if (check_counter == 3)	weakness = "BOUNCER";
		else							weakness = "NOWEAKNESS";

		cout << "Strong Point: " << endl;
		cout << "\t\t1. Yorker.\t\t2. Good Length. \t\t3. Bouncer.\t\t4. No Strong Point" << endl;
		cin >> check_counter;
		while (check_counter < 1 && check_counter > 4)
		{
			cin >> check_counter;
		}

		if (check_counter == 1)			strongpoint = "YORKER";
		else if (check_counter == 2)	strongpoint = "GOODLENGTH";
		else if (check_counter == 3)	strongpoint = "BOUNCER";
		else							strongpoint = "NOSTRONGPOINT";

		if (weakness == strongpoint)
		{
			cout << "Player cannot have same weak and strong point...";
		}
	} while (strongpoint == weakness);
	//open the file of player team and append the attributes to the end.
	//fstream::out makes a new file if team file not present.
	//fstream::app append everything in the last. we don't now need to read all and then write again...
	write.open(filename.c_str(), fstream::out | fstream::app);

	write << name;
	write << "\t";
	write << id;
	write << "\t";
	write << ptype;
	write << "\t";
	write << btype;
	write << "\t";
	write << batpower;
	write << "\t";
	write << ballpower;
	write << "\t";
	write << weakness;
	write << "\t";
	write << strongpoint;
	write << endl;
	//close the file...
	write.close();
}
//check total teams available, written on "ALL_TEAMS.txt"
void CheckTotalTeams(string*& teams, int& total_Teams)
{
	ifstream in;
	string temp;
	//open the file for input.
	in.open("TEAMS/ALL_TEAMS.txt");
	//if file does not exist, then no team can be selected, so exit the game.
	if (in.fail())
	{
		cout << "ERROR FINDING THE TEAMS..." << endl;
		exit(0);
	}
	else
	{
		//if file opens.
		//total_teams count.
		total_Teams = 0;
		while (!in.eof())
		{
			//increase everytime if it found a team.
			in >> temp;
			// in >> PAKISTAN  -> total_teams = 1.
			// in >> ANYTEAM   -> total_teams = 2.
			total_Teams++;
		}
		//close the file.
		in.close();
		//if no team present inn class, then exit the game.
		if (total_Teams == 0)
		{
			exit(0);
		}

		//generate a pointer array to store all team names present in 'ALL_TEAMS.txt'.
		teams = new string[total_Teams];
		//again open the file.
		in.open("TEAMS/ALL_TEAMS.txt");

		for (int i = 0; i < total_Teams; i++)
		{
			//this time, every team name will be stored in the array.
			in >> teams[i];
			//first time   teams[0] = "PAKISTAN".
			//next time		teams[1] = "ANYTEAM".
		}
		//closing the file.
		in.close();
	}
}
//check if file has at least 11 players.
bool CheckTeam11Players(const string& filename)
{
	bool can_play;
	int count = 0;
	string players;
	ifstream input;

	input.open(filename.c_str());

	if (input.fail())
	{
		cout << "ERROR 404..." << endl;
		exit(0);
	}

	while (!input.eof())
	{
		//read the whole line at once...
		getline(input, players);
		//after reading a line, increase player count.
		count++;
	}
	//close the file.
	input.close();
	//check if count of player is greater than 10.
	if (count >= 11)
	{
		can_play = true;
	}
	else
	{
		can_play = false;
	}
	//return true if file has at least 11 players, else return false,
	return can_play;
}
//display aal teams, and ask user to select 1.
void chooseTeam(string& team_name, const string* all_teams, const int& total_teams)
{
	int choice;

	cout << "Please choose your Team..." << endl;
	//display all the teams present.
	for (int i = 0; i < total_teams; i++)
	{
		cout << i + 1 << ". " << all_teams[i] << endl;
	}
	//take input from user.
	cin >> choice;
	//check for irrelevent input.
	while (choice < 1 || choice > total_teams)
	{
		cin >> choice;
	}
	//team name would be the selected team.
	//i.e if choice == 1. -> all_teams[0] = "PAKISTAN" . then team name will be stored in that variable.
	team_name = all_teams[choice-1];
}

void selectOver(int& overs)
{
	//ask user for total over he wants to play.
	cout << "Please enter the number of overs you want to play?. ";
	cin >> overs;
	//total overs can range 0-50...
	while (overs <= 0 || overs > 50)
	{
		cout << "INVALID INPUT!!!" << endl;
		cout << "PLEASE ENTER NUMBER OF OVERS... ";
		cin >> overs;
	}
}
//generate 2d array of total length [over][6]...
char** generateOvers(const int& over)
{
	char** overslength;

	overslength = new char* [over];

	for (int i = 0; i < over; i++)
	{
		overslength[i] = new char[6];
	}
	//return the pointer.
	return overslength;
}
//toss fucntion to decide user bat or ball.
void TOSS(bool& playerbatting)
{
	int choice;

	cout << "Please choose from the following... \n" << endl;
	cout << "\t1. HEAD.\t\t";
	cout << "2. TAIL." << endl;
	cin >> choice;

	while (choice < 1 || choice > 2)
	{
		cout << "[+]INVALID CHOICE!!! " << endl;
		cin >> choice;
	}
	srand(time(0));
	//batting or bowling is based on random numbers.
	//if random value(1,2) matches user input(1,2), user will win the toss.
	int toss = (rand() % 2) + 1;

	if (toss == choice)
	{
		playerbatting = true;
	}
	else
	{
		playerbatting = false;
	}
}
//confirm user if he wants to bat or bowl..
void winchoice(bool& playerbat)
{
	int choice;
	cout << "You have won the toss... " << endl;
	cout << "Please select from the following..." << endl;
	cout << "1. BAT. " << endl;
	cout << "2. BOWL. " << endl;
	cin >> choice;

	while (choice < 1 || choice > 2)
	{
		cout << "[+]INVALID CHOICE!!! " << endl;
		cin >> choice;
	}

	if (choice == 2)
	{
		playerbat = false;
	}
	else
	{
		playerbat = true;
	}
}
//randomly select CPU bat or bowl.
void opponentchoice(bool& playerbat)
{
	srand(time(0));
	int choice = (rand() % 2) + 1;

	if (choice == 1)
	{
		cout << "BEST 11 has win the toss and decided to bat first... " << endl;
	}
	else
	{
		cout << "BEST 11 has win the toss and decided to bowl first... " << endl;
		playerbat = true;
	}
}
//display scores and wickets.
void ShowScoreWidget(const Team& team, const int& overs, const int& totalOvers, const Player& playing1, const Player& playing2, const Player& bowler, const int& extras)
{
	cout << team.getTeamName() << ": " << team.getTeamScore()+extras << "/" << team.getTeamWickets();
	cout << "\t" << (overs-1) / 6 << "." << ((overs-1)%6) << "/" << totalOvers << endl;
	cout << playing1.getPlayerName() << "*: " << playing1.getPlayerScore() << endl;
	cout << playing2.getPlayerName() << ": " << playing2.getPlayerScore() << endl;
	cout << "Bowler: " << bowler.getPlayerName() << ": "<< bowler.getPlayerBowlScore() << "/" << bowler.getPlayerWickets() << endl;
}
//display the ball type on console
void DisplayWhatHappen(const char& ball)
{
	cout << "\n\t\t************************************" << endl;
	if (ball == 'N')
	{
		cout << "\t\t\t~~~NO BALL~~~" << endl;
	}
	else if (ball == '0')
	{
		cout << "\t\t\t~~~0 RUN~~~" << endl;
	}
	else if (ball == '1')
	{
		cout << "\t\t\t~~~1 RUN~~~" << endl;
	}
	else if (ball == '2')
	{
		cout << "\t\t\t~~~2 RUNs~~~" << endl;
	}
	else if (ball == '3')
	{
		cout << "\t\t\t~~~3 RUNs~~~" << endl;
	}
	else if (ball == '4')
	{
		cout << "\t\t\t~~~4 RUNs~~~" << endl;
	}
	else if (ball == '5')
	{
		cout << "\t\t\t~~~5 RUNs~~~" << endl;
	}
	else if (ball == '6')
	{
		cout << "\t\t\t~~~6 RUNs~~~" << endl;
	}
	else if (ball == 'W')
	{
		cout << "\t\t\t~~~OUT~~~" << endl;
	}
	else if (ball == 'w')
	{
		cout << "\t\t\t~~~WIDE BALL~~~" << endl;
	}

	cout << "\t\t************************************" << endl;
}

void ThisOver(char** Over, int index)
{
	//take full char 2d pointer and index of that over.
	system("pause");
	system("cls");
	cout << "\n\n\t\tTHIS OVER" << endl;
	cout << "\t";
	//show the 6 balls on console.
	for (int i = 0; i < 6; i++)
	{
		cout << Over[index][i] << "\t";
	}
	cout << endl;
	system("pause");
	system("cls");
}
//display the record of all the overs.
void DisplayOvers(char** Overs, const int& overs, const int& ballsPlayed)
{
	cout << "OVERS: " << endl;
	for (int i = 0; i < overs; i++)
	{
		cout << "Over #" << i + 1 << endl;
		for (int j = 0; j < 6; j++)
		{
			if (Overs[i][j] == '0' || Overs[i][j] == '1' || Overs[i][j] == '2' || Overs[i][j] == '3' || Overs[i][j] == '4' || Overs[i][j] == '5' || Overs[i][j] == '6')
			{
				cout << Overs[i][j] << "\t";
			}
			else if (Overs[i][j] == 'W')
			{
				cout << Overs[i][j] << "\t";
			}
			else
			{
				break;
			}
		}
		cout << endl;
	}
}
//display winner function which will display the winner depend on scores.
void DISPLAYWINNER(const Team& playerTeam, const Team& opponentTeam)
{
	//display both teams record.
	cout << "\n\n\n\t\t\t*****************************************" << endl;
	cout << "\t\t\t\t" << playerTeam.getTeamName() << ": " << playerTeam.getTeamScore() << "/" << playerTeam.getTeamWickets() << endl;
	cout << "\t\t\t\t" << opponentTeam.getTeamName() << ": " << opponentTeam.getTeamScore() << "/" << opponentTeam.getTeamWickets() << endl;
	//check if user team score is equal to CPU team score.
	if ((playerTeam.getTeamScore()) == (opponentTeam.getTeamScore()))
	{
		cout << "\t\t\t\t~~~MATCH TIE~~~" << endl;
	}
	//check if user team score is greater
	else if ((playerTeam.getTeamScore()) > (opponentTeam.getTeamScore()))
	{
		cout << "\t\t\t\t~~~PLAYER WINS~~~" << endl;
	}
	//else CPU will be the winner.
	else
	{
		cout << "\t\t\t\t~~~CPU WINS~~~" << endl;
	}

	cout << "\t\t\t*****************************************" << endl;
}
//ask user for a new bowler.
void chooseBowler(const Team& playerTeam, int& bowler, int& prev_bowler)
{
	cout << "SELECT BWOLER...\n" << endl;
	//display all team players.
	for (int i = 0; i < 11; i++)
	{
		//indicate by * that this was the previous bowler.
		if (i == prev_bowler)
		{
			cout << i + 1 << ". " << playerTeam.playing[i]->getPlayerName() << "*" << endl;
		}
		else
		{
			cout << i + 1 << ". " << playerTeam.playing[i]->getPlayerName() << endl;
		}
	}

	do
	{
		cin >> bowler;
		while (bowler < 1 || bowler > 11)
		{
			cout << "Please choose Valid bowler!!!" << endl;
			cin >> bowler;
		}
		bowler--;
		//check if selected bowler was not the previous bowler.
		//a bowler cannot ball 2 consecutive overs.
		if (bowler == prev_bowler)
		{
			cout << "Bowler cannot ball this over!!!!.\nPick someone else." << endl;
		}
	} while (prev_bowler == bowler);

	prev_bowler = bowler;
}
//check if we can select that batsmen or not.
bool validBat(const int& batsmen, const int& runner, const int* batout)
{
	bool allocate = true;
	//run thorugh array and check if selected batsmen is in list of out or not.
	for (int i = 0; i < 11; i++)
	{
		//if already in a list, then we cannot select him
		if (batout[i] == batsmen)
		{
			allocate = false;
			break;
		}
	}
	//check if selected batsmen is a runner or not.
	if (batsmen == runner)
	{
		cout << "Already Batting...\nChoose other one..." << endl;
		allocate = false;
	}
	//return true or false.
	return allocate;
}
//select BAtsmen function to ask user to choose batsmen
void selectBatsmen(const Team& team, int& batsmen, int& runner , const int* batout)
{
	system("cls");
	
	cout << "Select Batsmen...\n" << endl;
	//display all players on console and ask user for player no.
	for (int i = 0; i < 11; i++)
	{
		cout << i + 1 << ". " << team.playing[i]->getPlayerName() << endl;
	}

	cin >> batsmen;
	//bound check - > Players(0-10)
	while (batsmen < 1 || batsmen > 11)
	{
		cout << "CHoose walid batsmen" << endl;
		cin >> batsmen;
	}
	//function to check if selected batsmen is already given out or is a runner...
	//we cannot select batsmen again once he is given out.
	while (validBat(batsmen-1, runner, batout) == false)
	{
		cin >> batsmen;
	}
	//decrease by 1 as array index start from 0:)
	batsmen--;
	system("cls");
	//check we set if we need to select runner or not.
	if (runner == 11)
	{
		cout << "Select Runner up...\n" << endl;
		//display all players.
		for (int i = 0; i < 11; i++)
		{
			cout << i + 1 << ". " << team.playing[i]->getPlayerName() << endl;
		}

		cin >> runner;
		//check if runner and batsmen are not same and in range of 1-11
		while ((runner == batsmen + 1) || (runner <1 || runner > 11))
		{
			cout << "PLease select a different batsmen...." << endl;
			cin >> runner;
		}
		//decrease by 1 as array index start from 0:)
		runner--;
	}	
}
//
//void MatchProcess(const char& ball, const string& bowltype, int& extras, Team& opponentTeam, Team& playerTeam, int& batsmen, int& runner, int& bowler, int*batOut, int&wickets, int& totalBallsPlayed )
//{
//	if (ball == 'N' || ball == 'w' || bowltype == "NO BALL")
//	{
//		extras++;
//		totalBallsPlayed--;
//		opponentTeam.playing[bowler]->UpdatePlayerBowlScore();
//	}
//	else if (ball == 'W')
//	{
//		batOut[wickets] = batsmen;
//
//		wickets++;
//		playerTeam.SetTeamWickets(wickets);
//		opponentTeam.playing[bowler]->UpdatePlayerWickets();
//		system("pause");
//		selectBatsmen(playerTeam, batsmen, runner, batOut);
//	}
//	else
//	{
//		opponentTeam.playing[bowler]->UpdatePlayerBowlScore(static_cast<int>(ball) - 48);
//	}
//	if (ball == '1' || ball == '3' || ball == '5')
//	{
//		int temp = batsmen;
//		batsmen = runner;
//		runner = temp;
//	}
//
//	playerTeam.AutoTeamScore();
//}
//display the best Player of Both teams.
void BESTPLAYERS(const Team& playerTeam, const Team& opponentTeam)
{
	int maxScore = -1;
	int Secondmax = 0;
	int indexcheck = -1;
	int indexWicketcheck = -1;
	int maxWickets = -1;
	int SecondMaxWickets = 0;
	//for all players
	for (int i = 0; i < 11; i++)
	{
		//get the maxscore scored by any of the player.
		if (maxScore < playerTeam.playing[i]->getPlayerScore())
		{
			//store the score of the player(max score in team).
			maxScore = playerTeam.playing[i]->getPlayerScore();
			//store the index of the player
			indexcheck = i;
		}
		//get the max wickets taken by any player
		if (maxWickets < playerTeam.playing[i]->getPlayerWickets())
		{
			//store the max wickets
			maxWickets = playerTeam.playing[i]->getPlayerWickets();
			//store the index of that player.
			indexWicketcheck = i;
		}
	}
	//now store second max score and wickets. 
	//remember max and second max scores or wickets can be same, but it should not be of same player.
	for (int i = 0; i < 11; i++)
	{
		if (Secondmax < playerTeam.playing[i]->getPlayerScore() && indexcheck != i)
		{
			Secondmax = playerTeam.playing[i]->getPlayerScore();
		}
		if (SecondMaxWickets < playerTeam.playing[i]->getPlayerWickets() && indexWicketcheck != i)
		{
			SecondMaxWickets = playerTeam.playing[i]->getPlayerWickets();
		}
	}
	//display user team best players.
	cout << "\n\n\t\t******************************************************************" << endl; 
	cout << "\t\t" << playerTeam.getTeamName() << "\t" << playerTeam.getTeamScore() << "/" << playerTeam.getTeamWickets() << endl;
	for (int i = 0; i < 11; i++)
	{
		if (maxScore == playerTeam.playing[i]->getPlayerScore() || Secondmax == playerTeam.playing[i]->getPlayerScore())
		{
			cout << "\t\t" << playerTeam.playing[i]->getPlayerName() << ": " << playerTeam.playing[i]->getPlayerScore() << endl;
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if (maxWickets == playerTeam.playing[i]->getPlayerWickets() && maxWickets > 0)
		{
			cout << "\t\t" << playerTeam.playing[i]->getPlayerName() << ": " << playerTeam.playing[i]->getPlayerBowlScore() << "/" << playerTeam.playing[i]->getPlayerWickets() << endl;
		}
		if (SecondMaxWickets == playerTeam.playing[i]->getPlayerWickets() && SecondMaxWickets > 0)
		{
			cout << "\t\t" << playerTeam.playing[i]->getPlayerName() << ": " << playerTeam.playing[i]->getPlayerBowlScore() << "/" << playerTeam.playing[i]->getPlayerWickets() << endl;
		}
	}

	maxScore = -1;
	Secondmax = -1;
	indexcheck = -1;
	maxWickets = 0;
	SecondMaxWickets = -1;
	//similarly for CPU team.
	for (int i = 0; i < 11; i++)
	{
		if (maxScore < opponentTeam.playing[i]->getPlayerScore())
		{
			maxScore = opponentTeam.playing[i]->getPlayerScore();
			indexcheck = i;
		}
		if (maxWickets < opponentTeam.playing[i]->getPlayerWickets())
		{
			maxWickets = opponentTeam.playing[i]->getPlayerWickets();
			indexWicketcheck = i;
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (Secondmax < opponentTeam.playing[i]->getPlayerScore() && indexcheck != i)
		{
			Secondmax = opponentTeam.playing[i]->getPlayerScore();
		}
		if (SecondMaxWickets < opponentTeam.playing[i]->getPlayerWickets() && indexWicketcheck != i)
		{
			SecondMaxWickets = opponentTeam.playing[i]->getPlayerWickets();
		}
	}

	cout << "\t\t******************************************************************" << endl;
	cout << "\t\t" << opponentTeam.getTeamName() << "\t" << opponentTeam.getTeamScore() << "/" << opponentTeam.getTeamWickets() << endl;
	for (int i = 0; i < 11; i++)
	{
		if (maxScore == opponentTeam.playing[i]->getPlayerScore() || Secondmax == opponentTeam.playing[i]->getPlayerScore())
		{
			cout << "\t\t" << opponentTeam.playing[i]->getPlayerName() << ": " << opponentTeam.playing[i]->getPlayerScore() << endl;
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (maxWickets == opponentTeam.playing[i]->getPlayerWickets() && maxWickets > 0)
		{
			cout << "\t\t" << opponentTeam.playing[i]->getPlayerName() << ": " << opponentTeam.playing[i]->getPlayerBowlScore() << "/" << opponentTeam.playing[i]->getPlayerWickets() << endl;
		}
		if (SecondMaxWickets == opponentTeam.playing[i]->getPlayerWickets() && SecondMaxWickets > 0)
		{
			cout << "\t\t" << opponentTeam.playing[i]->getPlayerName() << ": " << opponentTeam.playing[i]->getPlayerBowlScore() << "/" << opponentTeam.playing[i]->getPlayerWickets() << endl;
		}
	}

	cout << "\t\t******************************************************************" << endl;
}