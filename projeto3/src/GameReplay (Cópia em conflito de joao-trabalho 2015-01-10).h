#include "Board.h"
#include "GameState.h"
#include "Block.h"

#include <iostream>
#include <vector>
#include <stack>



class GameReplay
{
	std::stack<GameState> replay;
	GameState oldGS;
	int playsCounter;
public:
	GameReplay(){
		this->playsCounter = 0;
	}
	GameReplay(std::stack<GameState> replay);

	GameState getActualGameState();
	GameState getPreviousGameState();
	std::stack<GameState> getGameSateStack();

	std::vector<GameField> getScoredFields();
	Block getPlayedBlock();

	void nextMove();
	int getPlaysCounter();




	~GameReplay(void);
};
