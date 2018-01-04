//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//	Project Title:	Hunt the Wumpus
//	Class:			CSS 342
//	Professor:		John Chenault
//	Created by;		Ye Eun (Audrey) Chae
//	Platform:		MacOS Sierroa 10.12.6
//	Environment:	VIM / g++ -std=c++11
//	Date Created;	November 30, 2017
//	Duration:		20 hours
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////
//		class Character - a friend of Location. It's us!
//////////////////////////////////////////////////////////////////////////////
class Character{

private:
	std::string name;
	bool dead;
	int arrowCount;
	int yRow;
	int xCol;

public:
	Character();
	virtual ~Character();
	void setName(std::string namey);
	void setLocation(int row, int col);
	bool shootArrow();	//returns false if the arrow count is at 0
	void die();
	
	std::string getName();
	int getArrowCount();
	int getRow();
	int getCol();
	bool amiDead();
	
	void move(char step);

};


#endif

