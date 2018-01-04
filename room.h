//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//	Project Title:	Hunt the Wumpus
//	Professor:		John Chenault
//	Created by:		Ye Eun (Audrey) Chae
//	Platform:		MacOS Sierra 10.12.6
//	Environment:	VIM / g++ -std=c++11
//	Date created:	November 30, 2017
//	Duration:		20 hours
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef ROOM_H
#define ROOM_H

class Room{

private:
	int roomNum;
	bool wumpus = false;
	bool bat = false;
	bool pit = false;
	bool visited = false;

public:
	Room();
	virtual ~Room();

	void setWumpus(bool state);
	void setBats(bool state);
	void setPit();
	void setVisited();
	void setRoomNum(int x);


	bool hasWumpus();
	bool hasBats();
	bool hasPit();
	bool beenThere();
	int getRoomNum();
};

#endif 
