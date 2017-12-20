#ifndef ENNEMIS_H
#define ENNEMIS_H

class CEsquadronTie;

class Ennemis : public EntiteVolante
{
private:
	CEsquadronTie* SquadLink;
	int			   SquadID;

public:
	Ennemis(categorie, affiliation, int, int, int, int, int);
	~Ennemis();
	void LinkToSquad(CEsquadronTie* link, int ID) { SquadLink = link; SquadID = ID; }
	void Remove();
	void UpdateTrajet(int x, int y);
};
#endif 