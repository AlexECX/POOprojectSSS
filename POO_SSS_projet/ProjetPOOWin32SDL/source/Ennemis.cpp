#include "EntiteVolante.h"
#include "Ennemis.h"
#include "EsquadronTie.h"


Ennemis::Ennemis(affiliation AffiliationParam,
			 	 int			PosXParam,
				 int			PosYParam)
				 : EntiteVolante(tie_fighter,
					AffiliationParam,
					PosXParam,
					PosYParam,
					1,
					10,
					0)
{
	Hit1.w = 48;
	Hit1.h = 3;
	Hit2.w = 21;
	Hit2.h = 48;
	Hit3.w = 48;
	Hit3.h = 3;
	//SquadLink = nullptr;
}

Ennemis::~Ennemis()
{
}

void Ennemis::UpdateTrajet(int x, int y)
{
	if (coordX > -100) {
		coordX = x;
		coordY = y;
	}
	else
		HP = 0;
}


