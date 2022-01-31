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
	for (int i = 0; i < tictactoe.getWidth() * 2 + 1; i++)
		std::cout << "-";
	std::cout << std::endl;

	for (int i = 0; i < tictactoe.getHeight(); i++)
	{
		for (int j = 0; j < tictactoe.getWidth(); j++)
		{
			std::cout << "|";
			switch (tictactoe.getSquare(i, j))
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

	for (int i = 0; i < tictactoe.getWidth() * 2 + 1; i++)
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

		if (words.size() == 1)
		{
			switch (words.back()[0])
			{
			case 'n':
				tictactoe.newGame();
				break;

			case 't':
				playing = false;
				break;

			default:
				break;
			}
		}
		if (words.size() == 2)
		{
			// We test if first string is number
			if (std::atoi(words[0].c_str()) == 0)
			{
				switch (words[0][0])
				{
				case 'w':
					tictactoe.changeWidth(std::atoi(words[1].c_str()));
					break;

				case 'h':
					tictactoe.changeHeight(std::atoi(words[1].c_str()));
					break;

				case 's':
					tictactoe.changeMinimum(std::atoi(words[1].c_str()));
					break;

				case 'n':
					tictactoe.newGame();
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
					Player winner = (Player) tictactoe.playRound(std::atoi(words[0].c_str()) - 1, std::atoi(words[1].c_str()) - 1);
					if (winner != NONE)
					{
						system("cls");
						PrintTable(tictactoe);

						std::cout << "Winner is " << (winner == CROSS ? "CROSS" : "NOUGHT") << "!\n";
						std::cout << "For restart use command \"r\". To end use command \"t\"\n";
						while (std::cin >> line)
						{
							if (line.compare("r") == 0)
							{
								tictactoe.newGame();
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