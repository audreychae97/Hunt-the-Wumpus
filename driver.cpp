/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	Project Title:	Hunt the Wumpus
//	Class:			CSS 342
//	Professor:		John Chenault
//	Created by:		Ye Eun (Audrey) Chae
//	Platform:		MacOS Sierra 10.12.6
//	Environment:	VIM/ g++ -std=c++11
//	Date Created:	November 30, 2017
//	Duration:		20 hours
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "room.h"
#include "character.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdexcept>
#include <ctime>
#include <ctype.h>
#include <stdio.h>

using namespace std;


//////////////////////////////////////////////////////////////////////////////
//	randNum()	Generates a random integer from 0 - 7
//////////////////////////////////////////////////////////////////////////////
int randNum(){
	return  rand() % 8;
}

//////////////////////////////////////////////////////////////////////////////
//	moveWumpus()	moves the wumpus elsewhere because character missed!
//////////////////////////////////////////////////////////////////////////////
void moveWumpus(vector<vector<Room> > & popMap){
	int wRow;	
	int wCol;
	int nRow;
	int nCol;

	//find the wumpus
	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){
			if(popMap.at(row).at(col).hasWumpus()){
				wRow = row;
				wCol = col;
			}
		}
	}
	//remove from current room
	popMap.at(wRow).at(wCol).setWumpus(false);
	//set into a new room..
	int dir = rand() % 5;	//four possibilites of moving
	if(dir == 0){		//left
		nRow = wRow;
		nCol = wCol - 1;
	}
	else if (dir == 1){	//up
		nRow = wRow - 1;
		nCol = wCol;
	}
	else if(dir == 2){	//right
		nRow = wRow;
		nCol = wCol + 1;
	}
	else if(dir == 3){	//down
		nRow = wRow + 1;
		nCol = wCol;
	}
	else{	//stay
		nRow = wRow;
		nCol = wCol;
	}
	// set initial values and then check for edge cases 
	if(wRow == 0){	
		nRow == 0;
	}	
	if(wCol == 0){
		wCol == 0;
	}
	if (wRow == 7){
		nRow == 7;
	}
	if (wCol == 7){
		wCol == 7;
	}
	popMap.at(nRow).at(nCol).setWumpus(true);
}
//////////////////////////////////////////////////////////////////////////////
//	stepChecker()	returns false if you try to move or shoot into a wall
//////////////////////////////////////////////////////////////////////////////
bool stepChecker(char step, Character & zeus){
	if((zeus.getRow() == 0) && ((step == 'i') || (step == 'I'))){	
		return false;
	}
	else if((zeus.getRow() == 7) && ((step == 'm') || (step == 'M'))){
		return false;
	}
	else if((zeus.getCol() == 0) && ((step == 'j') || (step == 'J'))){
		return false;
	}
	else if((zeus.getCol() == 7) && ((step == 'l') || (step == 'L'))){
		return false;
	}
	else{
		return true; // a valid step
	}

}
//////////////////////////////////////////////////////////////////////////////
//	shoot()	checks and validates the move 
//////////////////////////////////////////////////////////////////////////////
bool shoot(vector<vector<Room> > popMap, Character& zeus, char dir){
	int currRow = zeus.getRow();
	int currCol = zeus.getCol();
	int sRow;
	int sCol;	
	//validate move
	if(stepChecker(dir, zeus) == false){ //shot into a wall 
		cout << "You shot into a wall! What a waste of an arrow.." << endl;
		return false; //wumpus is not a wall.. missed! 
	}
	else{	//check what the shot was
		if(dir == 'I'){	//shoot up
			sRow = currRow -1;
			sCol = currCol;
		}
		else if(dir == 'J'){	//shoot left
			sRow = currRow;
			sCol = currCol - 1;
		}
		else if(dir == 'M'){ //shoot down
			sRow = currRow + 1;
			sCol = currCol;
		}
		else if(dir == 'L'){	//shoot right
			sRow = currRow;
			sCol = currCol + 1;
		}
		else{
			cout << "Hm.. Do you want to waste your arrows?" << endl;
			sRow = currRow;
			sCol = currCol;
		}
	}

	//check if you got the wumpus or not
	if(popMap.at(sRow).at(sCol).hasWumpus()){
		return true;
		//make this cooler
	}
	else{	//missed... move the wumpus
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////
//	progressCheck()		checks the user's new location and sees if he's alive
//////////////////////////////////////////////////////////////////////////////
void progressCheck(vector<vector<Room> > popMap, Character& zeus){
	int row = zeus.getRow();
	int col = zeus.getCol();
	
	//bat case
	if(popMap.at(row).at(col).hasBats() == true){
		cout << "Landed on a bat! Weeeee " << endl;
		//move the character
		int newRow = randNum();
		int newCol = randNum();
		
		zeus.setLocation(newRow, newCol); 
		//move the bat
		int newRow2 = randNum();
		int newCol2 = randNum();
		popMap.at(row).at(col).setBats(false);
		popMap.at(newRow2).at(newCol2).setBats(true);
		return;
	}
	//pit case = RIP!
	else if(popMap.at(row).at(col).hasPit() == true){
		cout << "[RIP] Landed on a bottomless pit. :( " << endl;
		zeus.die();
		return;
		}
	else if(popMap.at(row).at(col).hasWumpus() == true){
		cout << "[RIP] Landed on a WUMPUS! *CHOMP CHOMP* " << endl;
		zeus.die();
		return;
	}
	else{
			//survived! cool :) 
	}
}
//////////////////////////////////////////////////////////////////////////////
//	hints() -	checks the surroundings adjacent to the character and displays
//				messages 
//////////////////////////////////////////////////////////////////////////////
void hints(vector<vector<Room> > popMap, Character & zeus){
	int currRow = zeus.getRow();
	int currCol = zeus.getCol();
	int up = currRow - 1;
	int down = currRow + 1;
	int left = currCol - 1;
	int right = currCol + 1;
	if(currRow == 0){
		up = 0; 
	}
	if(currCol == 0){
		left = 0;	
	}	
	if(currRow == 7){
		down = 7;
	}
	if(currCol == 7){
		right = 7;
	}
	//Are there bats nearby?
	if((popMap.at(up).at(currCol).hasBats() == true) ||
		(popMap.at(down).at(currCol).hasBats() == true) ||
		(popMap.at(currRow).at(left).hasBats() == true) ||
		(popMap.at(currRow).at(right).hasBats() == true)){
		
		cout << "[HINT] Squeek Squeek! Bats nearby.."<< endl; 
	}
	//Is there a pit nearby? 
	if((popMap.at(up).at(currCol).hasPit() == true) ||
		(popMap.at(down).at(currCol).hasPit() == true) ||
		(popMap.at(currRow).at(left).hasPit() == true) ||
		(popMap.at(currRow).at(right).hasPit() == true)){
		
		cout << "[HINT] *shivers* I feel a breeze nearby.."<< endl; 
	}
	
	if((popMap.at(up).at(currCol).hasWumpus() == true) ||
		(popMap.at(down).at(currCol).hasWumpus() == true) ||
		(popMap.at(currRow).at(left).hasWumpus() == true) ||
		(popMap.at(currRow).at(right).hasWumpus() == true)){
		
		cout << "[HINT] *sniff sniff* It stinks in here.."<< endl; 
	}
}
//////////////////////////////////////////////////////////////////////////////
//	gameRules()		prints the intro and cute little wumpus!
//////////////////////////////////////////////////////////////////////////////
void printMsg(string txtFile){
	string expression;
	ifstream inFile;
	inFile.open(txtFile);
	
	if(!inFile.is_open()){
		cout << "Could not find file" << endl;
	}
	else{
		while(inFile.good()){
			std::getline(inFile, expression);
			cout <<expression << endl;
		}
	}
	inFile.close();	
}
//////////////////////////////////////////////////////////////////////////////
//	makeMap()	Generates a skeleton 2D vector that just contains rooms 
//////////////////////////////////////////////////////////////////////////////
vector<vector<Room> >  makeMap(){
	vector<vector<Room> > MAP(8, vector<Room>(8)); 
	int roomCount = 0;
	for(size_t row = 0; row < 8; row++){
		for(size_t col = 0; col < 8; col++){
			Room newRoom;	
			newRoom.setRoomNum(roomCount);
			MAP.at(row).at(col) = newRoom;
			roomCount++;			
		}
	}
	return MAP;		
}
//////////////////////////////////////////////////////////////////////////////
//	fillMap()	fills skeleton 2D vector (Map) with:
//				- 4 bats 
//				- 4 pits 
//				- 1 wumpus
//////////////////////////////////////////////////////////////////////////////
void fillMap(vector<vector<Room> > & skeleton){
	//create random integer 
	int rand1 = 0;	
	int rand2 = 0;
	
	//Bats - 4 Bats total
	for (int i = 0; i < 4; i++){
		rand1 = randNum();
		rand2 = randNum();

		//at that location in the Map, place a bat!
		skeleton.at(rand1).at(rand2).setBats(true);
	}	
	//Puts - 4 Pits total
	for(int i = 0; i < 4; i++){
		rand1 = randNum();
		rand2 = randNum();
		
		//at that location in the Map, place a pit
		skeleton.at(rand1).at(rand2).setPit();
	}
	//WUMPUS!!
	rand1 = randNum();
	rand2 = randNum();
	skeleton.at(rand1).at(rand2).setWumpus(true);
}
//////////////////////////////////////////////////////////////////////////////
//	printMap()	iterates through the vector and places an appropriate symbol
//				for every instance where that room contains a bat, wumpus, 
//				pit, and/or character. 
//				** A single room CAN contain a bat, pit, and wumpus all at once
//////////////////////////////////////////////////////////////////////////////
void printMap(vector<vector<Room> > & popMap, Character & zeus){
	//Character's current location 
	int currRow = zeus.getRow();
	int currCol = zeus.getCol();

	//a counter for how many rooms in each row of the console. Want 8. 	
	int count = 0; 
	for(size_t row = 0; row < 8; row++){
		for(size_t col = 0; col < 8; col++){
			
			//make sure there are only 8 rooms per row on the display
			if ((count % 8) == 0) {
			cout << endl;
			}
	
			//the type of symbol to be used for each instance 
			 string kind;
			
			//Does that Room have a bat? b = BAT!
			if(popMap.at(row).at(col).hasBats() == true){
				kind.append("B");
			}		
			//Does that Room have a Wumpus? w = WUMPUS!
			if(popMap.at(row).at(col).hasWumpus() == true){
				kind.append("W");
			}
			//Does that Room have a pit? p = PIT!
			if(popMap.at(row).at(col).hasPit() == true){
				kind.append("P");
			}
			//Have we been there already? ::  = FOOTPRINTS!
			else if (popMap.at(row).at(col).beenThere() == true){
				kind.append("::");
			}	
			//else, cases if empty room or character is currently there
			// * = CHARACTER. YOU.
			if((currRow == row) && (currCol == col)){	
				kind.append("*");
			}							
			//print it
			cout << popMap.at(row).at(col).getRoomNum() << " " << kind << "\t";
			count++;	//increase iteration count 
		}
	}
	cout <<"\n" << endl;
}
//////////////////////////////////////////////////////////////////////////////
//	observations()	checks to see if you landed on a bat, a wumpus, a pit.
//					or if you've already been there before
//////////////////////////////////////////////////////////////////////////////
bool observations(vector<vector<Room> > & popMap, Character & zeus){
	int currRow = zeus.getRow();
	int currCol = zeus.getCol();
	if(popMap.at(currRow).at(currCol).beenThere() == true){
		cout <<"\n[ALERT] I see footprints..I've been here before \n" << endl;
	}
	//bat case
	if(popMap.at(currRow).at(currCol).hasBats() == true){
		popMap.at(currRow).at(currCol).setVisited();
		cout << "\n[ALERT] Landed on a bat! Weeee !!\n" << endl;
		
		//move the character elswhere
		int newRow = randNum();
		int newCol = randNum();
		zeus.setLocation(newRow, newCol);
		
		//move the bat, too
		int newRow2 = randNum();
		int newCol2 = randNum();
	
		popMap.at(currRow).at(currCol).setBats(false);
		
		while(popMap.at(newRow2).at(newCol2).hasBats() == true){
			newRow2 = randNum();
			newCol2 = randNum();
		}
		popMap.at(newRow2).at(newCol2).setBats(true);
		return true;
	}
		//pit case = RIP!
	else if(popMap.at(currRow).at(currCol).hasPit() == true){
		cout << "\n[RIP] Landed on a bottomless pit :( \n" << endl;
		zeus.die();
		return false;
	}
		//wumpus case = RIP!
	else if(popMap.at(currRow).at(currCol).hasWumpus() == true){
		cout << "\n[RIP] Landed on a WUMPUS! *CHOMP CHOMP*\n" << endl;
		zeus.die();
		return false;
	}
	else{
		return false; 
			//survived! cool :) 
	}
}
//////////////////////////////////////////////////////////////////////////////
//	playGame()	 a loop that continuously asks for user input.
//				- exits if the player dies.. *see death rules at top* 
//				- exits if user types in X (exit game) 
//				
//////////////////////////////////////////////////////////////////////////////
void playGame(vector<vector<Room> >& popMap, Character& zeus){
	char step[5];	//the user's input 
	bool dead = false;	

	while(dead != true){	//while you're alive.. play. 
		int currRow = zeus.getRow();
		int currCol = zeus.getCol();
		
		//print out the user's current location before moving
		cout <<"****************************************************" << endl;
		cout << "User: " << zeus.getName();
		cout << " || Current Room: " <<
		popMap.at(currRow).at(currCol).getRoomNum();
		cout << " || Number of Arrows: " << zeus.getArrowCount() << endl;
		cout <<"****************************************************" << endl;
		//what's around me?
		hints(popMap, zeus);	
		if(observations(popMap, zeus) == true){	//did I die, have I been here?
			continue;
		}
		if(zeus.amiDead()){	//exit the loop if user quits or dies 
			printMsg("lost.txt");
			printMap(popMap, zeus);
			dead = true;
			return;		
		}
		//obtain the next step 
		cout <<"What's your next move?" << endl;
		cin >> step;	//feed the user's step	
		string mStep(step);	//converting to string for the 'MAP' otpion
		if (mStep == "Map" || mStep == "map" || mStep == "MAP"){
			printMap(popMap, zeus);
		}
		else if(isupper(step[0])== true){	//he shot an arrow 
			zeus.shootArrow();

			//did he run into a wall?
			if(stepChecker(step[0], zeus) == false){
				cout << "[WARNING] That's a wall!" << endl;
			}
			if (zeus.getArrowCount() == 0){	//did he run out of arrows?
				cout << "[WARNING] You're out of arrows! RIP" << endl;
				printMsg("lost.txt");
				printMap(popMap, zeus);	
				dead = true;
				return;
			}		
			//shoot in that direction
			else if(shoot(popMap, zeus, step[0]) == true){	//got him!
				printMsg("congrats.txt");
				printMap(popMap, zeus);
				dead = true;
				return;		
			}
			else{ //wumpus moved and the message already displayed
				//move wumpus
				cout << "[ALERT] You missed! Wumpus is moving now" << endl;
				moveWumpus(popMap);				
			}
		}
		else{	//if he didn't shoot an arrow and just moved... 
			if(stepChecker(step[0], zeus) == false){
				cout << "[WARNING] That's a wall!" << endl;
			}
			else{
				zeus.move(step[0]);	
				//always mark your footprints for that room
				popMap.at(currRow).at(currCol).setVisited();
			}
		}
		cout << endl;			
	}

}
//////////////////////////////////////////////////////////////////////////////
//	intro() -The opener of the game
//			- displays the welcome message
//			- takes in the user ID
//			- sets initial location of the character 
//			- begins the game after initial print of the map
//////////////////////////////////////////////////////////////////////////////
void intro(){
	//Welcome message
	string userID;	//user ID
	int initPosR = randNum();
	int initPosC = randNum();
	Character zeus;
	vector<vector<Room> > coolMap = makeMap();

	fillMap(coolMap);	//fill the skeleton map  w/ initial values of bats,etc.
	printMsg("wumpus.txt");
	cout << "Enter user ID: ";
	//cin >> userID;
	getline(cin, userID);
	//set Character's initial fields
	zeus.setName(userID);
	zeus.setLocation(initPosR, initPosC);
	cout << "\nHi " << userID << "!" << " Ready? Good luck!\n" << endl;	
	progressCheck(coolMap, zeus);	//always check for bats, pits and wumpus
	playGame(coolMap, zeus);	//begin playing the game 
	
}

int main(){
	srand(time(0));
	intro();	

};

