#include "GameReplay.h"


GameReplay::GameReplay(std::stack<GameState> replay)
{
   GameState gs;
   std::stack<GameState> tmpStack;

   while (replay.empty() == false)
   {
      gs = replay.top();
      replay.pop();
      tmpStack.push(gs);
   }
   this->playsCounter = 0;
   this->replay = tmpStack;
}


GameReplay::~GameReplay(void)
{
}

GameState GameReplay::getActualGameState(){
	return this->replay.top();
}

GameState GameReplay::getPreviousGameState(){
	return this->oldGS;
}

std::stack<GameState> GameReplay::getGameSateStack(){
	return this->replay;
}

std::vector<GameField> GameReplay::getScoredFields(){
	if(this->playsCounter < 4)
		return std::vector<GameField>();

	Board diff = this->replay.top().getBoard() - this->oldGS.getBoard();

	return diff.getScoredFields();

}

Block GameReplay::getPlayedBlock(){
	 std::vector<Block > blocks = this->replay.top().getBoard().getBlocks();
        
     if (this->playsCounter == 1)
            return blocks[0];
        
     Board diff = this->replay.top().getBoard() - this->oldGS.getBoard();

	 return diff.getBlocks()[0];
	
}

int GameReplay::getPlaysCounter(){
	return this->playsCounter;
}

void GameReplay::nextMove(){

	this->playsCounter++;
	this->oldGS = this->replay.top();
	this->replay.pop();
}



