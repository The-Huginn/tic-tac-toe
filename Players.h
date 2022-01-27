#pragma once
/**
* @file Players.h
* @brief This file contains enum for identifying players of Tic Tac Toe game
* @author Rastislav Budinsky
*/
#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>

class PlayerClass : public QObject
{
  Q_OBJECT

public:
    explicit PlayerClass(QObject *parent = nullptr): QObject(parent) {}

    enum Player {NONE, CROSS, NOUGHT};
    Q_ENUM(Player)
};

Q_DECLARE_METATYPE(PlayerClass::Player)

#endif // !PLAYERS_H
