/**
* @file TicTacToeHeader.cpp
* @brief This file implements the interface for playing the game Tic Tac Toe
* @author Rastislav Budinsky
*/
#include "TicTacToeHeader.h"
#include <algorithm>

#ifndef CLI
#include <QDebug>
#endif

#ifndef CLI
Game::Game(QObject* parent) : QObject(parent)
#else
Game::Game()
#endif
{
    this->current = PlayerClass::Player::CROSS;
	this->grid = { 3, 3 };
    this->to_win_next = 3;
	this->to_win = 3;
    std::fill_n(stats, STATS_SIZE, 0);
    this->game.resize(this->grid.first, std::vector<PlayerClass::Player>(this->grid.second, PlayerClass::Player::NONE));
}

void Game::newGame()
{
    this->to_win = this->to_win_next;
    this->current = PlayerClass::Player::CROSS;
    this->game.clear();
    this->game.resize(this->grid.first, std::vector<PlayerClass::Player>(this->grid.second, PlayerClass::Player::NONE));
}

bool Game::changeHeight(int height)
{
    if (height < minimumHeight())
		return false;

	this->grid.first = height;
    // We have to change in case we lowered the size
    this->to_win_next = (this->to_win_next > this->grid.first && this->to_win_next > this->grid.second) ? std::max(this->grid.first, this->grid.second) : this->to_win_next;

	return true;
}

bool Game::changeWidth(int width)
{
    if (width < minimumWidth())
		return false;

	this->grid.second = width;
    // We have to change in case we lowered the size
    this->to_win_next = (this->to_win_next > this->grid.first && this->to_win_next > this->grid.second) ? std::max(this->grid.first, this->grid.second) : this->to_win_next;

	return true;
}

bool Game::changeMinimum(int minimum)
{
    if (minimum > this->grid.first && minimum > this->grid.second)
		return false;

    this->to_win_next = std::max(minimum, 3);   // We want at least 3 connected, otherwise not a game
	return true;
}

int Game::minimumHeight()
{
	// Magic constant for height
	return 3;
}

int Game::minimumWidth()
{
	// Magic constant for width
	return 3;
}

int Game::minimumSquares()
{
    return std::min(minimumHeight(), minimumWidth());
}

int Game::nextWidth()
{
    return this->grid.second;
}

int Game::nextHeight()
{
    return this->grid.first;
}

int Game::nextMinimum()
{
    return this->to_win_next;
}

int Game::getWidth()
{
	return this->game[0].size();
}

int Game::getHeight()
{
	return this->game.size();
}

int Game::nextPlayer()
{
	return this->current;
}

int Game::playRound(int row, int column)
{
	if (row < 0 || row >= this->game.size() || column < 0 || column >= this->game[0].size())
        return PlayerClass::Player::NONE;

    if (this->game[row][column] != PlayerClass::Player::NONE)
        return PlayerClass::Player::NONE;

    this->game[row][column] = this->current;

	// logic is primitive and no optimizations are done, for demonstration purposes only
	bool won = false;
	for (int y = 0; y < this->game.size(); y++)
	{
        for (int x = 0; x < this->game[y].size(); x++)
		{
            // check horizontal
            if (x <= (int)this->game[y].size() - this->to_win)
            {
                won = true;
                for (int i = 1; i < this->to_win; i++)
                    if (this->game[y][x + i] != this->game[y][x + i - 1] || this->game[y][x + i] == PlayerClass::Player::NONE)
                        won = false;
                if (won)
                    break;
            }

            // check vertical
            if (y <= (int)this->game.size() - this->to_win)
            {
                won = true;
                for (int i = 1; i < this->to_win; i++)
                    if (this->game[y + i][x] != this->game[y + i - 1][x] || this->game[y + i][x] == PlayerClass::Player::NONE)
                        won = false;
                if (won)
                    break;
            }

            // check main diagonal
            if (y <= (int)this->game.size() - this->to_win && x <= (int)this->game[y].size() - this->to_win)
            {
                won = true;
                for (int i = 1; i < this->to_win; i++)
                    if (this->game[y + i][x + i] != this->game[y + i - 1][x + i - 1] || this->game[y + i][x + i] == PlayerClass::Player::NONE)
                        won = false;
                if (won)
                    break;
            }

            // check anti-diagonal
            if (y >= (int)this->to_win - 1 && x <= (int)this->game[y].size() - this->to_win)
            {
                won = true;
                for (int i = 1; i < this->to_win; i++)
                    if (this->game[y - i][x + i] != this->game[y - i + 1][x + i - 1] || this->game[y - i][x + i] == PlayerClass::Player::NONE)
                        won = false;
                if (won)
                    break;
            }
		}
		if (won)
			break;
	}

    // no winner but may be a draw
    if (!won)
    {
        won = true;
        for (int y = 0; y < this->game.size(); y++)
            for (int x = 0; x < this->game[y].size(); x++)
                if (this->game[y][x] == PlayerClass::Player::NONE)
                    won = false;
        if (won)
            this->current = PlayerClass::Player::DRAW;
    }


	// we dont switch to the next player
	if (won)
    {
        stats[this->current - 1]++;
		return this->current;
    }

    this->current = this->current == PlayerClass::Player::CROSS ? PlayerClass::Player::NOUGHT : PlayerClass::Player::CROSS;

    return PlayerClass::Player::NONE;
}

int Game::getSquare(int row, int column)
{
	if (row < 0 || row >= this->game.size() || column < 0 || column >= this->game[0].size())
        return PlayerClass::Player::NONE;

	return this->game[row][column];
}

int Game::getCrossWins()
{
    return stats[0];
}

int Game::getNoughtWins()
{
    return stats[1];
}

int Game::getDraws()
{
    return stats[2];
}
