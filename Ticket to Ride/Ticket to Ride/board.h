#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

//Size is determined by number of edeges in tr_board
const int BOARD_SIZE = 12;
/**
 * Used to store all edges on the board.
 * Still need to upload the rest.
 * 
 * Almost the adjacency list class, just for the time being.
 */
class Board {

private:
    std::string from;
    int intFrom;
    std::string to;
    int intTo;
    int points;

public:
    Board();
    Board(const int& intFroma, const std::string& froma, const int& intToa, const std::string& toa, const int& pointsa);
    std::string getFrom();
    std::string getTo();
    int getIntFrom();
    int getIntTo();
    int getPoints();

};

/**
 * Might try doing this another way. I could try to do boost, an adjacency list of nodes,
 * or even an adjacency graph. Didn't work out like what I wanted to.
 */


//Parses from a csv file and fills a vector.
std::vector<Board*> parseBoard();
void clearBoard(std::vector<Board*> boardVec);

/**
 * Gets a begining node and ending node along with a weight and creates a undirected edge between them.
 * Needs adj though, I'll figure out something else to make it easier to read later though.
 */
void addEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v, Board* wt);

//Deletes edge form adj, but it doesn't clear the memory of the item inside.
void deleteEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v);

//Prints graph of avaliable edges along with trains needed to traverse it. 
void printGraph(std::vector<std::pair<int, Board*> > adj[], const int& V);

//Just clears out adj, doesn't delete Boards*
void clearGraph(std::vector<std::pair<int, Board*> > adj[], const int& V);

//Returns weight of edge if exist, if not, then returns 0.
int findEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v);

/**
 * Returns the lowest amount of trains needed to fulfil an edge.
 * Used to make sure that the user has enough trains before starting the turn.
 */
int smallestDistance(std::vector<std::pair<int, Board*> > adj[], const int& V);
#endif