#pragma once
/**
* @file Players.h
* @brief This file contains enum for identifying players of Tic Tac Toe game
* @author Rastislav Budinsky
*/
#ifndef PLAYERS_H
#define PLAYERS_H

#define CLI

// Based on macro we change some syntax
#ifndef CLI 
#include <QObject>
class PlayerClass : public QObject
{
    Q_OBJECT

public:
    explicit PlayerClass(QObject* parent = nullptr) : QObject(parent) {}
    enum Player { NONE, CROSS, NOUGHT, DRAW };
    Q_ENUM(Player)
};
#else
class PlayerClass
{
public:
    explicit PlayerClass() {}
    enum Player { NONE, CROSS, NOUGHT, DRAW };
};
#endif

#endif // !PLAYERS_H
