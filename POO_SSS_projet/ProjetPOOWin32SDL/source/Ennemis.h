#ifndef ENNEMIS_H
#define ENNEMIS_H
#include <SDL.h>

class CEsquadronTie;

class Ennemis : public EntiteVolante
{
private:
	//CEsquadronTie* SquadLink;
	int			   SquadID;
	//Hit boxes
	SDL_Rect Hit1, Hit2, Hit3;

public:
	Ennemis(affiliation, int, int);
	~Ennemis();
	
	void UpdateTrajet(int x, int y);

};
#endif 