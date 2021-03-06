#pragma once
/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: FenetrePrincipale.h
Date: 15 avril 2021
But: Déclaration de FenetrePrincipale.h
====================================*/

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "FenetreDeJeu.h"
#include "FenetrePointage.h"
#include "Player.h"
#include "FenetreAide.h"
#include <QMainWindow>
#include <QMenu>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include <QInputDialog>
#include <mmsystem.h>
#include "BoutonPrincipal.h"
#include <strmif.h>
#include <control.h>
#include "Player.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <uuids.h>

#pragma comment(lib, "strmiids.lib")
class FenetrePrincipale : public QMainWindow
{
    
    Q_OBJECT
public:
    FenetrePrincipale();
    ~FenetrePrincipale();

public slots:
    void slotPourFenetreDeJeu();
    void slotChangerFenetrePrincipale();
    void slotPourFenetrePointage();
    void slotPourEnableFenetre();
    void slotChangerFenetreAide();
    void closeEvent(QCloseEvent* event);
    void slotPourContinuer();

private:

    //Boutons pour les autres pages
    BoutonPrincipal* boutonPourFenetreJeu;
    BoutonPrincipal* boutonPourFenetreReglage;
    BoutonPrincipal* boutonPourScore;
    BoutonPrincipal* boutonPourQuitter;
    BoutonPrincipal* boutonPourContinuer;

    //Le titre Tetris Mania 
    QLabel* labelTetris;
    
    //Creation d'un laytout
    QVBoxLayout* layoutVertical1;

    QWidget* widget;

    FenetreDeJeu* fenetreDeJeu;
    FenetreAide* fenetreAide;
    QStackedWidget* index;

    //Pointage
    FenetrePointage* fenetrePointage;
    QInputDialog* demandeUsername;

    //Player
    Player* player;
};
#endif