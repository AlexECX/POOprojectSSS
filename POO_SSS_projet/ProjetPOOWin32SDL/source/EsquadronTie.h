#pragma once

class Ennemis;
struct SDL_Thread;

class CEsquadronTie
{
private:
	std::vector<Ennemis> Squad;
	SDL_Thread* SquadThreadPtr;
	int SquadThreadReturnValue;
	int SquadCount;
	int Active;
public:
	CEsquadronTie(std::vector<Ennemis>);
	~CEsquadronTie();
	Ennemis* getMember(int member) { return &Squad[member]; }
	int getSquadronSize() { return Squad.size(); }
	bool isAlive() { return SquadCount > 0; }
	bool isActive() { return Active == 0; }

	void Update();
	void Remove() { Active++; }
	void RemoveMember(int member);

	static int StartSquadThread(void* pointer);
	int SquadThread();
};