#pragma once
//José Pedro Baltazar Mendes
//xmende04	

#include "priorityQ.h"
#include "adjacencyList.h"
#include "densityCurveEquations.h"

#include <chrono>

class PrimGraph
{
public:
	PrimGraph();
	~PrimGraph();

	unsigned long long executePrim(int vertexNumber, int root, bool dense);

private:
	void generateEdges();

	int edgeCount;
	int vertexCount;
	bool dense;
	BinaryHeap bh;
	AdjList adj;
};

