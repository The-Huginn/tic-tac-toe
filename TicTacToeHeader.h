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

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
	private:
		std::pair<int, int> grid;
		int to_win;
        std::vector<std::vector<PlayerClass::Player>> game;
        PlayerClass::Player current;

public slots:
        void callMe(int);

	public:
		/**
		 * @brief Constructor
		*/
        Q_INVOKABLE Game(QObject *parent = nullptr);

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
};

#endif // !TICTACTOEHEADER_H
