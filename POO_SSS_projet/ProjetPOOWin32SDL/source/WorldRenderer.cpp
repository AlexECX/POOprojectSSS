
#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\LTexture.h"
#include "..\ressources\LSprite.h"







WorldRenderer::WorldRenderer(LTexture gametextures[], LSprite gamesprites[]): GameTextures(gametextures), GameSprites(gamesprites)
{
}

WorldRenderer::~WorldRenderer()
{
}

void WorldRenderer::Render(std::list<Joueur> &PlayerRender)
{
	for (P = PlayerRender.begin(); P != PlayerRender.end(); P++) {
		if (P->isAlive())
			GameTextures[P->getCategorie()].render(P->getCoordX(), P->getCoordY());

	}
}

void WorldRenderer::Render(std::list<CEsquadronTie> &SquadRender)
{
	for (F = SquadRender.begin(); F != SquadRender.end(); F++) {
		if (F->isActive()) {
			int Members = F->getSquadronSize();
			for (int i = 0; i < F->getSquadronSize(); i++) {
				if (F->getMember(i)->isAlive())
					GameTextures[F->getMember(i)->getCategorie()].render(F->getMember(i)->getCoordX(), F->getMember(i)->getCoordY());
			}
		}
	}
}

void WorldRenderer::Render(std::list<Projectile> &ProjectileRender)
{
	for (T = ProjectileRender.begin(); T != ProjectileRender.end(); T++) {
		if (T->isAlive())
			GameTextures[T->getCategorie()].render(T->getCoordX(), T->getCoordY());

	}
}
