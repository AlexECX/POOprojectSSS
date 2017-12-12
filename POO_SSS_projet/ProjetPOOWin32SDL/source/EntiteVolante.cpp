#include "EntiteVolante.h"

EntiteVolante::EntiteVolante(categorie CategorieParam,
							affiliation AffiliationParam,
							int			PosXParam,
							int			PosYParam,
							int			HP_Param,
							int			DamageParam,
							int			SpeedParam)
{
	Categorie = CategorieParam;
	Affiliation = AffiliationParam;
	coordX = PosXParam;
	coordY = PosYParam;
	HP = HP_Param;
	Damage = DamageParam;
	VitesseDeplacment = SpeedParam;
	Active = 0;
}

EntiteVolante::~EntiteVolante()
{
}

void EntiteVolante::UpdateTrajet(int x, int y)
{
	coordX = x;
	coordY = y;  
}
