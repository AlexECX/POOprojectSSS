#include "EntiteVolante.h"
#include "Ennemis.h"

Ennemis::Ennemis(categorie CategorieParam,
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

Ennemis::~Ennemis()
{
}

void Ennemis::UpdateTrajet(int x, int y)
{
	if (coordX > 1) {
		coordX = x;
		coordY = y;
	}
	else
		HP = 0;
}


