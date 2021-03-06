#pragma once
/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: BoutonPrincipal.h
Date: 15 avril 2021
But: D�clarer BoutonPrincipal.h
====================================*/

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>
#include <qdebug.h>
class BoutonPrincipal : public QPushButton
{
private: 
	bool buttonFPGA;
public:
	BoutonPrincipal(bool button);
	~BoutonPrincipal();
protected:
	void hoverEnter(QHoverEvent* event);
	void hoverLeave(QHoverEvent* event);
	bool event(QEvent* event);
};

