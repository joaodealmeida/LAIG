#include <string>

#include "PrologParser.h"

#define toDigit(c) (c - '0')

std::string PrologParser::boardRepresentationToProlog(std::vector<std::vector<int>> boardRep) {
    std::string returnRep = "[";
    
	for (int i = 0; i < boardRep.size(); i++ ) {
        returnRep += "[";
        
		for (int j = 0; j < boardRep[i].size(); j++ )
			returnRep += std::to_string( (long double) boardRep[i][j] ) + ",";
        
        returnRep.pop_back();   //  Remove outstanding comma.
        
        returnRep += "],";
    }
    
    returnRep.pop_back();       //  Remove outstanding comma, again!
    
    returnRep += "]";
    
    return returnRep;
}

std::vector<std::vector<int>> PrologParser::prologToBoardRepresentation(std::string boardRep, int lineSize) {
    std::vector<std::vector<int>> returnRep;
    
    std::vector<int> line;
    
    for (int i = 0, lc = 0; i < boardRep.size(); i++)
        if (isdigit(boardRep[i])) {
            line.push_back(toDigit(boardRep[i]));
            
            if (++lc == lineSize) {
                returnRep.push_back(line);
                
                line = std::vector<int>();
                
                lc = 0;
            }
        }
    
    return returnRep;
}
