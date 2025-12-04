#include <iostream>
#include<cstdlib>
using namespace std;
enum enchoice{Stone=1,Paper=2, Scissors=3};
enum enwinner{Player=1,Computer=2,Draw=3};
struct stRoundInfo {
	short RoundNumber=0;
	enchoice PlayerChoice;
	enchoice ComputerChoice;
	enwinner Winner;
	string WinnerName;
};
struct stGameResult {
	short GameRounds = 0;
	short PlayerWinTimes=0;
	short ComputerWinTimes=0;
	short DrawTimes=0;
	enwinner GameWinner;
	string GameWinnerName;
};
short ReadHowManyRounds() {
	short RoundNumber = 0;
	do {
		cout << "How Many Round 1 To 10:\n ";
		cin >> RoundNumber;
	} while (RoundNumber < 0 || RoundNumber>10);
	return RoundNumber;
}
int GetRandomNumber(int from, int to) {

	int RandomNumber = rand() % (to - from + 1) + from;
	return RandomNumber;
}
enchoice ReadPlayerChoice() {
	short PlayerChoice = 1;
	do {
		cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
		cin >> PlayerChoice;
	} while (PlayerChoice < 0 || PlayerChoice>3);
	return (enchoice)PlayerChoice;
}
enchoice GetComputerChoice() {
	return (enchoice)GetRandomNumber(1, 3);
}
enwinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice) {
		return enwinner::Draw;
	}
	switch (RoundInfo.PlayerChoice) {
	case enchoice::Stone:
		if (RoundInfo.ComputerChoice == enchoice::Paper) {
			return enwinner::Computer;
		}
		break;
	case enchoice::Paper:
		if (RoundInfo.ComputerChoice == enchoice::Scissors) {
			return enwinner::Computer;
		}
		break;
	case enchoice::Scissors:
		if (RoundInfo.ComputerChoice == enchoice::Stone) {
			return enwinner::Computer;
		}
		break;
    
	}
	return enwinner::Player;
}
string WinnerName(enwinner Winner) {
	string arrWinnerName[3] = {"Player","Computer","No Winner"};
	return arrWinnerName[Winner - 1];
}
string Choice(enchoice Choice) {
	string arrWinnerName[3] = { "Stone","Paper","Scissors" };
	return arrWinnerName[Choice - 1];
}
void WinnerScreenColor(enwinner Winner) {
	switch (Winner) {
	  case enwinner::Player:
		system("color 2F");
		break;
	  case  enwinner::Computer:
		  system("color 4F");
		  cout << "\a";
		  break;
	  case enwinner::Draw:
		  system("color 6F");

	}

}
void PrintRoundResult(stRoundInfo RoundInfo) {
	cout << "_________________Round[" << RoundInfo.RoundNumber << "]____________________\n";
	cout << "Player 1 Choice:" << Choice(RoundInfo.PlayerChoice)<< endl;
	cout << "Computer Choice:" << Choice( RoundInfo.ComputerChoice) << endl;
	cout << "Round winner:" << RoundInfo.WinnerName << endl;
	cout << "_____________________________________________";
	WinnerScreenColor(RoundInfo.Winner);

}
enwinner WhoWonTheGame(short PlayerWintimes, short ComputerWintimes) {
	if (PlayerWintimes > ComputerWintimes)
		return enwinner::Player;
	else if (ComputerWintimes > PlayerWintimes)
		return enwinner::Computer;
	else
		return enwinner::Draw;
}
stGameResult FillGameResult(short GameRounds, short PlayerWintimes,short ComputerWintimes,short Drawtimes) {
	stGameResult GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.PlayerWinTimes = PlayerWintimes;
	GameResult.ComputerWinTimes = ComputerWintimes;
	GameResult.DrawTimes = Drawtimes;
	GameResult.GameWinner = WhoWonTheGame(GameResult.PlayerWinTimes, GameResult.ComputerWinTimes);
	GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;

}
stGameResult PlayGame(short ReadHowManyRounds) {
	stRoundInfo RoundInfo;
	short PlayerWintimes = 0, ComputerWintimes = 0, Drawtimes = 0;
	for (short GameRound = 1; GameRound <= ReadHowManyRounds; GameRound++) {
		cout << "\nRound[" << GameRound << "] begins:\n\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enwinner::Computer)
			ComputerWintimes++;
		else if (RoundInfo.Winner == enwinner::Player)
			PlayerWintimes++;
		else
			Drawtimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(ReadHowManyRounds, PlayerWintimes, ComputerWintimes, Drawtimes);
}
void ResatScreen() {
	system("cls");
	system("color 0F");
}
void ShowGameOverScreen() {
	cout << "\n\n\t\t_________________________________________________________________________\n\n";
	cout << "\t\t\t             +++ G a m e  O v e r +++\n\n";
	cout << "\t\t_________________________________________________________________________\n";
}
void PrintGameResult(stGameResult GameResult) {
	cout << "\n\n\t\t__________________________[Game Result]___________________________________\n\n";
	cout << "\t\tGame Rounds       :" << GameResult.GameRounds << endl;
	cout << "\t\tPlayer 1 Won times:" << GameResult.PlayerWinTimes << endl;
	cout << "\t\tComputer Won times:" << GameResult.ComputerWinTimes << endl;
	cout << "\t\tDraw times        :" << GameResult.DrawTimes << endl;
	cout << "\t\tFinal Winner      :" << GameResult.GameWinnerName << endl;
	cout << "\t\t_______________________________________________________________________________\n";
	WinnerScreenColor(GameResult.GameWinner);

}
void StartGame() {
	string opinion = "";
	do {
		ResatScreen();
	    stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		PrintGameResult(GameResult);

		cout << "Do you want to play again:Y/N\n";
		cin >> opinion;
	} while (opinion == "Y" ||  opinion == "y" );
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}