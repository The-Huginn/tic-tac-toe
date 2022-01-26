#pragma once
/**
* @file TicTacToeHeader.h
* @brief This file contains interface for interacting and playing the game Tic Tac Toe.
* Game is implemented using Singleton, new game automatically destroys any previous ones.
* Default game size is 3x3 and minimum connected squares is 3.
* @author Rastislav Budinsky
*/
#include "Players.h"

/**
* @brief Creates new game of size and squares defined previously, default size is 3x3 and minimum connected squares is 3.
*/
void NewGame();

/**
* @brief Changes the height of the grid for next games.
* @param height New height,
* @return True upon success otherwise called with incorrect value,
*/
bool ChangeHeight(int height);

/**
* @brief Changes the width of the grid for next games.
* @param width New width.
* @return True upon success otherwise called with incorrect value.
*/
bool ChangeWidth(int width);

/**
* @brief Changes the minimum required connected squares.
* @param minimum New minimum.
* @return True upon success otherwise called with incorrect value.
*/
bool ChangeMinimum(int minimum);

/**
* @return The minimum height.
*/
int MinimumHeight();

/**
* @return The minimum width.
*/
int MinimumWidth();

/**
* @return The minimum required connected squares.
*/
int MinimumSquares();

/**
* @return Player, who is playing next round.
*/
Player NextPlayer();

/**
* @brief Proceeds one round in the Player, who was playing that round.
* @param column The column of the square.
* @param row The row of the square.
* @return Enum value of the Player, who won, otherwise NONE.
*/
Player PlayRound(int column, int row);