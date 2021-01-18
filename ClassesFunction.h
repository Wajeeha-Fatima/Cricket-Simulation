#pragma once
#include<iostream>

using namespace std;
//display bowltype on console and chnage bowltype in simple words.
void DisplayBowlType(const int& length, const float& width, string& bowlType)
{
	cout << "\n\n\t\t************************************" << endl;

	//check for wide ball
	if (width > 3.0 || width < 0)
	{
		cout << "\t\t\t~~~WIDE~~~" << endl;
		bowlType = "WIDE";
	}
	//OFF SIDE ball check if width >= 1.5
	else if (width >= 1.5 && width <= 3.0)
	{
		if (length >= 0 && length <= 20)
		{
			cout << "\t\t\t~~~OFF SIDE BOUNCER~~~" << endl;
			bowlType = "OFF SIDE BOUNCER";
		}
		else if (length >= 21 && length <= 40)
		{
			cout << "\t\t\t~~~OFF SIDE GOODLENGTH~~~" << endl;
			bowlType = "OFF SIDE GOODLENGTH";
		}
		else if (length >= 41 && length <= 50)
		{
			cout << "\t\t\t~~~WIDE YORKER~~~" << endl;
			bowlType = "WIDE YORKER";
		}
		else
		{
			cout << "\t\t\t~~~NO BALL~~~" << endl;
			bowlType = "NO BALL";
		}
	}
	else if (width >= 0 && width < 1.5)
	{
		if (length >= 0 && length <= 20)
		{
			cout << "\t\t\t~~~BOUNCER~~~" << endl;
			bowlType = "BOUNCER";
		}
		else if (length >= 21 && length <= 40)
		{
			cout << "\t\t\t~~~GOODLENGTH~~~" << endl;
			bowlType = "GOODLENGTH";
		}
		else if (length >= 41 && length <= 50)
		{
			cout << "\t\t\t~~~TOE CRUSHER~~~" << endl;
			bowlType = "TOE CRUSHER";
		}
		else
		{
			cout << "\t\t\t~~~NO BALL~~~" << endl;
			bowlType = "NO BALL";
		}
	}
	else
	{
		cout << "\t\t\t~~~WIDE BALL~~~~" << endl;
		bowlType = "WIDE BALL";
	}

	cout << "\t\t************************************" << endl;
}
//this function will take integer as input and return its char value.
char scoreIntToChar(const int& score)
{
	if (score == 0)
	{
		return '0';
	}
	else if (score == 1)
	{
		return '1';
	}
	else if (score == 2)
	{
		return '2';
	}
	else if (score == 3)
	{
		return '3';
	}
	else if (score == 4)
	{
		return '4';
	}
	else if (score == 5)
	{
		return '5';
	}
	else if (score == 6)
	{
		return '6';
	}
	else
	{
		return 'W';
	}
}