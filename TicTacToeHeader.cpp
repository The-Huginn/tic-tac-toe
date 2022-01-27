/**
* @file TicTacToeHeader.cpp
* @brief This file implements the interface for playing the game Tic Tac Toe
* @author Rastislav Budinsky
*/
#include "TicTacToeHeader.h"

Game::Game()
{
	this->current = CROSS;
	this->grid = { 3, 3 };
	this->to_win = 3;
	this->game.resize(this->grid.second, std::vector<Player>(this->grid.first, NONE));
}

void Game::NewGame()
{
	this->current = CROSS;
	this->game.resize(this->grid.second, std::vector<Player>(this->grid.first, NONE));
}

bool Game::ChangeHeight(int height)
{
	if (height < MinimumHeight())
		return false;

	this->grid.first = height;
	return true;
}

bool Game::ChangeWidth(int width)
{
	if (width < MinimumWidth())
		return false;

	this->grid.second = width;
	return true;
}

bool Game::ChangeMinimum(int minimum)
{
	if (minimum < this->grid.first && minimum < this->grid.second)
		return false;

	this->to_win = minimum;
	return true;
}

int Game::MinimumHeight()
{
	// Magic constant for height
	return 3;
}

int Game::MinimumWidth()
{
	// Magic constant for width
	return 3;
}

int Game::MinimumSquares()
{
	return std::min(MinimumHeight(), MinimumWidth());
}

Player Game::NextPlayer()
{
	return this->current;
}

Player Game::PlayRound(int row, int column)
{
	this->game[row][column] = this->current;

	// logic is primitive and no optimizations are done, for demonstration purposes only
	bool won = false;
	for (int y = 0; y < this->game.size(); y++)
	{
		for (int x = 0; x < this->game.size(); x++)
		{
			// check horizontal
			if (x <= this->game[y].size() - this->to_win)
			{
				won = true;
				for (int i = 1; i < this->to_win; i++)
					if (this->game[y][x + i] != this->game[y][x + i - 1])
						won = false;
				if (won)
					break;
			}

			// check vertical
			if (y <= this->game.size() - this->to_win)
			{
				won = true;
				for (int i = 1; i < this->to_win; i++)
					if (this->game[y + i][x] != this->game[y + i - 1][x])
						won = false;
				if (won)
					break;
			}

			// check main diagonal
			if (y >= this->to_win - 1 && x >= this->to_win - 1)
			{
				won = true;
				for (int i = 1; i < this->to_win; i++)
					if (this->game[y - i][x - i] != this->game[y - i + 1][x - i + 1])
						won = false;
				if (won)
					break;
			}

			// check anti-diagonal
			if (y <= this->game.size() - this->to_win && x <= this->game[y].size() - this->to_win)
			{
				won = true;
				for (int i = 1; i < this->to_win; i++)
					if (this->game[y + i][x + i] != this->game[y + i - 1][x + i - 1])
						won = false;
				if (won)
					break;
			}
		}
		if (won)
			break;
	}

	// we dont switch to the next player
	if (won)
		return this->current;

	this->current = this->current == CROSS ? NOUGHT : CROSS;

	return NONE;
}