#ifndef CONSTANTS_H
#define CONSTANDT_H
#include <string>

const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 4;
const std::string BEGINNING_PROMPT = "Please enter number of players between " + std::to_string(MIN_PLAYERS) + " and " + std::to_string(MAX_PLAYERS) + ", inclusive: ";
const std::string SECOND_PROMPT = "Invalid entry. " + BEGINNING_PROMPT;
const std::string WINNER_PROMPT = "Player %d is the winner!\n";
const std::string BOARD_PROMPT = "Where would you like to go?\n";
const std::string BOARD_OPTION = "\t(%d %d): From %s to %s: %d train(s) needed\n";
const std::string BOARD_EXPLAIN = "Enter the values like: \"0 7\", this leads from Calgary(0) to Vancouver(7): ";
const std::string PLAYER_INITIAL = "Player %d Train(s) %d\n";
const std::string PLAYER_NO_OPTION = "No more options.\n";
const std::string PLAYER_WRONG_INPUT = "You did this wrong. You don't deserve a turn.\n";
const std::string PLAYER_NO_PATH = "Path doesn't exist, try again: \n";
const std::string PLAYER_NO_TRAIN = "Not enough trains, try another path : \n";
#endif