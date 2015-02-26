#ifndef BOARD_H
#define BOARD_H

#include "CGF\CGFobject.h"
#include "Block.h"
#include "Rectangle.h"

#include <vector>

class GameField {
    
public:
    
    std::vector <int> position;
	int scoringPlayer;
    
    GameField(std::vector <int> pos, int pl) {
        position = pos;
		scoringPlayer = pl;
    }
    
};

class Board : public Primitives
{
	std::vector< std::vector< int > > board;

	//aux functions
	char getPieceOrientation(std::vector<int> position );
	void removeBlock(std::vector< std::vector< int > > &b, std::vector <int> coordinates);

	Primitives *piece;

public:
	Board(){}
	Board(GLenum drawstyle, GLenum normal);
	Board(std::vector< std::vector< int > > board);
	Board operator-(Board b);
	~Board();

	void updateBoard(std::vector< std::vector< int > > board){
		this->board = board;
	}

	std::vector< std::vector< int > > getBoard();

	std::vector <Block> getBlocks();
	std::vector <GameField> getScoredFields();
	
	void draw();
};


#endif
