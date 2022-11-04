#include "player.h"
#include <string>
#include <vector>
#include "constants.h"
#include <iostream>
#include "board.h"

Player::Player() {
	trains = TRAINS;
	points = POINTS;
}

int Player::getTrains() { return trains; }
int Player::getPoints() { return points; }

int playerCount() {
    std::string playerNum;
    printf(BEGINNING_PROMPT.c_str());
    getline(std::cin, playerNum);
    //checks if int and between min and max, if not, then it repeats
    while (!isNumber(playerNum) || 2 > std::stoi(playerNum) or 4 < std::stoi(playerNum)) {
        printf(SECOND_PROMPT.c_str());
        getline(std::cin, playerNum);
    }
    return std::stoi(playerNum);
}

void Player::subTrain(const int& traina) { trains -= traina; }

void Player::addPoints(const int& pointa) {
    switch(pointa) {
        case 3:
            points += 4;
            break;
        case 4:
            points += 7;
            break;
        case 5:
            points += 10;
            break;
        case 6:
            points += 15;
            break;
    default:
        points += pointa;
    }
}

bool isNumber(const std::string s){
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool playerSelect(std::vector<std::pair<int, Board*>> boardAdj[], const std::vector<Player*>& playerVec, const int& playerNum){
    //if one of the user is lower than 3, then it becomes the final round for all
    bool lastTurn = true;
    for (int i = 0; i < playerNum; i++) {
        //Prints out which turn and how many trains the player has left.
        printf(PLAYER_INITIAL.c_str(), i, playerVec[i]->getTrains());
        printGraph(boardAdj, BOARD_SIZE);
        std::string playerDest;
        //used in case the user slips, allows them to redo their turn
        bool onGoing = true;
        while (onGoing) {
            //if the user doesn't have enough trains for the remaining paths, skips.
            if (playerVec[i]->getTrains() < smallestDistance(boardAdj, BOARD_SIZE)) {
                printf(PLAYER_NO_OPTION.c_str());
                onGoing = false;
                break;
            }
            //User didn't input string properly
            getline(std::cin, playerDest);
            if (playerDest.find(' ') == std::string::npos) {
                printf(PLAYER_WRONG_INPUT.c_str());
                break;
            }
            //User puts in non int char.
            if (!isNumber(playerDest.substr(0, playerDest.find(' '))) || !isNumber(playerDest.substr(playerDest.find(' ') + 1, playerDest.size()))) {
                printf(PLAYER_WRONG_INPUT.c_str());
                break;
            }
            int from = stoi(playerDest.substr(0, playerDest.find(' ')));
            int to = stoi(playerDest.substr(playerDest.find(' '), playerDest.size()));
            //gets path that user selects and returns distance.
            int edgeVal = findEdge(boardAdj, from, to);
            //path doesn't exist.
            if (edgeVal == 0) {
                printf(PLAYER_NO_PATH.c_str());
            }
            //User doesn't have enough trains for path.
            else if (edgeVal > playerVec[i]->getTrains()) {
                printf(PLAYER_NO_TRAIN.c_str());
            }
            //adds points to player and deletets the edge, ends loop.
            else {
                playerVec[i]->subTrain(edgeVal);
                playerVec[i]->addPoints(edgeVal);
                deleteEdge(boardAdj, from, to);
                onGoing = false;
            }
        }
        if (playerVec[i]->getTrains() <= 2) {
            lastTurn = false;
        }
    }
    return lastTurn;
}

std::vector<Player*> playerVector(const int& playerNum) {
    std::vector<Player*> playerVec;
    for (int i = 0; i < playerNum; i++) {
        Player* playerItem = new Player();
        playerVec.push_back(playerItem);
    }
    return playerVec;
}

void clearPlayer(const std::vector<Player*>& playerVec) {
    for (int i = 0; i < playerVec.size(); i++) {
        //sacrifial lamb
        Player* lamb = playerVec[i];
        delete lamb;
    }
}