﻿#include "Board.h"
#include <chrono>
#include <thread>
#include<math.h>
using namespace std::chrono_literals;

Board::Board() {
	resetBoard();
	score = 0;
	game_over = false;
	level = 0;
	difficulte = 1;
	compteur = 0;
}

void Board::startGame() {
	srand((int)time(0));
	int cpt = 0;
	pieceHold.loadPiece(7);
	pieceApres.loadPiece(rand() % 6);

	while (game_over == false) { // Pour tester les pieces une apres l'autre
		if (loadPiece(pieceApres.getNumPiece())) {
			pieceApres.loadPiece(rand() % 6);
			print();
			moveDownPiece();
		}
	}
	std::cout << "********* GAME OVER ******** \n";
}

bool Board::loadPiece(int num_piece) {
	piece.loadPiece(num_piece);

	for (int i = 0; i < 4; i++) { // verif si possible de placer pieces a pos initiale 
		if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] == 1) {
			game_over = true; // jeu termine
			return false; // pas possible de loader la piece 
		}
	}
	return true;
}

void Board::movePiece(bool &nouvellePiece) { // bouger gauche, droite, bas, tourner

	if (GetAsyncKeyState(KEY_RIGHT) && verifMove(RIGHT))
	{
		piece.move(RIGHT);
	}

	if (GetAsyncKeyState(KEY_LEFT) && verifMove(LEFT))
	{
		piece.move(LEFT);
	}
	if (GetAsyncKeyState(KEY_DOWN) && verifMove(DOWN))
	{
		piece.goDown();
	}
	/*
	if (GetAsyncKeyState(SPACE_BAR) )
	{
		//Code à Simon pour tourner
	}
	*/
	if(GetAsyncKeyState(wKey)&& nouvellePiece == true)
	{
		nouvellePiece = false;
		changerPiece();
	}
}

bool Board::verifMove(int direction) {
	switch (direction) {
	case RIGHT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne + 1] == 1 ||
				piece.getCarre(i).colonne + 1 == COLONNES) {
				return false;
			}
		}
		break;
	case LEFT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne - 1] == 1 ||
				piece.getCarre(i).colonne - 1 < 0) {
				return false;
			}
		}
		break;

	case DOWN:
		for (int i = 0; i < 4; i++) {
			if (piece.getCarre(i).ligne + 1 != LIGNES) {
				if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == 1) { // la piece ne peut plus descendre 
					return false;
				}
			}
			else { // la piece est rendu a la derniere ligne 
				return false;
			}
		}
		break;
	}
	return true;
}

void Board::moveDownPiece() {
	bool possibleBas = true;
	bool nouvellePiece = true;

	do {
		pieceState(REMOVE);

		if (_kbhit()) movePiece(nouvellePiece);
		
		if (possibleBas = verifMove(DOWN) && (compteur == difficulte)) {
			piece.goDown();
			// si une touche a ete pressee
			compteur = 0;
		}

		print();
	} while (possibleBas == true);

	nouvellePiece = true;

	compteur = 0;
}

void Board::resetBoard() {
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j] = 0;
		}
	}
}

void Board::pieceState(int state) {
	for (int i = 0; i < 4; i++) {
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] = state;
	}
}

/*
author: Ryan Pickelsimer
source: https://github.com/rpickelsimer/Tetris/blob/master/Tetris.cpp
Date: 2021-03-02
Description: Utilisation de sa fonction clear() servant à effacer l'écran.
			 Cela offre une alternative à la fonction system("cls") montrant
			 certaines lacunes au niveau de l'efficacité tant qu'au fait d'effacer
			 plusieurs lignes.
*/
void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void Board::print() {
	pieceState(ADD);
	clear();//system("CLS");
	printBoard();
	std::this_thread::sleep_for(50ms);
	compteur++;
}

void Board::printBoard() {
	for (int i = 0; i < LIGNES; i++) {
		std::cout << "|";
		for (int j = 0; j < COLONNES; j++) {
			if (cases[i][j])
				std::cout << " x ";
			else
				std::cout << "   ";
		}
		std::cout << "|\n";
	}
	menuHold();
	menuPieceSuivante();

}

void Board::menuHold()
{
	bool isX = false;
	std::cout << "\n";
	std::cout << "     Hold\n";
	for(int i = 0; i < 2;i++)
	{
		std::cout << "|";
		for (int j = 2; j < 6; j++) {
			isX = false;
			for(int z = 0;z < 4; z++)
			{
				if(pieceHold.getCarre(z).ligne == i && pieceHold.getCarre(z).colonne == j)
				{
					std::cout << " x ";
					isX = true;
				}
			}
			if(isX == false)
			{
				std::cout << "   ";
			}
		}
		std::cout << "|";
		std::cout << "\n";
	}
}

void Board::menuPieceSuivante()
{
	bool isX = false;
	std::cout << "\n";
	std::cout << "     Suivante\n";
	for (int i = 0; i < 2; i++)
	{
		std::cout << "|";
		for (int j = 2; j < 6; j++) {
			isX = false;
			for (int z = 0; z < 4; z++)
			{
				if (pieceApres.getCarre(z).ligne == i && pieceApres.getCarre(z).colonne == j)
				{
					std::cout << " x ";
					isX = true;
				}
			}
			if (isX == false)
			{
				std::cout << "   ";
			}
		}
		std::cout << "|";
		std::cout << "\n";
	}
}

void Board::changerPiece()
{
	if(pieceHold.getNumPiece() == 7)
	{
		pieceHold.loadPiece(piece.getNumPiece());
		piece.loadPiece(pieceApres.getNumPiece());
	}
	else
	{
		int numHold = pieceHold.getNumPiece();
		pieceHold.loadPiece(piece.getNumPiece());
		piece.loadPiece(numHold);
	}
	
}