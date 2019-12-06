#pragma once
//José Pedro Baltazar Mendes
//xmende04	
#include "adjacencyList.h"

void AdjList::clean()
{
	if (adjacencies != nullptr)
	{
		for (int i = 0; i < vertexCount; i++)
		{
			AdjacencyNode* curr = adjacencies[i];
			AdjacencyNode* next = nullptr;

			while (curr != nullptr)
			{
				next = curr->next;
				delete(curr);
				curr = next;
			}
		}

		delete[]adjacencies;
	}

	adjacencies = nullptr;
}

AdjList::AdjList()
{
	vertexCount = 0;
	lastAdjacencyRoot = -1;
	currAdj = nullptr;
}

AdjList::~AdjList()
{
	clean();
}

void AdjList::insertEdge(int origin, int destination, int weight, bool called)
{
	AdjacencyNode* allocated = new AdjacencyNode({ destination, nullptr, weight });

	AdjacencyNode** curr = &(adjacencies[origin]);
	while (*curr != nullptr) //read access violation
		curr = &((*curr)->next);

	*curr = allocated;

	if (!called)
		insertEdge(destination, origin, weight, true); //undirected graph (one call to define both edges)

}

int AdjList::findWeight(int origin, int destination)
{
	if (origin == -1 || destination == -1) return -1;

	AdjacencyNode* curr = adjacencies[origin];
	while (curr != nullptr and curr->vertexNumber != destination)
		curr = curr->next;
	if (curr != nullptr)
		return curr->weight;
	return -1;
}

AdjacencyResult AdjList::giveAdjacency(int origin)
{
	if (origin != lastAdjacencyRoot) {
		currAdj = adjacencies[origin];
		lastAdjacencyRoot = origin;
	}

	if (currAdj == nullptr) return AdjacencyResult({ -1, INT_MAX });
	//we have to verify if the result is -1
	AdjacencyResult res = { currAdj->vertexNumber, currAdj->weight };
	currAdj = currAdj->next;

	return res;
}

void AdjList::changeVertexNumber(int vertexNumber)
{
	clean();
	vertexCount = vertexNumber;
	adjacencies = new AdjacencyNode* [vertexNumber];
	for (int i = 0; i < vertexCount; i++)
		adjacencies[i] = nullptr;
}


