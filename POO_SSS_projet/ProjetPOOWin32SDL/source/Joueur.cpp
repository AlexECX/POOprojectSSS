#include "EntiteVolante.h"
#include "Joueur.h"

Joueur::Joueur(categorie CategorieParam,
				affiliation AffiliationParam,
				int			PosXParam,
				int			PosYParam,
				int			HP_Param,
				int			DamageParam,
				int			SpeedParam) : EntiteVolante(CategorieParam,
														AffiliationParam,
														PosXParam,
														PosYParam,
														HP_Param,
														DamageParam,
														SpeedParam)
{
}
Joueur::~Joueur()
{
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