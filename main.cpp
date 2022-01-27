/**
* @file main.cpp
* @brief This file contains CLI version of Tic Tac Toe
* @author Rastislav Budinsky
*/
#include "TicTacToeHeader.h"

#include <iostream>
#include <string>
#include <sstream>

void PrintTable(Game& tictactoe)
{
	for (int i = 0; i < tictactoe.GetWidth() * 2 + 1; i++)
		std::cout << "-";
	std::cout << std::endl;

	for (int i = 0; i < tictactoe.GetHeight(); i++)
	{
		for (int j = 0; j < tictactoe.GetWidth(); j++)
		{
			std::cout << "|";
			switch (tictactoe.GetSquare(i, j))
			{
			case CROSS:
				std::cout << "X";
				break;

			case NOUGHT:
				std::cout << "O";
				break;

			default:
				std::cout << " ";
				break;
			}
		}
		std::cout << "|\n";
	}

	for (int i = 0; i < tictactoe.GetWidth() * 2 + 1; i++)
		std::cout << "-";
	std::cout << std::endl;
}

int main()
{
	Game tictactoe;
	bool playing = true;
	while (playing)
	{
		// Clear console
		system("cls");

		// Print commands
		std::cout << "Welcome to Tic Tac Toe CLI version!\nTo change grid width use command \"w *number greater than 3*\"\n";
		std::cout << "To change grid height use command \"h *number greater than 3*\"\nTo change number of connected squares use command \"s *number greater than minimal grid size*\"\n";
		std::cout << "To start a new game use command \"n\"\nTo play write coordinates of your move like \"*y coordinate* *x coordinate*\" starting from 1,1 top left\n";
		std::cout << "To exit use command \"t\"\n";

		// Print the table
		PrintTable(tictactoe);

		// Command handling
		std::string line;
		std::getline(std::cin, line);

		// Idea for spliting words from: https://java2blog.com/split-string-space-cpp/
		std::stringstream ss(line);

		std::string word; std::vector<std::string> words;
		while (std::getline(ss, word, ' '))
			words.push_back(word);

		if (words.size() == 1 && words.back().compare("n") == 0)
			tictactoe.NewGame();

		if (words.size() == 2)
		{
			// We test if first string is number
			if (std::atoi(words[0].c_str()) == 0)
			{
				switch (words[0][0])
				{
				case 'w':
					tictactoe.ChangeWidth(std::atoi(words[1].c_str()));
					break;

				case 'h':
					tictactoe.ChangeHeight(std::atoi(words[1].c_str()));
					break;

				case 's':
					tictactoe.ChangeMinimum(std::atoi(words[1].c_str()));
					break;

				case 'n':
					tictactoe.NewGame();
					break;

				case 't':
					playing = false;
					break;

				default:
					break;
				}
			}
			else
			{
				if (std::atoi(words[1].c_str()) != 0)
				{
					Player winner = tictactoe.PlayRound(std::atoi(words[0].c_str()) - 1, std::atoi(words[1].c_str()) - 1);
					if (winner != NONE)
					{
						system("cls");
						PrintTable(tictactoe);

						std::cout << "Winner is " << (winner == CROSS ? "CROSS" : "NOUGHT") << "!\n";
						std::cout << "For restart Press \"r\". To end Press \"t\"\n";
						while (std::cin >> line)
						{
							if (line.compare("r") == 0)
							{
								tictactoe.NewGame();
								break;
							}
							if (line.compare("t") == 0)
							{
								playing = false;
								break;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}