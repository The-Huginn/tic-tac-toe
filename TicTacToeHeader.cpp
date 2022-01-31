/**
* @file TicTacToeHeader.cpp
* @brief This file implements the interface for playing the game Tic Tac Toe
* @author Rastislav Budinsky
*/
#include "TicTacToeHeader.h"
#include <algorithm>

Game::Game()
{
    current = CROSS;
	grid = { 3, 3 };
    to_win_next = 3;
	to_win = 3;
    std::fill_n(stats, STATS_SIZE, 0);
    game.resize(grid.first, std::vector<Player>(grid.second, Player::NONE));
}

void Game::newGame()
{
    to_win = to_win_next;
    current = CROSS;
    game.clear();
    game.resize(grid.first, std::vector<Player>(grid.second, NONE));
}

bool Game::changeHeight(int height)
{
    if (height < minimumHeight())
		return false;

	grid.first = height;

    // We have to change in case we lowered the size
    to_win_next = (to_win_next > grid.first && to_win_next > grid.second) ? std::max(grid.first, grid.second) : to_win_next;

	return true;
}

bool Game::changeWidth(int width)
{
    if (width < minimumWidth())
		return false;

	grid.second = width;
    // We have to change in case we lowered the size
    to_win_next = (to_win_next > grid.first && to_win_next > grid.second) ? std::max(grid.first, grid.second) : to_win_next;

	return true;
}

bool Game::changeMinimum(int minimum)
{
    if (minimum > grid.first && minimum > grid.second)
		return false;

    to_win_next = std::max(minimum, 3);   // We want at least 3 connected, otherwise not a game
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
    return grid.second;
}

int Game::nextHeight()
{
    return grid.first;
}

int Game::nextMinimum()
{
    return to_win_next;
}

int Game::getWidth()
{
	return game[0].size();
}

int Game::getHeight()
{
	return game.size();
}

int Game::nextPlayer()
{
	return current;
}

int Game::playRound(int row, int column)
{
	if (row < 0 || row >= game.size() || column < 0 || column >= game[0].size())
        return NONE;

    if (game[row][column] != NONE)
        return NONE;

    game[row][column] = current;

	// logic is primitive and no optimizations are done, for demonstration purposes only
	bool won = false;
	for (int y = 0; y < game.size(); y++)
	{
        for (int x = 0; x < game[y].size(); x++)
		{
            // check horizontal
            if (x <= (int)game[y].size() - to_win)
            {
                won = true;
                for (int i = 1; i < to_win; i++)
                    if (game[y][x + i] != game[y][x + i - 1] || game[y][x + i] == NONE)
                        won = false;
                if (won)
                    break;
            }

            // check vertical
            if (y <= (int)game.size() - to_win)
            {
                won = true;
                for (int i = 1; i < to_win; i++)
                    if (game[y + i][x] != game[y + i - 1][x] || game[y + i][x] == NONE)
                        won = false;
                if (won)
                    break;
            }

            // check main diagonal
            if (y <= (int)game.size() - to_win && x <= (int)game[y].size() - to_win)
            {
                won = true;
                for (int i = 1; i < to_win; i++)
                    if (game[y + i][x + i] != game[y + i - 1][x + i - 1] || game[y + i][x + i] == NONE)
                        won = false;
                if (won)
                    break;
            }

            // check anti-diagonal
            if (y >= (int)to_win - 1 && x <= (int)game[y].size() - to_win)
            {
                won = true;
                for (int i = 1; i < to_win; i++)
                    if (game[y - i][x + i] != game[y - i + 1][x + i - 1] || game[y - i][x + i] == NONE)
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
        for (int y = 0; y < game.size(); y++)
            for (int x = 0; x < game[y].size(); x++)
                if (game[y][x] == NONE)
                    won = false;
        if (won)
            current = DRAW;
    }


	// we dont switch to the next player
	if (won)
    {
        stats[current - 1]++;
		return current;
    }

    current = current == CROSS ? NOUGHT : CROSS;

    return NONE;
}

int Game::getSquare(int row, int column)
{
	if (row < 0 || row >= game.size() || column < 0 || column >= game[0].size())
        return NONE;

	return game[row][column];
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
