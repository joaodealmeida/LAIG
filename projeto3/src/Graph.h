#pragma once

#include "Node.h"
class Graph
{
public:
	Graph(void){}
	~Graph(void){}

	void addNode(Node *n1){
		graphNodes.push_back(n1);
	}

	/*void deleteNode(Node *n1){
		vector<Node *>::iterator it = std::find(graphNodes.begin(), graphNodes.end(), n1);
        
        if (it != graphNodes.end())
            graphNodes.erase(it);
	}*/

	void setRootNode(Node *n1){
		this->rootNode=n1;
	}

	void setRootRef(string id){
		rootref=id;
	}

	Node * getRootNode(){
		return rootNode;
	}

	string getRootNodeRef(){
		return rootref;
	}

	vector<Node *> getGraphNodes(){
		return graphNodes;
	}


private:
	string rootref;
	Node *rootNode;
	vector<Node *> graphNodes;
};

