#include "FenetreDeJeu.h"


FenetreDeJeu::FenetreDeJeu(QMainWindow* fenetrePrincipale) : m_menuMenu(nullptr), m_menuBar(nullptr), m_menuOptionAccueil(nullptr), m_menuOptionQuitter(nullptr),
m_widget(nullptr), m_layout(nullptr), m_Garder(nullptr), m_hold(nullptr), m_gauche(nullptr), m_layoutGauche(nullptr),
m_centre(nullptr), m_droite(nullptr), m_gaucheHold(nullptr), m_Test(nullptr), m_bar(nullptr), m_layoutCentre(nullptr), m_tetris(nullptr),
m_next(nullptr), m_score(nullptr), m_bestscore(nullptr), m_joueur(nullptr), m_level(nullptr), m_layoutDroite(nullptr), m_elevel(nullptr),
m_pnext(nullptr), m_holdnext(nullptr), m_menuOptionAide(nullptr), frameHold(nullptr), framePieceSuivante(nullptr)
{
	m_layout = new QHBoxLayout();
	m_widget = new QWidget();
	board = new Board(this);
	frameHold = new FramePourPiece((board->getPieceHold()));
	framePieceSuivante = new FramePourPiece((board->getPieceSuivante()));
	//Partie Gauche
	m_gauche = new QGroupBox(tr("Gauche"));
	m_gaucheHold = new QGroupBox(tr("Hold"));
	m_layoutGauche = new QVBoxLayout();
	m_Garder = new QLabel("Garder");
	m_hold = new QGridLayout;
	m_Test = new QLabel("Test");
	m_Garder->setAlignment(Qt::AlignLeft);
	m_hold->setAlignment(Qt::AlignLeft);
	m_hold->addWidget(frameHold, 0, 0);
	m_gaucheHold->setLayout(m_hold);
	m_layoutGauche->addWidget(m_Garder);
	m_layoutGauche->addWidget(m_gaucheHold);
	m_gauche->setLayout(m_layoutGauche);
	m_layout->addWidget(m_gauche);

	//Partie Centre 
	m_centre = new QGroupBox(tr("Centre"));
	m_console = new QGroupBox(tr("Tetris"));
	m_layoutCentre = new QVBoxLayout();
	m_bar = new QProgressBar();
	m_tetris = new QVBoxLayout;

	boardInit(); // mettre au centre

	m_console->setLayout(m_tetris);
	m_layoutCentre->addWidget(m_bar);
	m_layoutCentre->addWidget(m_console);
	m_centre->setLayout(m_layoutCentre);
	m_layout->addWidget(m_centre);

	//Partie Droite
	m_droite = new QGroupBox(tr("Droite"));
	m_holdnext = new QGroupBox(tr("Next"));
	m_pnext = new QGridLayout;
	m_layoutDroite = new QVBoxLayout();
	m_elevel = new QProgressBar();
	m_next = new QLabel("Next");
	m_score = new QLabel("Score");
	m_bestscore = new QLabel("Prochain meilleur score");
	m_joueur = new QLabel("Joueur");
	m_level = new QLabel("Level");



	m_holdnext->setLayout(m_pnext);
	m_layoutDroite->addWidget(m_next);
	m_layoutDroite->addWidget(framePieceSuivante);
	m_layoutDroite->addWidget(m_holdnext);
	m_layoutDroite->addWidget(m_score);
	m_layoutDroite->addWidget(m_bestscore);
	m_layoutDroite->addWidget(m_joueur);
	m_layoutDroite->addWidget(m_elevel);
	m_layoutDroite->addWidget(m_level);
	m_droite->setLayout(m_layoutDroite);
	m_layout->addWidget(m_droite);

	//Onglet Menu + Aide
	m_menuBar = new QMenuBar;
	m_menuMenu = new QMenu("Menu");
	m_menuBar->addMenu(m_menuMenu);
	m_menuOptionAccueil = new QAction("Accueil");
	m_menuOptionQuitter = new QAction("Quitter");
	m_menuOptionAide = new QAction("Aide");
	m_menuMenu->addAction(m_menuOptionAccueil);
	m_menuMenu->addAction(m_menuOptionQuitter);
	m_menuMenu->addAction(m_menuOptionAide);
	m_layout->setMenuBar(m_menuBar);


	//Action 
	QObject::connect(m_menuOptionAccueil, SIGNAL(triggered(bool)), this, SLOT(slotPourFenetrePrincipale()));
	QObject::connect(this, SIGNAL(signalRetourPrincipale()), fenetrePrincipale, SLOT(slotChangerFenetrePrincipale()));
	QObject::connect(m_menuOptionAide, SIGNAL(triggered(bool)), this, SLOT(slotPourFenetreAide()));
	QObject::connect(this, SIGNAL(signalAllerAide()), fenetrePrincipale, SLOT(slotChangerFenetreAide()));
	QObject::connect(m_menuOptionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));


	setLayout(m_layout);
}

void FenetreDeJeu::slotPourFenetrePrincipale()
{
	emit signalRetourPrincipale();
}

void FenetreDeJeu::slotPourFenetreAide()
{
	emit signalAllerAide();
}


void FenetreDeJeu::boardInit() {

	board->setFocus();
	board->setFocusPolicy(Qt::StrongFocus);
	m_tetris->addWidget(board);
}

FenetreDeJeu::~FenetreDeJeu()
{
	close();
}

void FenetreDeJeu::slotPourTrigeredHold()
{
	frameHold->setPiece(board->getPieceHold());
}

void FenetreDeJeu::slotPourTrigeredSuivante()
{
	framePieceSuivante->setPiece(board->getPieceSuivante());
}