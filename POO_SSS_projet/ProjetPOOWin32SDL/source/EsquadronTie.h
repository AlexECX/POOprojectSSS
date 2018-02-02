#pragma once
#include <vector>
#include <mutex>

class Ennemis;
struct SDL_Thread;

class CEsquadronTie
{
private:
	std::vector<std::shared_ptr<Ennemis>> Squad;
	SDL_Thread* SquadThreadPtr;
	int SquadThreadReturnValue;
	int SquadCount;
	std::mutex Squad_lock;
public:
	CEsquadronTie(std::vector<std::shared_ptr<Ennemis>>&);
	CEsquadronTie(CEsquadronTie const &E);
	~CEsquadronTie();

	std::shared_ptr<Ennemis> getMember(int member) { return Squad[member]; }

	int getSquadronSize() { return SquadCount; }

	bool isAlive() { return SquadCount > 0; }

	void Update();
	void RemoveMember(int member);
	void MakeFly();

	void operator=(CEsquadronTie const &E) {
		Squad = std::move(E.Squad);
		SquadCount = E.SquadCount;
	}

	static int StartSquadThread(void* pointer);
	int SquadThread();
};