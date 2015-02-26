#include "LeBloq.h"
#include "PrologParser.h"

#include <sstream>
#include <ctime>



LeBloq::LeBloq()
{
	this->sckt = new SocketClient(Address, Port);
	gameType = LeBloqGameTypePlayerVsPlayer;
	std::vector<int> position;
	position.push_back(13);
	position.push_back(4);
	pickPiece = Block(GL_FILL, GL_SMOOTH, 'v', 1, position);
}


LeBloq::~LeBloq()
{
}

void LeBloq::setGameType(LeBloqGameType type){
	this->gameType = type;
}

LeBloqGameType LeBloq::getGameType(){
	return this->gameType;
}

int LeBloq::checkWinner(Board b){
	stringstream ssX,ssY;
	ssX << this->boardsizeX;
	ssY << this->boardsizeY;

	string message = "checkWinner(" + PrologParser::boardRepresentationToProlog(b.getBoard()) + "," + ssX.str() + "," + ssY.str() + ").";
    
    std::cout << "[Check Winner Debug] " << message << std::endl;
    
    sckt->write(message);
    
    int winner = atoi(sckt->read().c_str());
    
    std::cout << "Winner State: " << winner << std::endl;
    
    return winner;
}

GameState LeBloq::parseReply(string msg) {
    msg.erase(0, 3);
	msg.pop_back();
    
    vector< vector<int> > boardV = PrologParser::prologToBoardRepresentation(msg, this->boardsizeX);
    
    Board board = Board(boardV);
    
    int nextPlayer = (this->gameStates.size() ? (getActualGameState().getPlayer() == 1 ? 2 : 1) : 2);
    
    std::cout << "Next Player: " << nextPlayer << std::endl;
    
    int winner = 0;
    
    bool playing = true;
    
    if (this->gameStates.size())
        if (( winner = checkWinner(board) )) {
            nextPlayer = winner;
			playing = false;
        }
    
    GameState state = GameState(board, nextPlayer, playing);
    
    this->gameStates.push(state);
    
    return state;
}

GameState LeBloq::newGame(int boardsizeX, int boardsizeY){
	stringstream ssX,ssY;
	ssX << boardsizeX;
	ssY << boardsizeY;
	
	sckt->write("initialize(" + ssX.str() + "," + ssY.str() + ").");

	string reply = sckt->read();

	if (reply.find("fail") != string::npos || reply.find("ok(") == string::npos){
		printf("Unable to create board.\n");
	}

	this->boardsizeX = boardsizeX;
	this->boardsizeY = boardsizeY;

	GameState actualGS,newGS;
	
	actualGS = parseReply(reply);
	newGS = GameState(actualGS.getBoard(),1, true);

	this->gameStart = (unsigned int) time(NULL);
	this->turnStart = gameStart;

	cout << newGS.getPlayer() << std::endl;

	while (this->gameStates.size())
        this->gameStates.pop();
    
    this->gameStates.push(newGS);
    
    return newGS;




}

GameState LeBloq::getActualGameState(){
	return this->gameStates.top();
}

GameState LeBloq::getPreviousGameState(){
	GameState actual = this->gameStates.top();
	this->gameStates.pop();
	GameState previous = getActualGameState();
	this->gameStates.push(actual);
	
	return previous;
}

stack<GameState> LeBloq::getGameStates(){
	return this->gameStates;
}
void LeBloq::undoGameState(){
	this->gameStates.pop();
}

vector <int> LeBloq::getBoardSize(){
	vector <int> returnVec;
	returnVec.push_back(this->boardsizeX);
	returnVec.push_back(this->boardsizeY);

	return returnVec;
}

unsigned int LeBloq::getTimeElapsed(){
	return (unsigned int)time(NULL) - this->gameStart;
}

unsigned int LeBloq::getTurnTimeElapsed(){
	return (unsigned int)time(NULL) - this->turnStart;
}

unsigned int LeBloq::getMaxTurnTime(){
	return this->maxTurnTime;
}

void LeBloq::setMaxTurnTime(unsigned int time){
	this->maxTurnTime = time;
}
bool LeBloq::expire(){
	if (getTurnTimeElapsed() <= this->maxTurnTime)
        return false;
    
    if (this->gameStates.size() == 1)    //First play exception.
        return false;

	
	if(this->gameType != LeBloqGameTypePlayerVsPlayer) //Only available for PlayervsPlayer
		return false;

    
    GameState actualGS = getActualGameState();

    
    actualGS.setPlayer(actualGS.getPlayer() == 1 ? 2 : 1);
    
    this->gameStates.push(actualGS);
	this->turnStart = (unsigned int) time(NULL);
    
    return true;
}

GameState LeBloq::makePlay(){
	return makePlay(workingPiece);
}

GameState LeBloq::makePlay(Block piece){
	return makePlay(piece.getType(), piece.getOrientation(), piece.getBlockPosition());
}

GameState LeBloq::makePlay(int piece, char orientation, vector<int> position){
	stringstream bXss,bYss,typess,orientationss,posXss,posYss,playerss;
	string message, reply;
	bXss << boardsizeX;
	bYss << boardsizeY;
	typess << piece;
	orientationss << orientation;
	posXss << ( (int) position[0] );
	posYss << ( (int) position[1] );
	playerss << getActualGameState().getPlayer();



	message = (this->gameStates.size() == 1 ? "playFT(" : "play(") + PrologParser::boardRepresentationToProlog(getActualGameState().getBoard().getBoard()) + "," + typess.str() + "," + orientationss.str() + "," + posXss.str() + "," + posYss.str() + "," + playerss.str() + "," + bXss.str() + "," + bYss.str() + ").";
    
    for (int i = 0; i < 3; i++) {
        sckt->write(message);
		reply = sckt->read();
        
        if (reply.find("fail") != string::npos || reply.find("ok(") == string::npos) {
            if (i == 2){
                std::cout << "Unable to perform play: "<< message << std::endl;
				return getActualGameState();
			}
        } else
            break;
    }

    GameState state = parseReply(reply);
	this->turnStart = (unsigned int) time(NULL);
    
    return state;
}

GameState LeBloq::makeAIPlay(){
	string message,reply;
	stringstream bXss,bYss, playerss;

	bXss << boardsizeX;
	bYss << boardsizeY;
	playerss << getActualGameState().getPlayer();

	message = (this->gameStates.size() == 1 ? "playAIFT(" : "playAI(") + PrologParser::boardRepresentationToProlog(getActualGameState().getBoard().getBoard()) + "," + playerss.str() + "," + bXss.str() + "," + bYss.str() + ").";

    
    for (int i = 0; i < 3; i++) {
        sckt->write(message);
        
        reply = sckt->read();
        
        if (reply.find("fail") != string::npos || reply.find("ok(") == string::npos) {
            if (i == 2){
                std::cout << "Unable to perform play: "<< message << std::endl;
				return getActualGameState();
			}
        } else
            break;
    }
    
    GameState state = parseReply(reply);
    
    this->turnStart = (unsigned int) time(NULL);
    
    return state;
}

int LeBloq::getWinner(){
	return(this->checkWinner(getActualGameState().getBoard()));
}
