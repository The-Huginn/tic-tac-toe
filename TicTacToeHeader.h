#pragma once
/**
* @file TicTacToeHeader.h
* @brief This file contains interface for interacting and playing the game Tic Tac Toe.
* Game is implemented using Singleton, new game automatically destroys any previous ones.
* Default game size is 3x3 and minimum connected squares is 3.
* @author Rastislav Budinsky
*/
#ifndef TICTACTOEHEADER_H
#define TICTACTOEHEADER_H

#include "Players.h"
#include <utility>
#include <vector>

class Game
{

	private:
        #define STATS_SIZE 3

		std::pair<int, int> grid;
        int to_win_next;
		int to_win;
        int stats[STATS_SIZE];
        std::vector<std::vector<Player>> game;
        Player current;

	public:
		/**
		 * @brief Constructor
		*/
		Game(); 

		/**
		* @brief Creates new game of size and squares defined previously, default size is 3x3 and minimum connected squares is 3.
		*/
        void newGame();

		/**
		* @brief Changes the height of the grid for next games.
		* @param height New height,
		* @return True upon success otherwise called with incorrect value,
		*/
        bool changeHeight(int height);

		/**
		* @brief Changes the width of the grid for next games.
		* @param width New width.
		* @return True upon success otherwise called with incorrect value.
		*/
        bool changeWidth(int width);

		/**
		* @brief Changes the minimum required connected squares.
		* @param minimum New minimum.
		* @return True upon success otherwise called with incorrect value.
		*/
        bool changeMinimum(int minimum);

		/**
		* @return The minimum height.
		*/
        int minimumHeight();

		/**
		* @return The minimum width.
		*/
        int minimumWidth();

		/**
		* @return The minimum required connected squares.
		*/
        int minimumSquares();

        /**
         * @return Current Width or newly set Width if changed.
        */
        int nextWidth();

        /**
         * @return Current Height or newly set Height if changed.
        */
        int nextHeight();

        /**
         * @return Current Minimum or newly set Minimum if changed.
        */
        int nextMinimum();

		/**
		 * @return Current Width.
		*/
        int getWidth();

		/**
		 * @return Current Height.
		*/
        int getHeight();

		/**
        * @return Int value of the Player, who is playing next round.
		*/
        int nextPlayer();

		/**
		* @brief Proceeds one round in the Player, who was playing that round.
		* @param row The row of the square.
		* @param column The column of the square.
        * @return Int value of the Player, who won, otherwise NONE.
		*/
        int playRound(int row, int column);

		/**
		 * @param row The row of the square.
		 * @param column The column of the square.
         * @return Int value of the player occupying the square, if empty then NONE.
		*/
        int getSquare(int row, int column);

        /**
         * @return The number of wins by Cross
         */
        int getCrossWins();

        /**
         * @return The number of wins by Nought
         */
        int getNoughtWins();

        /**
         * @return The number of draws
         */
        int getDraws();
};

#endif // !TICTACTOEHEADER_H
