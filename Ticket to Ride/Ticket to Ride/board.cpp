#include "board.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <unordered_set>

std::string Board::getFrom() { return from; }

std::string Board::getTo() { return to; }

int Board::getIntFrom() { return intFrom; }

int Board::getIntTo() { return intTo; }

int Board::getPoints() { return points; }

Board::Board() : intFrom(0), from(""), intTo(0), to(""), points(0) {}

Board::Board(const int& intFroma, const std::string& froma, const int& intToa, const std::string& toa, const int& pointsa) :
    intFrom(intFroma), from(froma), intTo(intToa), to(toa), points(pointsa) {}

std::vector<Board*> parseBoard() {
    std::vector<Board*> boardVec;
    std::ifstream input;
    //magic strings aren't good coding pratice, but probably won't do different versions.
    input.open("tr_board.csv");
    while (!input.eof()) {
        std::string line;
        //temp to not mutilate line.
        std::string temp;
        getline(input, line);
        temp = line;
        std::vector<std::string> hold;
        while (temp.find(',') != std::string::npos) {
            hold.push_back(temp.substr(0, temp.find(',')));
            temp.erase(0, temp.find(',') + 1);
        }
        Board* trip = new Board(std::stoi(hold[0]), hold[1], std::stoi(hold[2]), hold[3], std::stoi(hold[4]));
        boardVec.push_back(trip);
    }
    input.close();
    return boardVec;
}

void clearBoard(std::vector<Board*> boardVec) {
    for (int i = 0; i < boardVec.size(); i++) {
        //Another sacrificial lamb
        Board* lamb = boardVec[i];
        delete lamb;
    }
}

void addEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v, Board* wt) {
    adj[u].push_back(std::make_pair(v, wt));
    //Doing it for both so they both have the same edge
    adj[v].push_back(std::make_pair(u, wt));
}

int findEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v) {
    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i].first == v) {
            return adj[u][i].second->getPoints();
        }
    }
    return 0;
}

void deleteEdge(std::vector <std::pair<int, Board*> > adj[], const int& u, const int& v) {
    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i].first == v) {
            adj[u].erase(adj[u].begin() + i);
            break;
        }
    }
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i].first == u) {
            adj[v].erase(adj[v].begin() + i);
            break;
        }
    }
}

int smallestDistance(std::vector<std::pair<int, Board*> > adj[], const int& V) {
    //large number so almost anything on the first try will be smaller.
    int min = 100000000;
    for (int i = 0; i < V; i++) {
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            min = std::min(min, it->second->getPoints());
        }
    }
    return min;
}

void printGraph(std::vector<std::pair<int, Board*> > adj[], const int& V) {
    std::string v;
    std::string w;
    printf(BOARD_PROMPT.c_str());
    std::unordered_set<std::string> destSet;
    for (int i = 0; i < V; i++) {
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            v = it->second->getFrom();
            w = it->second->getTo();
            std::unordered_set<std::string>::const_iterator got = destSet.find(v + w);
            //in order to prevent duplicates and make it easier to read, I limited it to just one node instead of both sides.
            if (got == destSet.end()) {
                //inserts node so there's no longer a duplicate.
                destSet.insert(v + w);
                printf(BOARD_OPTION.c_str(), it->second->getIntFrom(), it->second->getIntTo(), v.c_str(), w.c_str(), it->second->getPoints());
            }
        }
    }
    printf(BOARD_EXPLAIN.c_str());
}

//doesn't deallocate the Board storage though.
void clearGraph(std::vector<std::pair<int, Board*> > adj[], const int& V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            adj[i].erase(adj[i].begin() + j);
        }
    }
}