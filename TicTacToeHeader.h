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

// We redefine macros if we are in CLI version
#ifndef CLI
#include <QObject>
#else
#undef Q_INVOKABLE
#define Q_INVOKABLE
#undef Q_OBJECT
#define Q_OBJECT
#endif

class Game
#ifndef CLI
	: public QObject
#endif
{
    Q_OBJECT

	private:
        #define STATS_SIZE 3

		std::pair<int, int> grid;
        int to_win_next;
		int to_win;
        int stats[STATS_SIZE];
        std::vector<std::vector<PlayerClass::Player>> game;
        PlayerClass::Player current;

	public:
		/**
		 * @brief Constructor
		*/
#ifndef CLI
		Q_INVOKABLE Game(QObject* parent = nullptr);
#else 
		Game();
#endif  

		/**
		* @brief Creates new game of size and squares defined previously, default size is 3x3 and minimum connected squares is 3.
		*/
        Q_INVOKABLE void newGame();

		/**
		* @brief Changes the height of the grid for next games.
		* @param height New height,
		* @return True upon success otherwise called with incorrect value,
		*/
        Q_INVOKABLE bool changeHeight(int height);

		/**
		* @brief Changes the width of the grid for next games.
		* @param width New width.
		* @return True upon success otherwise called with incorrect value.
		*/
        Q_INVOKABLE bool changeWidth(int width);

		/**
		* @brief Changes the minimum required connected squares.
		* @param minimum New minimum.
		* @return True upon success otherwise called with incorrect value.
		*/
        Q_INVOKABLE bool changeMinimum(int minimum);

		/**
		* @return The minimum height.
		*/
        Q_INVOKABLE int minimumHeight();

		/**
		* @return The minimum width.
		*/
        Q_INVOKABLE int minimumWidth();

		/**
		* @return The minimum required connected squares.
		*/
        Q_INVOKABLE int minimumSquares();

        /**
         * @return Current Width or newly set Width if changed.
        */
        Q_INVOKABLE int nextWidth();

        /**
         * @return Current Height or newly set Height if changed.
        */
        Q_INVOKABLE int nextHeight();

        /**
         * @return Current Minimum or newly set Minimum if changed.
        */
        Q_INVOKABLE int nextMinimum();

		/**
		 * @return Current Width.
		*/
        Q_INVOKABLE int getWidth();

		/**
		 * @return Current Height.
		*/
        Q_INVOKABLE int getHeight();

		/**
        * @return Int value of the Player, who is playing next round.
		*/
        Q_INVOKABLE int nextPlayer();

		/**
		* @brief Proceeds one round in the Player, who was playing that round.
		* @param row The row of the square.
		* @param column The column of the square.
        * @return Int value of the Player, who won, otherwise NONE.
		*/
        Q_INVOKABLE int playRound(int row, int column);

		/**
		 * @param row The row of the square.
		 * @param column The column of the square.
         * @return Int value of the player occupying the square, if empty then NONE.
		*/
        Q_INVOKABLE int getSquare(int row, int column);

        /**
         * @return The number of wins by Cross
         */
        Q_INVOKABLE int getCrossWins();

        /**
         * @return The number of wins by Nought
         */
        Q_INVOKABLE int getNoughtWins();

        /**
         * @return The number of draws
         */
        Q_INVOKABLE int getDraws();
};

#endif // !TICTACTOEHEADER_H
