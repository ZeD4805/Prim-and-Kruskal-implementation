#pragma once
//José Pedro Baltazar Mendes
//xmende04	

#include <stdlib.h>
#include <vector>
#define INT_MAX 2147483647

using namespace std;

//Linked list adjacency
//each node of the linked list contains it's weight
typedef struct _AdjacencyResult{
	int destination;
	int weight;
}AdjacencyResult;

typedef struct _AdjacencyNode {
	int vertexNumber;
	struct _AdjacencyNode *next;
	int weight;
}AdjacencyNode;

class AdjList
{
public:
	AdjList();
	~AdjList();
	void insertEdge(int origin, int destination, int weight, bool called=false);
	int findWeight(int origin, int destination);
	AdjacencyResult giveAdjacency(int origin);

	void changeVertexNumber(int vertexNumber);

private:

	void clean();

	int vertexCount;
	AdjacencyNode ** adjacencies;
	int lastAdjacencyRoot;
	AdjacencyNode *currAdj;
};

