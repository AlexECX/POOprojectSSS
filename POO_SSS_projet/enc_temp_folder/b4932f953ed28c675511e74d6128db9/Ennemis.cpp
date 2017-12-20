#include "EntiteVolante.h"
#include "Ennemis.h"
#include "EsquadronTie.h"


Ennemis::Ennemis(categorie CategorieParam,
				 affiliation AffiliationParam,
				 int			PosXParam,
				 int			PosYParam,
				 int			HP_Param,
				 int			DamageParam,
				 int			SpeedParam)
				: EntiteVolante(CategorieParam,
								AffiliationParam,
								PosXParam,
								PosYParam,
								HP_Param,
								DamageParam,
								SpeedParam)
{
	SquadLink = nullptr;
}

Ennemis::~Ennemis()
{
	if (SquadLink->getSquadronSize() <= 1)
		delete SquadLink;
	else
		SquadLink->RemoveMember(SquadID);
	/*if (SquadLink != nullptr)
		delete SquadLink;*/
}

void Ennemis::Remove()
{
	  SquadLink = nullptr;
}

void Ennemis::UpdateTrajet(int x, int y)
{
	if (coordX > 1/*-100*/) {
		coordX = x;
		coordY = y;
	}
	else
		HP = 0;
}


