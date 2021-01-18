#include<iostream>
#include<string>
#include<fstream>
#include"Cricket_Functions.h"
#include"Team.h"

using namespace std;

void main()
{
	int menu_choice = 0;
	string* all_teams;
	int total_teams = 0;
	string team_name;
	int check;

	string fileName = "TEAMS/";
	ifstream in;

	Team playerTeam;
	Team opponentTeam;

	//goto-jump  to start the game from start
	jump:
		menu(menu_choice); //display menu on screen
		system("cls");	//clear the screen

	//if choice is 1, then choose a team from databse.
	if (menu_choice == 1)
	{
		//check total teams present in the database.
		CheckTotalTeams(all_teams, total_teams);
		//choose the team....
		chooseTeam(team_name, all_teams, total_teams);
	}
	//if user wants to create his own team.
	else if (menu_choice == 2)
	{
		//Create team FUNC().
		CreateTeam(team_name);
	}
	else
	{	
		//Exit mean finish the game.
		return;
	}
	//open the file of the team, selected or created by user.
	fileName = "TEAMS/" + team_name + ".txt";
	//oppen the file.
	in.open(fileName.c_str());
	//if fail to open, then again show the menu.
	if (in.fail())
	{
		cout << "[+]TEAM DOES NOT EXIST IN OUR DATABASE..." << endl;
		goto jump;
	}
	else
	{
		//check 
		//a team should have at least 11 players in it.
		//this func() will check if user selected team has 11 player or not.
		while (CheckTeam11Players(fileName) == false)
		{
			//if user selected team does not have 11 players, then ask user to add.
			cout << "Your Team Should have atleast 11 players....";
			cout << "Do you want to create a player?" << endl;
			cout << "\t\t1. Yes.\t\t2. No" << endl;
			cin >> check;

			while (check < 1 || check > 2)
			{
				cin >> check;
			}

			if (check == 1)
			{
				//if he wants to add,then add player.
				CreatePlayer(team_name);
			}
			else
			{
				in.close();
				goto jump;
			}
		}

		string name;
		int id;
		string type;
		string p_type;
		int batpower;
		int ballpower;
		string weakness;
		string strongness;
		//set player team name
		playerTeam.SetTeamName(team_name);
		//read 11 players from the file and set accordingly.
		for (int i = 0; i < 11; i++)
		{
			in >> name;
			in >> id;
			in >> type;
			in >> p_type;
			in >> batpower;
			in >> ballpower;
			in >> weakness;
			in >> strongness;
			//set player at index i(0-10)
			playerTeam.SetPlayer(name, id, type, p_type, batpower, ballpower, weakness, strongness, i);
		}
		//close the file...
		in.close();

		system("cls");
		//display the Team on console.
		playerTeam.displayTeam();
		cout << endl;
		system("pause");
		system("cls");
		//open "BEST_11.txt" which is CPU team.
		in.open("TEAMS/BEST_11.txt");
		if (in.fail())
		{
			cout << "GAME FULL OF ERRORS!!!" << endl;
			cout << "[+]UPDATE AVAILABLE!!!" << endl;
			exit(0);
		}
		else
		{
			//set CPU team name.
			opponentTeam.SetTeamName("BEST11");

			for (int i = 0; i < 11; i++)
			{
				in >> name;
				in >> id;
				in >> type;
				in >> p_type;
				in >> batpower;
				in >> ballpower;
				in >> weakness;
				in >> strongness;

				opponentTeam.SetPlayer(name, id, type, p_type, batpower, ballpower, weakness, strongness, i);
			}
			//closing the file.
			in.close();
			//display the team on console.
			opponentTeam.displayTeam();
			cout << endl;
			system("pause");
			system("cls");
		}

		int overs = 0;
		char** Player_OVERS;
		string bowltype;

		bool playerBat = false;

		//ask user for total overs(no restriction on overs i.e it can 1,2,3...)...
		selectOver(overs);
		//overs array to store ball to ball score.
		Player_OVERS = generateOvers(overs);
		system("cls");
		//TOSS
		TOSS(playerBat);
		system("cls");

		if (playerBat)
		{
			//choice after winning toss
			winchoice(playerBat);
		}
		else
		{
			//CPU choice...
			opponentchoice(playerBat);
		}
		system("pause");
		system("cls");

		int length = 0;
		float width = 0;
		bool strike;
		int batsmen = 0;
		int runner = 1;
		int wickets = 0;
		int batOut[11] = { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		int bowler = 10;
		int prev_bowler = 11;
		int pextras = 0;
		int oextras = 0;
		char ball;
		int totalBallsPlayed = 1;

		//if player batting
		if (playerBat)
		{
			runner = 11;	//runner = 11 will be undefined, so ask user for runner.
			//select BAtsmen function to ask user to choose batsmen
			selectBatsmen(playerTeam, batsmen, runner, batOut);
			system("cls");
			//loop for evey ball count.
			for (totalBallsPlayed = 1; totalBallsPlayed < ((overs * 6) + 1); totalBallsPlayed++)
			{
				cout << "\t\t\tPLAYER BATTING...\n" << endl;
				//display scores and wickets in left top like a widgtet
				ShowScoreWidget(playerTeam, totalBallsPlayed, overs, *playerTeam.playing[batsmen], *playerTeam.playing[runner], *opponentTeam.playing[bowler], pextras);
				//call BOWL function of CPU() 
				opponentTeam.playing[bowler]->BOWL(length, width, bowltype, playerBat);
				//call the BAT function of player and store the char in ball.
				ball = playerTeam.playing[batsmen]->BAT(length, width, bowltype, playerBat);
				//display on console.
				DisplayWhatHappen(ball);
				//store the ball in the array.
				//for 1st ball -> Player_OVERS[0][0] = ball after calculation.
				//for 2nd ball -> Player_OVERS[0][1] = ball after calculation.
				//for 7nd ball -> Player_OVERS[1][0] = ball after calculation.
				Player_OVERS[(totalBallsPlayed - 1) / 6][(totalBallsPlayed - 1) % 6] = ball;
				//if balltype is no ball, then add 1 score to extras, and then bowler has to bowl that bowl again.
				if (ball == 'N' || ball == 'w' || bowltype == "NO BALL")
				{
					pextras++;
					totalBallsPlayed--;
					opponentTeam.playing[bowler]->UpdatePlayerBowlScore(); //update bowlerscore by 1, as he give an extra.
				}
				else if (ball == 'W')
				{//if Out was given.
					//store the batsmen number in wickets index.
					//batOut[0] = batsmenNo. (0-10)
					batOut[wickets] = batsmen;
					//then increase the index.
					wickets++;
					//set the updated wickets
					playerTeam.SetTeamWickets(wickets);
					//update the bowler wickets..
					opponentTeam.playing[bowler]->UpdatePlayerWickets();
					system("pause");
					//again ask for new batsmen.
					selectBatsmen(playerTeam, batsmen, runner, batOut);
				}
				else
				{
					//else update the score return by the BAT function.
					//char value will in range (48-54)
					opponentTeam.playing[bowler]->UpdatePlayerBowlScore(static_cast<int>(ball) - 48);
				}
				//if it was an odd score, then batsmen will become runner and runner become the batsmen.
				if (ball == '1' || ball == '3' || ball == '5')
				{
					/// <summary>
					/// batsmen = 1, runner = 2
					/// </summary>
					int temp = batsmen;
					batsmen = runner;
					runner = temp;
					// btsmen = 2, runner = 1.
				}
				//auto calculate team score.
				playerTeam.AutoTeamScore();

				//MatchProcess(ball, bowltype, pextras, opponentTeam, playerTeam, batsmen, runner, bowler, batOut, wickets, totalBallsPlayed);
				//if 6 balls are bowl, then change the bowler.
				if (totalBallsPlayed % 6 == 0)
				{
					//display what happen in that over.
					ThisOver(Player_OVERS, (totalBallsPlayed - 1) / 6);
					
					bowler--;
					//check because no 5 can be a batsmen ,and it is not recommended to ball from batsmen.
					if (bowler < 6)
					{
						bowler = 10;
					}
				}

				//check if 10 wickets are taken
				if (playerTeam.getTeamWickets() >= 10)
				{
					break;
				}
				
				cout << endl;
				system("pause");
				system("cls");
			}
			//set the score as total Team Score + extras given.
			playerTeam.SetTeamScore(playerTeam.getTeamScore() + pextras);
			//display the whole stats on console.
			playerTeam.displayTeamBatStats();
			system("pause");
			system("cls");
		}
		else
		{
			//loop for every ball.
			for (totalBallsPlayed = 1; totalBallsPlayed < ((overs * 6) + 1); totalBallsPlayed++)
			{
				//after every over ask for a new bowler.
				//over means, when 6 balls are thrown.
				//totalBallsPlayed-1   ->    as we start the loop from 1, we have to check it by -1.
				if ((totalBallsPlayed-1) % 6 == 0)
				{
					//choose bowler...
					chooseBowler(playerTeam, bowler, prev_bowler);
					system("cls");
				}
				cout << "\t\t\tOPPONENT BATTING...\n" << endl;
				//show scoreboard.
				ShowScoreWidget(opponentTeam, totalBallsPlayed, overs, *opponentTeam.playing[batsmen], *opponentTeam.playing[runner], *playerTeam.playing[bowler], oextras);
				//BOWL func().
				playerTeam.playing[bowler]->BOWL(length, width, bowltype, playerBat);
				//BAT fun()
				ball = opponentTeam.playing[batsmen]->BAT(length, width, bowltype, playerBat);

				if (ball == 'N' || ball == 'w' || bowltype == "NO BALL")
				{
					oextras++;
					totalBallsPlayed--;
					playerTeam.playing[bowler]->UpdatePlayerBowlScore();
				}
				else if (ball == 'W')
				{
					if (runner > batsmen)
					{
						batsmen = runner + 1;
					}
					else
					{
						batsmen++;
					}
					wickets++;
					opponentTeam.SetTeamWickets(wickets);
					playerTeam.playing[bowler]->UpdatePlayerWickets();
					if (opponentTeam.getTeamWickets() >= 10)
						break;
				}
				else
				{
					playerTeam.playing[bowler]->UpdatePlayerBowlScore(static_cast<int>(ball) - 48);
				}

				if (ball == '1' || ball == '3' || ball == '5')
				{
					int temp = batsmen;
					batsmen = runner;
					runner = temp;
				}

				opponentTeam.AutoTeamScore();

				DisplayWhatHappen(ball);
				Player_OVERS[(totalBallsPlayed - 1) / 6][(totalBallsPlayed - 1) % 6] = ball;
				cout << endl;
				system("pause");
				system("cls");
			}
			opponentTeam.SetTeamScore(opponentTeam.getTeamScore() + oextras);

			opponentTeam.displayTeamBatStats();
			system("pause");
			system("cls");
		}
		//display all the overs record.
		DisplayOvers(Player_OVERS, overs, totalBallsPlayed-1);

		system("pause");
		system("cls");

		//display the chasing score for chasing team.
		//if user was batting, then display team name and total score off the user team
		cout << "\n\n\n\t\t\t****************************************************************" << endl;
		if (playerBat)
		{
			cout << "\t\t\t\t" << opponentTeam.getTeamName() << " need " << playerTeam.getTeamScore() + 1 << " runs to win in " << overs << " overs." << endl;
		}
		else
		{
			cout << "\t\t\t\t" << playerTeam.getTeamName() << " need " << opponentTeam.getTeamScore() + 1 << " runs to win in " << overs << " overs." << endl;
		}
		cout << "\t\t\t****************************************************************\n\n" << endl;

		system("pause");
		system("cls");

		batsmen = 0;
		runner = 1;
		wickets = 0;
		bowler = 10;
		//if it was user batting, then in this section, it would be CPU batting as chase.
		if (playerBat)
		{
			for (totalBallsPlayed = 1; totalBallsPlayed < ((overs * 6) + 1); totalBallsPlayed++)
			{
				//ask for bowler.
				if ((totalBallsPlayed-1) % 6 == 0)
				{
					chooseBowler(playerTeam, bowler, prev_bowler);
					system("cls");
				}
				cout << "\t\t\tOPPONENT BATTING...\n" << endl;
				//display scoreboard.
				ShowScoreWidget(opponentTeam, totalBallsPlayed, overs, *opponentTeam.playing[batsmen], *opponentTeam.playing[runner], *playerTeam.playing[bowler], oextras);
				//display the reamining score and balls for the chasing team.
				cout << "Need " << -1*(opponentTeam.getTeamScore() + oextras - playerTeam.getTeamScore() - 1) << " runs in ";
				cout << (overs * 6) - totalBallsPlayed + 1 << " balls" << endl;
				//BOWL fun().
				playerTeam.playing[bowler]->BOWL(length, width, bowltype, !playerBat);
				//BAT fun().
				ball = opponentTeam.playing[batsmen]->BAT(length, width, bowltype, !playerBat);

				if (ball == 'N' || ball == 'w' || bowltype == "NO BALL")
				{
					oextras++;					
					totalBallsPlayed--;
					playerTeam.playing[bowler]->UpdatePlayerBowlScore();
				}
				else if (ball == 'W')
				{
					if (runner > batsmen)
					{
						batsmen = runner + 1;
					}
					else
					{
						batsmen++;
					}
					wickets++;
					opponentTeam.SetTeamWickets(wickets);
					playerTeam.playing[bowler]->UpdatePlayerWickets();
					if (opponentTeam.getTeamWickets() >= 10)
					{
						break;
					}
				}
				else
				{
					playerTeam.playing[bowler]->UpdatePlayerBowlScore(static_cast<int>(ball) - 48);
				}

				if (ball == '1' || ball == '3' || ball == '5')
				{
					int temp = batsmen;
					batsmen = runner;
					runner = temp;
				}

				opponentTeam.AutoTeamScore();

				DisplayWhatHappen(ball);
				Player_OVERS[(totalBallsPlayed - 1) / 6][(totalBallsPlayed - 1) % 6] = ball;
				cout << endl;
				system("pause");
				system("cls");
				//check if CPU team score is greater than chase score.
				//if greater, then break the loop.
				if (opponentTeam.getTeamScore() + oextras > playerTeam.getTeamScore())
				{
					break;
				}
			}

			opponentTeam.SetTeamScore(opponentTeam.getTeamScore() + oextras);
		}
		else
		{
			runner = 11;
			selectBatsmen(playerTeam, batsmen, runner, batOut);
			system("cls");

			for (totalBallsPlayed = 1; totalBallsPlayed < ((overs * 6) + 1); totalBallsPlayed++)
			{
				cout << "\t\t\tPLAYER BATTING...\n" << endl;

				ShowScoreWidget(playerTeam, totalBallsPlayed, overs, *playerTeam.playing[batsmen], *playerTeam.playing[runner], *opponentTeam.playing[bowler], pextras);

				cout << "Need " << -1*(playerTeam.getTeamScore() + pextras - opponentTeam.getTeamScore() - 1) << " runs in " << (overs * 6) - totalBallsPlayed +1<< " balls" << endl;

				opponentTeam.playing[bowler]->BOWL(length, width, bowltype, !playerBat);

				ball = playerTeam.playing[batsmen]->BAT(length, width, bowltype, !playerBat);

				DisplayWhatHappen(ball);
				Player_OVERS[(totalBallsPlayed - 1) / 6][(totalBallsPlayed - 1) % 6] = ball;
				cout << endl;

				if (ball == 'N' || ball == 'w')
				{
					pextras++;
					totalBallsPlayed--;
					opponentTeam.playing[bowler]->UpdatePlayerBowlScore();
				}
				else if (ball == 'W')
				{
					batOut[wickets] = batsmen;
					wickets++;
					playerTeam.SetTeamWickets(wickets);
					opponentTeam.playing[bowler]->UpdatePlayerWickets();
					system("pause");
					selectBatsmen(playerTeam, batsmen, runner, batOut);
					if (playerTeam.getTeamWickets() >= 10)
						break;
				}
				else
				{
					opponentTeam.playing[bowler]->UpdatePlayerBowlScore(static_cast<int>(ball) - 48);
				}

				if (ball == '1' || ball == '3' || ball == '5')
				{
					int temp = batsmen;
					batsmen = runner;
					runner = temp;
				}

				playerTeam.AutoTeamScore();

				if (totalBallsPlayed % 6 == 0)
				{
					bowler--;
					if (bowler < 6)
					{
						bowler = 10;
					}
				}
				
				system("pause");
				system("cls");
				if (playerTeam.getTeamScore() + pextras > opponentTeam.getTeamScore())
				{
					break;
				}

			}

			playerTeam.SetTeamScore(playerTeam.getTeamScore() + pextras);
		}

	}
	//display winner function which will decide the winner team by scores.
	DISPLAYWINNER(playerTeam, opponentTeam);

	system("pause");
	system("cls");
	//display the best players of the Team.
	BESTPLAYERS(playerTeam, opponentTeam);

	system("pause");

	return;
}