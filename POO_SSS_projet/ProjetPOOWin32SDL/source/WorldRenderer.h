#pragma once

class LTexture;
struct LSprite;
class Ennemis;
class Joueur;
class EsquadronTie;
class Projectile;


class WorldRenderer
{
private:
	LTexture *GameTextures;
	LSprite *GameSprites;
	std::list<Joueur>::iterator P;
	std::list<Ennemis>::iterator S;
	std::list<std::vector<Ennemis>>::iterator M;
	std::list<CEsquadronTie>::iterator F;
	std::list<Projectile>::iterator T;


public:
	WorldRenderer(LTexture gametextures[], LSprite gamesprites[]);
	~WorldRenderer();

	void Render(std::list<Joueur>&);
	//void Render(std::list<Ennemis>);
	void Render(std::list<CEsquadronTie>&);
	void Render(std::list<Projectile>&);
	//void Render(std::list<categorie>);
};

