//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//	Project Title:	Hunt the Wumpus
//	Class:			CSS 342
//	Professor:		John Chenault
//	Created By:		Ye Eun (Audrey) Chae
//	Platform:		MacOS Sierra 10.12.6
//	Environment:	VIM / g++ -std=c++11
//	Date Created:	November 30, 2017
//	Duration:		20 hours 
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "room.h"

Room::Room(){
	//TBD	
}

Room::~Room(){
	//TBD
}


//sets the room condition for having a wumpus to true or false 
void Room::setWumpus(bool state){
	wumpus = state;	
}

//sets the room condition for having a bat to true or false 
void Room::setBats(bool state){
	bat = state;
}

//sets the room condition for having a pit to be true
void Room::setPit(){
	pit = true;
}

//sets the room condition for visited to true 
void Room::setVisited(){
	visited = true;
}

//sets the room number
void Room::setRoomNum(int x){
	roomNum = x;
}

bool Room::hasWumpus(){
	return wumpus;
}
bool Room::hasBats(){
	return bat;
}

bool Room::hasPit(){
	return pit; 
}
bool Room::beenThere(){
	return visited;
}
int Room::getRoomNum(){
	return roomNum;
}
