/*========================================
Author: Miran Member
=========================================
To use the custome Command:1) load in the districts and eligible_voters files. 2.) search for
a state 3.) type participant 4) the result should display how many people were
eligible_voters but did not vote. also displays a message to enocourage the user to vote.
*/
#include <ctype.h>  // needed this to uppercase the letters
#include <fstream>
#include <iostream>
#include <string>
#include "ourvector.h"
using namespace std;
/*structs to store districts.txt, structs make it so much easier to access the information
from the text file.*/
struct District {
	string name;
	int maxDist;
	ourvector<int> garryMandering;
};
struct Voters {
	string name;
	string voters;
};
/*=====================================================================
LOAD FUNCTION FROM THIS POINT ON
----------------------------------------------------------------------*/
/* converts the string that it recives from lower case to uppercase, I need to do this so I
can compare input with files state names.*/
string toUpper(string &str) {
	for(int i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}
/* when the load command is called this specific funcion is sub funcion for the load funcion.
it chops the name off the name from the lines and returns it*/
string getName(string &line) {
	int pos = line.find(",");
	string Name = line.substr(0, pos);
	line = line.substr(pos + 1, line.size() - Name.size() - 1);
	return Name;
}

/* also a sub funcion for the load funcion, this funcion gets the District
and also counts how many District there are using counter and returns it*/
int getDistrict(string &line) {
	int count = 0;
	while (!line.empty()) {
		count++;
		District district1;
		size_t pos = line.find(',');
		string numDistrict = line.substr(0, pos);
		if (numDistrict == "AL") {
			numDistrict = "1";
		}
		district1.garryMandering.push_back(stoi(numDistrict));
		line = line.substr(pos + 1, line.size() - numDistrict.size() - 1);
		pos = line.find(",");
		string demVotes = line.substr(0, pos);
		district1.garryMandering.push_back(stoi(demVotes));
		line = line.substr(pos + 1, line.size() - demVotes.size() - 1);
		pos = line.find(",");
		string repVotes;
		if ((int)pos == -1) {
			repVotes = line;
			district1.garryMandering.push_back(stoi(repVotes));
			line = "";
		} else {
			repVotes = line.substr(0, pos);
			district1.garryMandering.push_back(stoi(repVotes));
			line = line.substr(pos + 1, line.size() - repVotes.size() - 1);}
	}
	return count;
}
/* First of all I did not even know you can create a vector funcion,
but I learned you can. COOL!! I used that to my advantage and created
this funcion that recives a line that has all the district information
other then the name. it uses that to store all the districts for
each state in a vector*/
ourvector<int> getVotes(string &line, ourvector<int> &district1) {
	getName(line);
	while (!line.empty()) {
		size_t pos = line.find(',');
		string numDistrict = line.substr(0, pos);
		if (numDistrict == "AL") {
			numDistrict = "1";}
		district1.push_back(stoi(numDistrict));
		line = line.substr(pos + 1, line.size() - numDistrict.size() - 1);
		pos = line.find(",");
		string demVotes = line.substr(0, pos);
		district1.push_back(stoi(demVotes));
		line = line.substr(pos + 1, line.size() - demVotes.size() - 1);
		pos = line.find(",");
		string repVotes;
		if ((int)pos == -1) {
			repVotes = line;
			district1.push_back(stoi(repVotes));
			line = "";
		} else {
			repVotes = line.substr(0, pos);
			district1.push_back(stoi(repVotes));
			line = line.substr(pos + 1, line.size() - repVotes.size() - 1);}
	}
	return district1;
}
/* recives file name and the ourvector. This funcion will load all the data from the the file
to the vector. including name of the state and max District, and all the District info using structs
*/
void loadDistrict(string fileName, ourvector<District> &district) {
	ifstream inFile(fileName);
	string line;
	getline(inFile, line, '\n');
	while(!inFile.eof()) {
		District district1;
		string temp = line;
		district.push_back({getName(line), getDistrict(line),
							getVotes(temp, district1.garryMandering)});
							//  neat trick to store values in the vector directly.
		getline(inFile, line, '\n');}
}

string getVoters(string &line) {
	return line;
}
/* Does the same process as the previous function but this time it
loads the eligible_voters file.*/
void loadVoters(string fileName, ourvector<Voters> &voters) {
	ifstream inFile(fileName);
	string line;
	getline(inFile, line, '\n');
	while(!inFile.eof()) {
		if (!line.find("District")) {
			getline(inFile, line, '\n');
			continue;
		}
		voters.push_back({getName(line), getVoters(line)});
		getline(inFile, line, '\n');
	}
}
/* THIS IS THE MAIN LOADFILE COMMAND FUNCTION. 
It calls other sub function to work. Also couts the text from the
function rather then in the main.
*/ 
void commandLoad(ourvector<District> &district, ourvector<Voters> &voters,
				string &dataLoadedStatus) {
	string command;
	for (int i = 0; i < 2; i++) {  //  loops 2 times because you
	                               //  input 2 diffrent files at once
		cin >> command;
		if (command == "districts.txt" || command == "districts_fantasy.txt" ||
		    command == "districts_short.txt") {
			cout << "Reading: " << command << endl;
			loadDistrict(command, district);
			for (auto &e : district) {
				cout << "..." << e.name << "..." << e.maxDist << " districts total" << endl;
			}
			dataLoadedStatus = "Yes";
		} else if (command == "eligible_voters.txt"||
				  command == "eligible_voters_fantasy.txt"||
				  command == "eligible_voters_short.txt") {
			cout << "Reading: " << command << endl;
			loadVoters(command, voters);
			for (auto &e : voters) {
				cout << "..." << e.name << "..." << e.voters << " eligible voters" << endl;
			}
			dataLoadedStatus = "Yes";
		} else if (i == 0) {
			cout << "Invalid first file, try again." << endl;
			dataLoadedStatus = "No";
			cin >> command;
			break;
		} else {
			cout << "Invalid second file, try again."<< endl;
			dataLoadedStatus = "No";
			break;
		}
	}
}
/*============================================================
END OF LOAD FUNCTION
SEARCH FUNCTION FROM THIS POINT ON
-------------------------------------------------------------*/
/* searches through the vector untill it matches the user inputed
state. if state doesnot exist cout and error. user Linear Search. 
Also changes the stateStatus to the state searched which is
important as i use it in other funcions.*/
void search(ourvector<District> &district, ourvector<Voters> &voters,
			string &stateStatus) {
	string command;
	cin.ignore();
	getline(cin, command);
	toUpper(command);
	string temp = stateStatus;
	for (auto &e : district) {
		string str = e.name;
		string check = toUpper(str);
		if (command == check) {
			stateStatus = e.name;
		}
	}
	if(stateStatus == temp) {
		cout << "State does not exist, search again." << endl;
	}
}
/*===============================================================
END OF SEARCH FUNCTION
/*Sub function for the stats command. this function will calculate
the wasted votes and also total votes for the state.*/
void calculateWastedVotes(ourvector<int> &garryMandering,
						  int &demWastedVotes, int &repWastedVotes,
						  int &totalVotes) {
	int count = 1;
	int count1 = 2;
	int repWasted = 0;
	int demWasted = 0;
	int overHalf;
	for(auto&e : garryMandering) {
		if(count1 == 3) {
			demWasted = e;
			count1 = 0;
		} else if ((count%3) == 0) {
			repWasted = e;
			(repWasted == 0 && demWasted == 0) ?
			overHalf = 0 :
			overHalf = ((repWasted + demWasted) / 2) + 1;
			totalVotes = totalVotes + (repWasted + demWasted);
			if (repWasted < demWasted) {
				demWastedVotes = demWastedVotes + (demWasted - overHalf);
				repWastedVotes = repWastedVotes + repWasted;
			} else {
				demWastedVotes = demWastedVotes + demWasted;
				repWastedVotes = repWastedVotes + (repWasted - overHalf);
			}
		}
		count++; count1++;
	}
}
/*sub function which calcultes the gerryMandering and againts who*/
void calculateGerryMending(int maxDist, int demWastedVotes,
						   int repWastedVotes, int totalVotes) {
	string gerryMandering = "No";
	string against;
	double x = 0.0;
	if(maxDist < 3) {
		gerryMandering = "No";
	} else if (repWastedVotes < demWastedVotes) {
		x = demWastedVotes - repWastedVotes;
		x = x/ totalVotes;
		x = x* 100;
		against = "Democrats";
	} else if (repWastedVotes > demWastedVotes) {
		x = repWastedVotes - demWastedVotes;
		x = x/ totalVotes;
		x = x* 100;
		against = "Republicans";
	}
	if (x == 7 || x > 7) {
		gerryMandering = "Yes";
	}
	cout << "Gerrymandered: " << gerryMandering << endl;
	if(gerryMandering ==  "Yes") {
		cout << "Gerrymandered against: " << against << endl;
		cout << "Efficiency Factor: " << x << "%" << endl;
	}
}
/* Main stats function which calls other sub function to display
the wasted votes, and if there was Gerrymandering.*/
void stats(ourvector<District> &district,
		   ourvector<Voters> &voters, string stateStatus) {
	toUpper(stateStatus);
	int demWastedVotes = 0;
	int repWastedVotes = 0;
	int totalVotes = 0;
	//  loops through the vector untill same state and then displays
	//  the information of that state
	for (auto &e : district) {
		string str = e.name;
		string check = toUpper(str);
		if (stateStatus == check) {
			calculateWastedVotes(e.garryMandering, demWastedVotes,
								 repWastedVotes, totalVotes);
			calculateGerryMending(e.maxDist, demWastedVotes,
								  repWastedVotes, totalVotes);
			cout << "Wasted Democratic votes: " << demWastedVotes <<
			endl << "Wasted Republican votes: " << repWastedVotes <<
			endl << "Eligible voters: ";
		}
	}
	for (auto &e : voters) {  //  do displays the Eligible voters
							  //  from the second vector
		string str = e.name;
		string check = toUpper(str);
		if (stateStatus == check) {
			cout << e.voters << endl;
		}
	}
}
/*===========================================================
END OF STATS command
PLOT COMMAND FROM THIS POINT ON
-------------------------------------------------------------*/
/* sub function which calcuates how many D and R to plot when called*/
void demPlots(ourvector<int> &garryMandering) {
	int total;
	float demPlot;
	float repPlot;
	int count = -1;
	for(auto &e : garryMandering) {
		count++;
		if (count == 0) {
			cout << "District: " << e << endl;
		} else if (count == 1) {
			demPlot = e;
		} else if (count == 2) {
			repPlot = e;
			total = repPlot + demPlot;
			(demPlot == 0) ? demPlot = 0: demPlot = demPlot/total;
			//  makes sure that demplot stays 0 if the vector had 0
			demPlot = demPlot * 100;
			count = -1;
			demPlot = (int)(demPlot);
			(repPlot == 0) ? repPlot = 0: repPlot = 100 - demPlot;
			//  same as above makes sure it stays 0
			for (int i = 0; i < demPlot; i++) {
				cout << "D";
			}
			for(int i = 0; i < repPlot; i++) {
				cout << "R";
			}
			cout << endl;
		}
	}
}
/*Main PLOT funcion which displays D and R depanding on 
the votes a state has.*/
void plot(ourvector<District> &district, string stateStatus) {
	for (auto &e : district) {
		string temp = e.name;
		string check = toUpper(temp);
		stateStatus = toUpper(stateStatus);
		if (stateStatus == check) {
			demPlots(e.garryMandering);
		}
	}
}
/*===========================================================
END OF PLOT FUNCTION
PARTICIPANT FUNCTION FROM THIS POINT ON(CREATIVE COMPONANT)
calculates the amount of voters who did not vote and also 
encourages to vote :) */
void calculateParticipant(ourvector<int> &garryMandering, string total) {
	int totalVotes;
	int count = -1;
	for(auto &e : garryMandering) {
		count++;
		if (count == 0) {
			continue;
		} else if (count == 1) {
			totalVotes += e;
		} else if (count == 2) {
			totalVotes += e;
			count = -1;
		}
	}
	int temp = (int)(stoi(total)) - totalVotes;
	cout <<
		  "MMM/    -mmmmh         smmmm:     .ohNMMMMNds-      dmmmmmmmmmmmmmmmm/   "
		 << "`mmmmmmmmmmmmmmmm+    `ssMM" << endl
		 <<
		  "MMN.     sMMMMo       -MMMMy    `yMMMMMMMMMMMMd.    mMMMMMMMMMMMMMMMM/   "
		 << "`MMMMMMMMMMMMMMMMo     /sMM" << endl
		 <<
		 "MMd       dMMMM.     `mMMMm`   .mMMMMy-``-sMMMMN-   ------dMMMM/-----`   "
		 << "`MMMMm:::::::::::.     -yNM" << endl
		 <<
		 "MMs       .NMMMd     sMMMM-    hMMMM+      :MMMMm         hMMMM.         "
		 << "`MMMMd                 `yhM" << endl
		 <<
		 "MMo        +MMMM+   -MMMMo    .MMMMm        yMMMM:        hMMMM.         "
		 << "`MMMMNyyyyyyyyyyo      `hyM" << endl
		 <<
		 "MM/         hMMMN. `mMMMh     :MMMMh        oMMMM+        hMMMM.         "
		 << "`MMMMMMMMMMMMMMMh      `dyM" << endl
		 <<
		 "MMo         `NMMMh sMMMN.     -MMMMm        yMMMM/        hMMMM.         "
		 << "`MMMMm//////////:      `hyM" << endl
		 <<
		 "MMy          :MMMM/MMMM:       dMMMM:      .NMMMN`        hMMMM.         "
		 << "`MMMMd                 .hdM" << endl
		 <<
		 "MMm`          sMMMNMMMs        -NMMMMo`  `/NMMMM:         hMMMM.         "
		 << "`MMMMd...........`     :yNM" << endl
		 <<
		 "MMM-           dMMMMMm          .dMMMMMNNMMMMMm:          hMMMM.         "
		 << "`MMMMMMMMMMMMMMMMo     ysMM" << endl 
		 <<
		 "MMMs           .NMMMN.            :ymMMMMMMNh/            hMMMM.         "
		 << "`MMMMMMMMMMMMMMMMo    .dhMM" << endl;
	cout << "Remember to vote this November." << endl
		 << totalVotes << " people voted." << endl
		 << "There are " << total << " eligible Voters." << endl
		 << "That means " << temp << " people did not vote." << endl;
}
/*calls the function which displays the info on the terminal*/
void participant(ourvector<District> &district,
		   ourvector<Voters> &voters, string stateStatus) {
	string totalEligibleVoters;
	for (auto &e : voters) {
		string str = e.name;
		string check = toUpper(str);
		stateStatus = toUpper(stateStatus);
		if (stateStatus == check) {
			totalEligibleVoters = e.voters;
		}
	}
	for (auto &e : district) {
		string temp = e.name;
		string check = toUpper(temp);
		if (stateStatus == check) {
			calculateParticipant(e.garryMandering, totalEligibleVoters);
		}
	}
}
/*============================================================
END OF FUNCTIONS START OF MAIN*/
int main() {
	string stateStatus = "N/A";  //  default state
	ourvector<District> district;
	ourvector<Voters> voters;
	string dataLoadedStatus = "No";  //  this strin changes to yes
									 //  when you load the files in so its basically a check to make
									 //  sure that the data is loaded before user access it.
	string command;
	cout << "Welcome to the Gerrymandering App!" << endl;
	while (true) {  // runs until exit
		cout << endl << "Data loaded? " << dataLoadedStatus << endl;
		cout << "State: " << stateStatus << endl << endl;
		cout << "Enter command: ";
		cin >> command;
		cout << endl << endl << "-----------------------------" << endl << endl;
		if (command == "load") {
			if (dataLoadedStatus == "Yes") {
				cout << "Already read data in, exit and start over." << endl;
				cin >> command;  //  discard the rest of the command
				cin >> command;  //  discard the rest of the command
			} else {
				commandLoad(district, voters, dataLoadedStatus);
			}
		} else if (command == "exit") {
			break;
		} else if (dataLoadedStatus == "No") {
			getline(cin, command);  //  since some states have space in 
									//  between its better to user getline
			cout << "No data loaded, please load data first." << endl;
			continue;
		} else if (command == "search") {
			search(district, voters, stateStatus);
		} else if (stateStatus == "N/A") {
			cout << "No state indicated, please search for state first." << endl;
			continue;
		} else if (command == "stats") {
			stats(district,voters,stateStatus);
		} else if (command == "plot") {
			plot(district, stateStatus);
		} else if (command == "participant") {
			participant(district, voters, stateStatus);
		}
	}
    return 0;
}
/*====================================================================*/


