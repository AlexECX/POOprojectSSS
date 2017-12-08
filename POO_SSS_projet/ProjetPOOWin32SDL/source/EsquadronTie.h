#pragma once

class Ennemis;
struct SDL_Thread;

class CEsquadronTie
{
private:
	std::vector<Ennemis> Squad;
	SDL_Thread* SquadThreadPtr;
	int SquadThreadReturnValue;
	bool Flying;
public:
	CEsquadronTie(std::vector<Ennemis>);
	~CEsquadronTie();
	Ennemis* getMember(int member) { return &Squad[member]; }
	int getSquadronSize() { return Squad.size(); }
	

	void Update();

	static int StartSquadThread(void* pointer);
	int SquadThread();
};

