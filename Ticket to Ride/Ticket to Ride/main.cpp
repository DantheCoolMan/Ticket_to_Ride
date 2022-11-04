#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "player.h"
#include "constants.h"
#include "board.h"


int main(int argc, char** argv) {
    //Gets values from a CSV doc in order for the player to play it.
    std::vector<Board*> boardVec = parseBoard();

    std::vector <std::pair<int, Board*> > boardAdj[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        addEdge(boardAdj, boardVec[i]->getIntFrom(), boardVec[i]->getIntTo(), boardVec[i]);
    }
    int playerNum = playerCount();
    //setting up 
    std::vector<Player*> playerVec = playerVector(playerNum);
    while (playerSelect(boardAdj, playerVec, playerNum));
    std::vector<int> scores;
    for (int i = 0; i < playerNum; i++) {
        scores.push_back(playerVec[i]->getPoints());
    }
    int winner = std::max_element(scores.begin(), scores.end()) - scores.begin();
    printf(WINNER_PROMPT.c_str(), winner);

    //"freeing" data
    clearBoard(boardVec);
    clearPlayer(playerVec);
    clearGraph(boardAdj, BOARD_SIZE);

    return 0;
 
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
