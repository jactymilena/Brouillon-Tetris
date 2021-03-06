#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include "Piece.h"
#include "Player.h"

#define LIGNES 18
#define COLONNES 8

#define SPACE_BAR 32
#define KEY_UP 72
#define KEY_DOWN 40
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_W 87 // Hold
#define KEY_Q 81 // Tourner a gauche
#define KEY_E 69 // Tourner a droite

#define ADD 1
#define REMOVE 0
#define DOWN 0
#define SCORE 100

class Board {
public:
	Board();
	void startGame();
	void resetBoard();
	void printBoard();
	bool loadPiece(int num_piece);
	void print();
	void moveDownPiece();
	void movePiece(bool& nouvellePiece, int caseVoix);
	void pieceState(int state);
	bool verifMove(int direction);
	bool verifLigne(); 
	void enleverLigne(int i); 
	void printGameOver();
	void printHighScoreHistorique();

	//Menu Score
	void menuScore(); 
	void augmenterScore(int nbLigne);
	void augmenterLevel(); 
	void loadHighscore();
	void checkerScore();

	//Menu hold
	void changerPiece();
	void menuHold();

	//Menu Suivante
	void menuPieceSuivante();

	//Lecture FPGA
	//int lireFPGA();

	void clearConsole();

private:
	int cases[LIGNES][COLONNES];
	bool game_over;
	int level;
	Piece pieceHold;
	Piece piece;
	Piece pieceApres;
	int compteur;
	int difficulte;
	int min;
	int max;
	std::vector<Player> historique;
	Player player;
};
