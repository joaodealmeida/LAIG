#pragma once

#include "Board.h"

class GameState
{
	Board board;
	int player;
	bool playing;


public:
	GameState(){
		board = Board();
	}
	GameState(Board board, int player, bool playing){
		this->board = board;
		this->player = player;
		this->playing = playing;
	}

	void setPlayer(int player){
		this->player = player ;
	}

	int getPlayer(){
		return this->player;
	}

	Board getBoard(){
		return this->board;
	}

	bool getPlaying (){
		return this->playing;
	}
	
	~GameState(){}
};

