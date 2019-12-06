#pragma once
//José Pedro Baltazar Mendes
//xmende04	

#include <vector>
#include <iostream>
#include <chrono>

#include "densityCurveEquations.h"

using namespace std;

typedef struct _Edge {
	int origin;
	int destiny;
	int weight;
}Edge;

class DisjointElement //represents the set by itself, possesses a children vector to which the element is the head to
{
public:
	DisjointElement();
	~DisjointElement();

	DisjointElement* getSetHead();
	void mergeSet(DisjointElement* otherSet);
	int getSetRank();
private:
	int rank;
	DisjointElement* head;
};


class KruskalGraph
{
public:
	KruskalGraph();
	~KruskalGraph();

	
	unsigned long long executeKruskal(int vertexNumber, bool dense); //executes kruskal algorithm with a given number of vertices and the density of the edges

private:
	void fillEdgeBank(int vertexCount, bool dense); //used only for internal creation of the edges.
	int vertexCount;
	vector<Edge> edges;
};


