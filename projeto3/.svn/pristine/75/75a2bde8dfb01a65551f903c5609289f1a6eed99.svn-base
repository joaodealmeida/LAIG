#pragma once

#include "SocketClient.h"
#include "Board.h"
#include "Block.h"
#include "GameState.h"

#include <vector>
#include <stack>

#define Address  "127.0.0.1"
#define Port  60001

using namespace std;

typedef enum {

	LeBloqGameTypePlayerVsAI_Easy,
	LeBloqGameTypePlayerVsAI_Hard,
	LeBloqGameTypePlayerVsPlayer,
	LeBloqGameTypeAIVsAI

} LeBloqGameType;
class LeBloq
{
	SocketClient *sckt;
	int boardsizeX, boardsizeY;
	int gameStart, turnStart, maxTurnTime;

	int checkWinner(Board b);
	GameState parseReply(string msg);


	LeBloqGameType gameType;
	stack <GameState> gameStates;


	LeBloq();
	void operator=(LeBloq const &);

public:
	static LeBloq& getInstance() {
        static LeBloq instance;
        
        return instance;
    }

	void setGameType(LeBloqGameType type);
	LeBloqGameType getGameType();

	GameState newGame(int boardSizeX, int boardSizeY);
	GameState getActualGameState();
	GameState getPreviousGameState();
	stack<GameState> getGameStates();
	void undoGameState();


	vector <int> getBoardSize();


	unsigned int getTimeElapsed();
	unsigned int getTurnTimeElapsed();
	unsigned int getMaxTurnTime();
	void setMaxTurnTime(unsigned int time);

	int getWinner();

	bool expire();
	GameState makePlay();
	GameState makePlay(Block piece);
	GameState makePlay(int piece, char orientation, vector<int> position);
	GameState makeAIPlay();

	Block workingPiece;
	Block pickPiece;
	
	~LeBloq();
};

