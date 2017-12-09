#pragma once

class Ennemis;
struct SDL_Thread;

class CEsquadronTie
{
private:
	std::vector<Ennemis> Squad;
	SDL_Thread* SquadThreadPtr;
	int SquadThreadReturnValue;
	int Active;
public:
	CEsquadronTie(std::vector<Ennemis>);
	~CEsquadronTie();
	Ennemis* getMember(int member) { return &Squad[member]; }
	int getSquadronSize() { return Squad.size(); }
	bool isActive() { return Active == 0; }

	void Update();
	void Remove() { Active++; }

	static int StartSquadThread(void* pointer);
	int SquadThread();
};

