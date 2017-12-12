#ifndef ENNEMIS_H
#define ENNEMIS_H

class Ennemis : public EntiteVolante
{
private:

public:
	Ennemis(categorie, affiliation, int, int, int, int, int);
	~Ennemis();

	void UpdateTrajet(int x, int y);
};
#endif 