#include "EntiteVolante.h"
#include "Joueur.h"

Joueur::Joueur(affiliation AffiliationParam,
				int			PosXParam,
				int			PosYParam)
				: EntiteVolante(joueur,
								AffiliationParam,
								PosXParam,
								PosYParam,
								1,
								10,
								0)
{
	Size = 35;
}
Joueur::~Joueur()
{
}

void Joueur::UpdateTrajet(int x, int y)
{
	if (coordX + x > 0 && coordX + x < 1200)
		coordX += x;
	if (coordY + y > 0 && coordY + y < 700)
		coordY += y;
}

void Joueur::MouvUp()
{
	if (coordY > 0)
	{
		coordY--;
	}
}

void Joueur::MouvDown()
{
	if (coordY < 560)
	{
		coordY++;
	}
}

void Joueur::MouvLeft()
{
	if (coordX > 0)
	{
		coordX--;
	}
}

void Joueur::MouvRight()
{
	if (coordX < 1030)
	{
		coordX++;
	}
}