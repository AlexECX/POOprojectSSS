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
	int HP = HP_Param;
	int Damage = DamageParam;
	int VitesseDeplacment = SpeedParam;
}

EntiteVolante::~EntiteVolante()
{
}
