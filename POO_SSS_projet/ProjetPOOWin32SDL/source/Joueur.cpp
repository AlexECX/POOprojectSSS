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
	/*Categorie = CategorieParam;
	Affiliation = AffiliationParam;
	coordX = PosXParam;
	coordY = PosYParam;
	int HP = HP_Param;
	int Damage = DamageParam;
	int VitesseDeplacment = SpeedParam;*/
}
Joueur::~Joueur()
{
}
