//AMONG US: CPP EDITION
//Orbase, Fernand Angelo A.

//LIBRARIES 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cwchar>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>

using namespace std;

//HANDLE AND COORD FOR CONSOLE WINDOW
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
COORD  CursorPosition;

//ULTIMATE WEAPON
void Fernandizer()
{
	cin.clear();
	cin.ignore(500, '\n');
	cin.get();
}

//POSITION
void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

//GAME SCREEN SHAPE AND SIZE
void GameScreen()
{
	system("color F0");
	RECT Window;
	MoveWindow(GetConsoleWindow(), GetSystemMetrics(SM_CXSCREEN) / 2 - 850 / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - 640 / 2, 850, 640, TRUE);
	system("mode con: cols=100 lines=40");
}

//CLASS DEFINITION FOR THE MOBILE PHONE
class MobilePhone
{
	private: //private access - methods and variables under this section are only accessible in this class
		//INTEGERS//
		int GameMenuChoice;
		int TaskChoice;
		//INITIALIZED INTEGERS//
		int TaskDone = 0;
		int TaskProgress = 0;
		int TaskPoints = 0;
		int CrewTrust = 10;
		int PowerUp = 0;
		int GameOfficiallyOver = 0;
		//ARRAYS
		int TaskPointsArray[10];
		string CrewLeadersArray[10];
		//STRINGS//
		string UserAnswer;
		string CrewLeaderName;
		//CHARACTERS//
		char UserChoice;
		char HomeScreenChoice;
		bool isWrong;
		
	public: //public access - methods under this section are accessible outside this class
		//PHONE GRAPHICS//
		void Border(int, int);
		//GAME//
		void Game();
		void GameLevels();
		void GameConvo();
		void InitLeaderBoard();
		void LeaderBoard();
		void LeaderBoardReader();
		void LeaderBoardWriter();
		void Reset();
		//GAME GRAPHICS//
		void GameTitleScreen();
		void GameTitle();
		void GameSpaceBackground();	
		void GameCharacter();
		void LoadingScreen();
		void ProgressBar(int);
		void GameOver();
		void MerryXmas();
	
		MobilePhone() //CONSTRUCTOR
		{
			int LineCounter = 0;
			string LeaderBoardHeader;

			//READER
			ifstream Reader;
			Reader.open("LEADERBOARD.txt");
			
			getline(Reader, LeaderBoardHeader);
			getline(Reader, LeaderBoardHeader);
			getline(Reader, LeaderBoardHeader);

			while(Reader >> CrewLeaderName >> TaskPoints)
			{
				LineCounter++;	
			}

			Reader.close();

			//WRITER
			if (LineCounter == 0)
			{
				ofstream Writer;
				Writer.open("LEADERBOARD.txt");
				Writer << "LEADERBOARD" << endl << endl;
				Writer << "Crew Leader" << setw(25) << "Task Points";
				Writer.close();
			}
		}

		~MobilePhone()//DESTRUCTOR
		{

		}  
};

//OBJECTS
MobilePhone PhoneX, PhoneY;

//MAIN FUNCTION
int main()
{
	SetConsoleTitle(TEXT("AMONG US: CPP EDITION"));
	PhoneX.Game();

}

//NORMAL VOID FUNCTION DEFINITIONS//

void BubbleSort(int TaskPointsArray[], string CrewLeadersArray[]) //LEADERBOARD DATA SORTER
{  
	int i, j, temp;
	string temp2;

    for (i = 0; i < 10; i++)   
	{
		for (j = 0; j < 10 - 1; j++)
		{  
			if (TaskPointsArray[j + 1] > TaskPointsArray[j])  
			{
				temp = TaskPointsArray[j]; 
				temp2 = CrewLeadersArray[j];  
				TaskPointsArray[j] = TaskPointsArray[j + 1]; 
				CrewLeadersArray[j] = CrewLeadersArray[j + 1]; 
				TaskPointsArray[j+1] = temp;
				CrewLeadersArray[j+1]= temp2;
			}
		}   
	}   
}  

//METHOD DEFINITIONS (::)//

void MobilePhone::Border(int BorderStyle,int BorderSize) //IMPROVISED BORDER
{
	if(BorderStyle == 1)
	{
		for(int BorderMaker=0; BorderMaker < BorderSize; BorderMaker++)
		{
			Sleep(5); cout << char(176);
		}
	}
	
	if(BorderStyle == 2)
	{
		for(int BorderMaker=0; BorderMaker < BorderSize; BorderMaker++)
		{
			Sleep(5); cout << char(178);
		}
	}

	if(BorderStyle == 3)
	{
		for(int BorderMaker=0; BorderMaker < BorderSize; BorderMaker++)
		{
			Sleep(15); cout << char(178);
		}
	}

	if(BorderStyle == 4)
	{
		for(int BorderMaker=0; BorderMaker < BorderSize; BorderMaker++)
		{
			Sleep(25); cout << char(178);
		}
	}

	if(BorderStyle == 5)
	{
		for(int BorderMaker=0; BorderMaker < BorderSize; BorderMaker++)
		{
			cout << char(219);
		}
	}
}

//GAME//

void MobilePhone::Game() //AMONG US: C++ EDITION
{
	InitLeaderBoard();
	LeaderBoardReader();
	GameTitleScreen();
	GameSpaceBackground();
	GameTitle();

	gotoXY(65,26); cout << "[1] Start" << endl;
	gotoXY(65,27); cout << "[2] Leader Board" << endl;
	gotoXY(65,28); cout << "[3] Merry Xmas" << endl;
	gotoXY(65,29); cout << "[4] Exit" << endl << endl;
	gotoXY(68,38); cout << "INPUT: ";
	while (!(cin >> GameMenuChoice) || GameMenuChoice < 1 || GameMenuChoice > 4)
	{
		gotoXY(60,38); cerr << "INVALID INPUT! TRY AGAIN! [Press 1 - 3 only]";
		Fernandizer();
		gotoXY(60,38); cerr << "                                             ";
		gotoXY(68,38); cout << "INPUT: ";
	}

	switch(GameMenuChoice)
	{
		case 1:
		
			Reset();

			system("CLS");

			GameSpaceBackground();

			gotoXY(55,14); Border(2,20);
			gotoXY(65,15); cout << "CREW LEADER NAME";
			gotoXY(63,16); Border(2,20);
	
			do
			{
				int AlphaCount = 0;

				gotoXY(70,17); cin >> CrewLeaderName;

				isWrong = false;
				
				for (int i=0; i <= CrewLeaderName.length(); i++)
				{
					if (isalpha(CrewLeaderName[i]))
					{
						AlphaCount++;
					}
				}
				
				if (AlphaCount < 4 || CrewLeaderName.length() < 4 ||  CrewLeaderName.length() > 4) 
				{
					isWrong = true;

					gotoXY(45,17); cerr << "INVALID NAME! PLEASE ENTER AN ALPHABETICAL 4-CHARACTER NAME!";
					Fernandizer();
					gotoXY(45,17); cerr << "                                                            ";	
				}
			

			} while(isWrong == true);


			for(unsigned int k = 0; k < CrewLeaderName.length(); k++)
			{
				CrewLeaderName[k] = toupper(CrewLeaderName[k]);
			}
	
			system("CLS");

			GameSpaceBackground();

			gotoXY(65,13); cout << "THE AMONG US STORY";

			gotoXY(35,15); cout << "There are tasks that needs completion. But there is an IMPOSTOR";
			gotoXY(35,16); cout << "who sabotages the crew. Therefore, he must be ejected once and for all!";

			gotoXY(35,18); cout << "One way to do this is to have an emergency meeting with the crew.";
			gotoXY(35,19); cout << "The crew leader must engage and communicate to find the impostor's color.";

			gotoXY(35,21); cout << "If the crew leader mentions a wrong color, the crew members' trust will decrease";
			gotoXY(35,22); cout << "The Crew Trust and the Task Progress are key ingredients in accomplishing the game.";

			gotoXY(35,24); cout << "GOOD LUCK! GOD BLESS!";

			Fernandizer();
			system("CLS");

			GameLevels();
			break;

		case 2:
			LeaderBoard();
			break;

		case 3:
			MerryXmas();
			break;
			
		case 4:
			GameOfficiallyOver = 4;
			exit(1);
			break;
	}	
}

void MobilePhone::GameLevels() //MULTI-LEVEL SYSTEM
{
	GameScreen();

	while(GameOfficiallyOver == 0 && CrewTrust > 0)
	{
		LoadingScreen();

		if(TaskDone < 5 && PowerUp == 0) //LEVEL ONE
		{
			gotoXY(38,15); cout << "STAGE ONE: THE SKELD";
			cin.clear();
			cin.get();
			system("CLS");

			for(int i = 0; i < 3; i++)
			{
				gotoXY(2,2);Border(2,25);
				gotoXY(2,3);cout << "TASKS";
				gotoXY(2,4);Border(2,25);
				gotoXY(2,5);cout << "[1] Align Engine Output";
				gotoXY(2,6);cout << "[2] Calibrate Distributor";
				gotoXY(2,7);cout << "[3] Chart Course";
				gotoXY(2,8);cout << "[4] Clear Asteroids";
				gotoXY(2,9);cout << "[5] Swipe Card";
				gotoXY(2,10);Border(2,25);
				gotoXY(2,11);cout << "What to do?: "; 
				while(!(cin>>TaskChoice) || TaskChoice < 1 || TaskChoice > 5)
				{
					gotoXY(2,11);cerr << "INVALID INPUT! [Press 1-5 ONLY]";
					Fernandizer();
					gotoXY(2,11);cerr << "                               ";
					gotoXY(2,11);cout << "What to do?: "; 
				}

				system("CLS");

				switch(TaskChoice)
				{
					case 1:
					gotoXY(38,15); cout << "Aligning Engine Output...";
					gotoXY(0,16); Border(2,100);
					break;

					case 2:
					gotoXY(38,15); cout << "Calibrating Distributor...";
					gotoXY(0,16); Border(2,100);
					break;

					case 3:
					gotoXY(38,15); cout << "Commencing Chart Course...";
					gotoXY(0,16); Border(2,100);
					break;

					case 4:
					gotoXY(38,15); cout << "Clearing Asteroids...";
					gotoXY(0,16); Border(2,100);
					break;

					case 5:
					gotoXY(38,15); cout << "Swiping Card...";
					gotoXY(0,16); Border(2,100);
					break;
				}

				TaskDone++;
				ProgressBar(1);

				if(TaskDone == 5)
				{
					break;
				}
			}

			gotoXY(32,15); cout << "There's a MINOR SABOTAGE in the ship!";
			gotoXY(35,17); cout << "THERE IS AN IMPOSTOR AMONG US!";
			ProgressBar(2);
			GameConvo();
			GameOver();
		}

		else if((TaskDone >= 5 && TaskDone < 10 && PowerUp == 0) || PowerUp == 1) //LEVEL TWO
		{
			if(TaskDone == 5 && PowerUp == 0)
			{
				gotoXY(19,17);cout << "5 tasks done, but no impostor was found! Moving to next stage...";
				Fernandizer();
				system("CLS");
			}

			PowerUp = 1;

			gotoXY(38,15); cout << "STAGE TWO: MIRA HQ";
			gotoXY(35,16); cout << "POWER UP! [TASK ENHANCER + 10]";
			cin.clear();
			cin.get();
			system("CLS");

			for(int i = 0; i < 3; i++)
			{
				gotoXY(2,2);Border(2,25);
				gotoXY(2,3);cout << "TASKS";
				gotoXY(2,4);Border(2,25);
				gotoXY(2,5);cout << "[1] Assemble Artifact";
				gotoXY(2,6);cout << "[2] Measure Weather";
				gotoXY(2,7);cout << "[3] Prime Shield";
				gotoXY(2,8);cout << "[4] Fuel Engines";
				gotoXY(2,9);cout << "[5] Water Plants";
				gotoXY(2,10);Border(2,25);
				gotoXY(2,11);cout << "What to do?: "; 
				while(!(cin>>TaskChoice) || TaskChoice < 1 || TaskChoice > 5)
				{
					gotoXY(2,11);cerr << "INVALID INPUT! [Press 1-5 ONLY]";
					Fernandizer();
					gotoXY(2,11);cerr << "                               ";
					gotoXY(2,11);cout << "What to do?: "; 
				};

				system("CLS");

				switch(TaskChoice)
				{
					case 1:
					gotoXY(38,15); cout << "Assembling Artifact...";
					gotoXY(0,16); Border(3,100);
					break;

					case 2:
					gotoXY(38,15); cout << "Measuring Weather...";
					gotoXY(0,16); Border(3,100);
					break;

					case 3:
					gotoXY(38,15); cout << "Priming Shields...";
					gotoXY(0,16); Border(3,100);
					break;

					case 4:
					gotoXY(38,15); cout << "Fueling Engines...";
					gotoXY(0,16); Border(3,100);
					break;

					case 5:
					gotoXY(38,15); cout << "Watering Plants...";
					gotoXY(0,16); Border(3,100);
					break;
				}

				TaskDone++;
				ProgressBar(1);
		
				if(TaskDone == 10)
				{
					break;
				}
			}

			gotoXY(32,15); cout << "There's a MAJOR SABOTAGE in the ship!";
			gotoXY(35,17); cout << "THERE IS AN IMPOSTOR AMONG US!";
			ProgressBar(2);
			GameConvo();
			GameOver();
		}

		else if(TaskDone >= 10 || PowerUp > 1) //LEVEL THREE
		{
			if(TaskDone == 10 && PowerUp == 1)
			{
				gotoXY(19,17);cout << "10 tasks done, but no impostor was found! Moving to next stage...";
				Fernandizer();
				system("CLS");
			}

			PowerUp == 2;

			gotoXY(38,15); cout << "STAGE THREE: POLUS";
			gotoXY(35,16); cout << "POWER UP! [TASK ENHANCER + 15]";
			cin.clear();
			cin.get();
			system("CLS");

			for(int i = 0; i < 2; i++)
			{
				gotoXY(2,2);Border(2,25);
				gotoXY(2,3);cout << "TASKS";
				gotoXY(2,4);Border(2,25);
				gotoXY(2,5);cout << "[1] Align Telescope";
				gotoXY(2,6);cout << "[2] Fill Canisters";
				gotoXY(2,7);cout << "[3] Fix Weather Node";
				gotoXY(2,8);cout << "[4] Upload Data";
				gotoXY(2,9);cout << "[5] Reboot WiFi";
				gotoXY(2,10);Border(2,25);
				gotoXY(2,11);cout << "What to do?: "; 
				while(!(cin>>TaskChoice) || TaskChoice < 1 || TaskChoice > 5)
				{
					gotoXY(2,11);cerr << "INVALID INPUT! [Press 1-5 ONLY]";
					Fernandizer();
					gotoXY(2,11);cerr << "                               ";
					gotoXY(2,11);cout << "What to do?: "; 
				}

				system("CLS");

				switch(TaskChoice)
				{
					case 1:
					gotoXY(38,15); cout << "Aligning Telescope...";
					gotoXY(0,16); Border(4,100);
					break;

					case 2:
					gotoXY(38,15); cout << "Filling Canisters...";
					gotoXY(0,16); Border(4,100);
					break;

					case 3:
					gotoXY(38,15); cout << "Fixing Weather Node...";
					gotoXY(0,16); Border(4,100);
					break;

					case 4:
					gotoXY(38,15); cout << "Uploading Data...";
					gotoXY(0,16); Border(4,100);
					break;

					case 5:
					gotoXY(38,15); cout << "Rebooting WiFi...";
					gotoXY(0,16); Border(4,100);
					break;
				}

				TaskDone++;
				ProgressBar(1);

				if(TaskDone > 10)
				{
					break;
				}
			}

			gotoXY(32,15); cout << "There's a MAJOR SABOTAGE in the ship!";
			gotoXY(35,17); cout << "THERE IS AN IMPOSTOR AMONG US!";
			ProgressBar(2);
			GameConvo();
		}	
	}
}

void MobilePhone::GameConvo() //FAKE BOTS CHAT
{
	GameScreen();

	int size = 10;
	string Impostor;
	string* Innocent = new string[size];
	string* Convo = new string[size];

	srand(time(NULL));

	string ConvoArray[] = {"Who?", "I saw GREEN using the vent", "Where?", "I think it's you!", "Hey I saw YELLOW at the cafeteria!", "I'M NOT AN IMPOSTOR!!!", "It's not me", "Any proof?", "I think it's WHITE", "I saw BLACK with PINK!"};
	string ColorArray[] = {"PINK", "BLUE", "BLACK", "WHITE", "PURPLE", "RED", "YELLOW", "ORANGE", "GREEN", "BROWN"};

	gotoXY(1,1); cout << "TASKS DONE [" << TaskDone << "]";
	gotoXY(38,1); cout << "AMONG US: C++ EDITION";
	gotoXY(85,1); cout << "CREW TRUST [" << CrewTrust << "]";
	gotoXY(0,3); Border(5,100);
	
	GameCharacter();

	gotoXY(45,5); cout << "DO NOT SKIP or you'll be EJECTED!";	

	Impostor = ColorArray[rand() % 10];

	for(int c = 0; c < 10; c++)
	{		
		Convo[c] = ConvoArray[rand() % 10];
		Innocent[c] = ColorArray[rand() % 10];
		
		gotoXY(45,8+c+c); cout << Innocent[c] << "	: " << Convo[c];
		Sleep(500);
	}	

	gotoXY(0,34); Border(5,100);

	gotoXY(38,36); cout << "Who is the impostor?";
	gotoXY(1,38);

	for(int d = 0; d < 10; d++)
	{
		cout << ColorArray[d] << setw(10);
	}

	gotoXY(39,29); cout << CrewLeaderName << "	: ";
	getline(cin, UserAnswer);

	for(unsigned int l = 0; l < UserAnswer.length(); l++)
	{
		UserAnswer[l] = toupper(UserAnswer[l]);
	}

	system("CLS");

	if(UserAnswer.find("PINK") != string::npos)
	{
		UserAnswer = "PINK";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "PINK was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "PINK was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("BLUE") != string::npos)
	{
		UserAnswer = "BLUE";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "BLUE was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "BLUE was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("BLACK") != string::npos)
	{
		UserAnswer = "BLACK";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "BLACK was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "BLACK was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("WHITE") != string::npos)
	{
		UserAnswer = "WHITE";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "WHITE was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "WHITE was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("PURPLE") != string::npos)
	{
		UserAnswer = "PURPLE";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "PURPLE was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "PURPLE was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("RED") != string::npos)
	{
		UserAnswer = "RED";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "RED was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "RED was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("YELLOW") != string::npos)
	{
		UserAnswer = "YELLOW";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "YELLOW was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "YELLOW was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("ORANGE") != string::npos)
	{
		UserAnswer = "ORANGE";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "ORANGE was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "ORANGE was not an impostor";
			TaskProgress = TaskProgress + 25;
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("GREEN") != string::npos)
	{
		UserAnswer = "GREEN";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "GREEN was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "GREEN was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else if(UserAnswer.find("BROWN") != string::npos)
	{
		UserAnswer = "BROWN";

		if(UserAnswer == Impostor)
		{
			gotoXY(34,17); cout << "BROWN was an impostor.";
			TaskProgress = TaskProgress + 25;
			ProgressBar(1);
			PowerUp++;
		}

		else
		{
			gotoXY(34,17); cout << "BROWN was not an impostor";
			CrewTrust = CrewTrust - 2;
		}

		cin.ignore();
		system("CLS");
	}

	else
	{
		GameOfficiallyOver = 2;
		gotoXY(18,17); cout << "You've been ejected by your own crew members for not cooperating!";
		cin.ignore();
		GameOver();
	}

	if(CrewTrust == 0)
	{
		GameOfficiallyOver = 1;
	}
}

void MobilePhone::InitLeaderBoard() //LEADERBOARD INITIALIZER
{
	int LineCounter = 0;
	string LeaderBoardHeader;

	//reader
	ifstream Reader;
	Reader.open("LEADERBOARD.txt");
	
	getline(Reader, LeaderBoardHeader);
	getline(Reader, LeaderBoardHeader);
	getline(Reader, LeaderBoardHeader);

	while(Reader >> CrewLeaderName >> TaskPoints)
	{
		LineCounter++;	
	}

	Reader.close();

	//writer
	if (LineCounter == 0)
	{
		ofstream Writer;
		Writer.open("LEADERBOARD.txt");
		Writer << "LEADERBOARD" << endl << endl;
		Writer << "Crew Leader" << setw(25) << "Task Points";
		Writer.close();
	}
}

void MobilePhone::LeaderBoard() //TOP SCORERS SECTION
{
	system("CLS");
	GameSpaceBackground();

	gotoXY(67,1);cout << "LEADERBOARD" << endl << endl;
	gotoXY(54,3);cout << " Crew Leader" <<  setw(25) << "Task Points" << endl << endl;

	BubbleSort(TaskPointsArray, CrewLeadersArray);

	for(int i=0; i < 10; i++)
	{
		if(TaskPointsArray[i] != 0)
		{
			gotoXY(57,5+i); cout << CrewLeadersArray[i] <<  setw(25) << TaskPointsArray[i] << endl;
		}	
	}

	gotoXY(70,36); cout << "[B]ACK";
	gotoXY(69,38); cout << "INPUT: ";
	while (!(cin >> UserChoice) || toupper(UserChoice) != 'B')
	{
		gotoXY(55,38); cerr << "INVALID INPUT! TRY AGAIN! [Press B only]";
		Fernandizer();
		gotoXY(55,38); cerr << "                                        ";
		gotoXY(69,38); cout << "INPUT: ";
	}

	switch(toupper(UserChoice))
	{
		case 'B':
			Game();
			break;
	}
}

void MobilePhone::LeaderBoardReader() //LEADERBOARD DATA READER
{
	string LeaderBoardHeader;
	
	int i=0;
	ifstream Reader;
    Reader.open("LEADERBOARD.txt");

	getline(Reader, LeaderBoardHeader);
	getline(Reader, LeaderBoardHeader);
	getline(Reader, LeaderBoardHeader);

	while(Reader >> CrewLeaderName >> TaskPoints)
	{
		CrewLeadersArray[i] = CrewLeaderName;
		TaskPointsArray[i] = TaskPoints;
		i++;
	}
}

void MobilePhone::LeaderBoardWriter() //LEADERBOARD DATA WRITER
{
	string LeaderBoardData;

	if(TaskPoints != 0)
	{
		ofstream Writer;
		Writer.open("LEADERBOARD.txt", ios::app);
		Writer << endl << CrewLeaderName << setw(25) << TaskPoints << endl;
		Writer.close();
	}    
}

void MobilePhone::Reset() //GAME DATA RESETTER
{
	GameOfficiallyOver = 0;
	CrewLeaderName.clear();
	TaskDone = 0;
	TaskProgress = 0;
	TaskPoints = 0;
	CrewTrust = 10;
	PowerUp = 0;
}

//GAME GRAPHICS//

void MobilePhone::GameTitleScreen() //GAME TITLE SCREEN SIZE
{
	system("color 0F");

	RECT Window;
	MoveWindow(GetConsoleWindow(), GetSystemMetrics(SM_CXSCREEN) / 2 - 1200 / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - 640 / 2, 1200, 640, TRUE);
	system("mode con: cols=150 lines=40");
}

void MobilePhone::GameTitle() //AMONG US: C++ EDITION IMPROVISED GAME TITLE
{
   	gotoXY(5,5);  cout << "         ,@@@@@&,              #@         @@       ,@@@%      @@       @&     #@@@@#                   @@          &@    ,@@@@@@,      ";
   	gotoXY(5,6);  cout << "        @&       %@&           @@&       /@@,     (@/  #@&   (@@@      @&   .@@                        @@          @@   @@.     &%     ";
   	gotoXY(5,7);  cout << "      *@/,#%&@@%,  *@         *@@@       @&@%     @&    .@#  (@ @&     @%  ,@&                         @@          @&  @@              ";
   	gotoXY(5,8);  cout << "      @/@%      /@  &@#@.     &@ @(      @.&@    /@*     &@  (@ .@     @&  @@                          %@          @&  @/              ";
   	gotoXY(5,9);  cout << "     && @        @#  @( @.    @% #@     @@ *@    #@      ,@  /@  @@    @@  @&                          (@          @&  @@              ";
   	gotoXY(5,10); cout << "     @, (@@@&@@@@@,  &@ %@   /@   @%    @(  @(   &@      .@( /@   @#   @@  @/                           @,         @%   @@#            ";
	gotoXY(5,11); cout << "    /@               .@  @   @@   (@   /@   &@   &@      .@( /@   #@   @@ *@*                           @%         @#      &@@%        ";
    gotoXY(5,12); cout << "    @@                @. @*  @.    @#  @@   *@   &@      ,@  /@    @%  &@ ,@*       ((((%               @@        .@          .@@%     ";
    gotoXY(5,13); cout << "    @%                @%@@  %@     @@  @/    @/  (@      %@  /@    /@. @@  @/      #@                   %@        /@  *@         @@    ";
    gotoXY(5,14); cout << "    @%     (@@@@#     @%    @%      @,#@     @&  ,@/     @@  /@     @@ @@  @(      %@                    @*       @@  /@          @*   ";
    gotoXY(5,15); cout << "    @%    @%   #@.    @@   .@       @%@&     &@   @@     @(  /@      @/@&  @@      @@                    @@       @#  *@          @*   ";
    gotoXY(5,16); cout << "    @&    @#    @.    %@   @@       #@@/     ,@   ,@(   @@   /@      &@@%  ,@#    .@#                     @&     @@    @@       .@%    ";
    gotoXY(5,17); cout << "    &@////@.    @%////&@  .@(        @@       @%   (@@@@@    ,@*      @@    .@@@@@@#                       @@&#@@%      &@@&%@@@&      ";  
	gotoXY(60,20); cout << "C  +  +   E  D  I  T  I  O  N";                                                                                                                                         
}

void  MobilePhone::GameCharacter() //AMONG US: C++ EDITION IMPROVISED GAME CHARACTER
{
	SetConsoleTextAttribute(color,FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
	cout << endl << endl << endl << endl << endl << endl;
	cout << "            .,,,,,,,,,               "<< endl;
   	cout << "         ,,,,,,,,,,,,,,,,            "<< endl;
    cout << "        .,,,,,                       "<< endl;
   	cout << "       .,,,,   ,#%%%%@@@@@@@%*       "<< endl;
   	cout << "       .,,,,   **%%%%%%%%%%%%%%*     "<< endl;
    cout << "  ***  ..,,,,.  *****(((((/*****,    "<< endl;
    cout << " ****  ..,,,,,    ************       "<< endl;
    cout << "****  ...,,,,,,                      "<< endl;
    cout << "*****  ...,,,,,,,,,,,,,,,,,,,,.      "<< endl;
    cout << "*****  ....,,,,,,,,,,,,,,,,,,,.      "<< endl;
  	cout << "*****  .....,,,,,,,,,,,,,,,,,..      "<< endl;
    cout << "*****  ......,,,,,,,,,,,,,,,...      "<< endl;
    cout << " ****  ***********************       "<< endl;
    cout << "       **********************        "<< endl;
  	cout << "       ********       *******        "<< endl;
  	cout << "       ********      *******         "<< endl;
    cout << "       *******      *******          "<< endl;		
	SetConsoleTextAttribute(color, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

void MobilePhone::GameSpaceBackground() //AMONG US: C++ EDITION IMPROVISED GAME BACKGROUND
{                                                                                                                                                
    for(int i=0; i < 420; i++)
	{
		cout << "." << setw(5) << "." << setw(9);
	}
}

void MobilePhone::LoadingScreen() //MULTI-LEVEL LOADING SCREEN
{
	int m1 = 99, m2 = 39, m3 = 0, m4 = 0;

	gotoXY(0, 0);

	for (int i = 0; i <= 19; i++) 
	{
		for (int i = CursorPosition.X; i <= m1; i++) 
		{
			gotoXY(i, CursorPosition.Y); cout<<char(219);
			Sleep(0.9);
		}
		for (int i = CursorPosition.Y; i <= m2; i++) 
		{
			gotoXY(CursorPosition.X, i); cout<<char(219);
			Sleep(0.9);
		}
		m1--;
		m2--;
		for (int i = CursorPosition.X; i >= m3; i--) 
		{
			gotoXY(i, CursorPosition.Y); cout<<char(219);
			Sleep(0.9);
		}
		m4++;
		for (int i = CursorPosition.Y; i >= m4; i--) 
		{
			gotoXY(CursorPosition.X, i); cout<<char(219);
			Sleep(0.9);
		}
		m3++;
	}

	system("CLS");
}

void MobilePhone::ProgressBar(int BarStyle) //IMPROVISED PROGRESS BAR FOR TASK PROGRESS
{
	if(BarStyle == 1 && GameOfficiallyOver == 0)
	{
		if(TaskDone < 5)
		{
			TaskProgress = TaskProgress + 5;

			if(TaskProgress >= 100)
			{
				GameOfficiallyOver = 1;
				TaskPoints = TaskProgress * 10;
				TaskProgress = 100;
				GameOver();
			}
		}
		
		else if(TaskDone >= 5 && TaskDone <= 10)
		{
			TaskProgress = TaskProgress + 10;
			
			if(TaskProgress >= 100)
			{
				GameOfficiallyOver = 1;
				TaskPoints = TaskProgress * 10;
				TaskProgress = 100;
				GameOver();
			}
		}
		
		else if(TaskDone > 10)
		{
			TaskProgress = TaskProgress + 15;

			if(TaskProgress > 100)
			{
				GameOfficiallyOver = 1;
				TaskPoints = TaskProgress * 10;
				TaskProgress = 100;
				GameOver();
			}
		}

		gotoXY(38,37); cout << "Task Progress [" << TaskProgress << "%]";

		TaskPoints = TaskProgress * 10;

		gotoXY(41,3); cout << "Task Points [" << TaskPoints << "]";

		if(GameOfficiallyOver == 0)
		{
			for(int b = 0; b < 100; b++)
			{
				gotoXY(0+b,39); cout << char(176);
			}
		}

		if(GameOfficiallyOver == 0)
		{
			for(int t = 0; t < TaskProgress; t++)
			{
				gotoXY(0+t,39); cout << char(219);
				Sleep(10);
			}
		}

		Fernandizer();
		system("CLS");
	}

	if(BarStyle == 2 && GameOfficiallyOver == 0)
	{
		if(TaskDone < 5)
		{
			TaskProgress = TaskProgress - 4;
		}
		
		else if(TaskDone >= 5 && TaskDone <= 10)
		{
			TaskProgress = TaskProgress - 8;
		}
		
		else if(TaskDone > 10)
		{
			TaskProgress = TaskProgress - 12;
		}
		
		gotoXY(38,37); cout << "Task Progress [" << TaskProgress << "%]";

		gotoXY(41,3); cout << "Task Points [" << TaskPoints << "]";

		for(int b = 0; b < 100; b++)
		{
			gotoXY(0+b,39); cout << char(176);
		}

		for(int t = 0; t < TaskProgress; t++)
		{
			gotoXY(0+t,39); cout << char(219);
			Sleep(10);
		}

		cin.ignore();
		system("CLS");
	}
}

void MobilePhone::GameOver() //END GAME SCREEN
{
	if(CrewTrust == 0 && GameOfficiallyOver == 1)
	{
		system("CLS");
		GameTitleScreen();
		GameSpaceBackground();

		gotoXY(40,15); cout << " _______   _______  _______  _______     ___   .___________. __  ";
		gotoXY(40,16); cout << "|       \\ |   ____||   ____||   ____|   /   \\  |           ||  | ";
 		gotoXY(40,17); cout << "|  .--.  ||  |__   |  |__   |  |__     /  ^  \\ `---|  |----`|  |";
 		gotoXY(40,18); cout << "|  |  |  ||   __|  |   __|  |   __|   /  /_\\  \\    |  |     |  |  ";
 		gotoXY(40,19); cout << "|  '--'  ||  |____ |  |     |  |____ /  _____  \\   |  |     |__| ";
   		gotoXY(40,20); cout << "|_______/ |_______||__|     |_______/__/     \\__\\  |__|     (__) ";
	                                                    
		Fernandizer();
		system("CLS");

		LeaderBoardWriter();
		
		Game();
	}

	else if (TaskProgress == 100 && GameOfficiallyOver == 1)
	{
		system("CLS");
		GameTitleScreen();
		GameSpaceBackground();

		gotoXY(32,15); cout << "____    ____  __    ______ .___________.  ______   .______     ____    ____  __        ";
		gotoXY(32,16); cout << "\\   \\  /   / |  |  /      ||           | /  __  \\  |   _  \\    \\   \\  /   / |  | ";
 		gotoXY(32,17); cout << " \\   \\/   /  |  | |  ,----'`---|  |----`|  |  |  | |  |_)  |    \\   \\/   /  |  |   ";
 		gotoXY(32,18); cout << "  \\      /   |  | |  |         |  |     |  |  |  | |      /      \\_    _/   |  |     ";
 		gotoXY(32,19); cout << "   \\    /    |  | |  `----.    |  |     |  `--'  | |  |\\  \\----.   |  |     |__|    ";
   		gotoXY(32,20); cout << "    \\__/     |__|  \\______|    |__|      \\______/  | _| `._____|   |__|     (__)    ";

		Fernandizer();
		system("CLS");

		LeaderBoardWriter();

		Game();
	}

	else if (GameOfficiallyOver == 2)
	{
		system("CLS");
		GameTitleScreen();
		GameSpaceBackground();

		gotoXY(25,15); cout << " _______       ___      .___  ___.  _______      ______   ____    ____  _______ .______       __        ";
		gotoXY(25,16); cout << "/  _____|     /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     |  | ";
 		gotoXY(25,17); cout << "|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    |  |  ";
 		gotoXY(25,18); cout << "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     |  |  ";
 		gotoXY(25,19); cout << "|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.|__|  ";
   		gotoXY(25,20); cout << "\\_______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|(__)  ";                                                                                               

		Fernandizer();
		system("CLS");

		LeaderBoardWriter();

		Game();
	}
}

void MobilePhone::MerryXmas() //MERRY XMAS SER!
{
	system("color F0");

	RECT Window;
	GetWindowRect(GetConsoleWindow(), &Window);
	MoveWindow(GetConsoleWindow(), GetSystemMetrics(SM_CXSCREEN) / 2 - 660 / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - 640 / 2, 660, 640, TRUE);// Gets the size of the monitor display in order to perfectly center the console
	system("mode con: cols=80 lines=40");

	int row;
	int h = 1;
	int i = 1;
	int j = 1;

	SetConsoleTextAttribute(color,FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
	gotoXY(15, 0); cout << "HOW TALL DO YOU WANT FOR YOUR CHRISTMAS TREE? [3-8]: ";
	while(!(cin >> row) || (row < 3 || row > 8))
	{
		gotoXY(15, 0); cout << "                                                         ";
		gotoXY(15, 0); cout << "HOW TALL DO YOU WANT FOR YOUR CHRISTMAS TREE? [3-8]: ";
	}

	SetConsoleTextAttribute(color,FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	CursorPosition.Y += 2;
	for (int h = 1; h <= row; h++)
	{
		for (int i = 1; i <= h; i++)
		{
			gotoXY(37 - (row / 2), CursorPosition.Y);
			for (int j = 1; j <= 2 * row - 1; j++)
			{
				Sleep(1);
				if (j >= row - (i - 1) && j <= row + (i - 1))
				{
					cout << "$";
				}
				else
				{
					cout << " ";
				}
			}
			cout << endl;
			CursorPosition.Y++;
		}
	}
	SetConsoleTextAttribute(color,FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
	cout << "\n\t\t\tMERRY CHRISTMAS FROM GONG YOO!";
	Fernandizer();
	Game();
}