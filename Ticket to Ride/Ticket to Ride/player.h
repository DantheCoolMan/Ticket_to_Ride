#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "board.h"

//Trais is 45, but I haven't imported all edges in the game yet.
const int TRAINS = 10;
const int POINTS = 0;
/**
 * This class is used to hold player data such as Trains and Points.
 * In the future, this will hold 3 destination cards and an adjacency list
 * to determine longest path(NP, sadly) or if the user completed a path from the two edges.
 * 
 * This class counts the amount of players and is used to play the majority of the game.
 * 
 *
 */
class Player {
private:
	int trains;
	int points;

public:
	Player();

	int getTrains();

	int getPoints();

	//This method subtracts from trains.
	void subTrain(const int& traina);

	/**
	 *This method adds to point values based on how long the track was.
	 * Track:Points
	 * 1:1
	 * 2:2
	 * 3:4
	 * 4:7
	 * 5:10
	 * 6:15
	 */
	void addPoints(const int& pointa);
};


 //Takes in str from stdin that's between min_players and max_players, returns int of that str.
int playerCount();

//Checks if str is int.
bool isNumber(const std::string s);

/**
 * Goes through the whole party, shows user the board, allows them to choose an edge, deletes the edge from the board,
 * subtracts train from player, adds points. 
 */
bool playerSelect(std::vector <std::pair<int, Board*> > boardAdj[], const std::vector<Player*>& playerVec, const int& playerNum);

std::vector<Player*> playerVector(const int& playerNum);

void clearPlayer(const std::vector<Player*>& playerVec);

#endif