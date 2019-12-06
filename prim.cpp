#pragma once
//José Pedro Baltazar Mendes
//xmende04	
#include "prim.h"

#define VERBOSEPRIM
//#define SUPERVERBOSEPRIM

PrimGraph::PrimGraph()
{
	vertexCount = 0;
	edgeCount = 0;
	dense = true;
}

PrimGraph::~PrimGraph()
{

}

void PrimGraph::generateEdges()
{
	adj.changeVertexNumber(vertexCount);

	int targetEdgeNumber = numberOfEdges(vertexCount, dense);

	int maxVertexes = maxEdges(vertexCount);

	edgeCount = 0;
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = i + 1; j < vertexCount; j++)
		{
			if (rand() % maxVertexes <= targetEdgeNumber) {
				adj.insertEdge(i, j, rand() % (INT_MAX-1)); //in order for the max weight value to remain smaller than our considered 'infinite'
				edgeCount++;
			}
		}
	}
}

unsigned long long PrimGraph::executePrim(int vertexNumber, int root, bool isDense)
{	
	vertexCount = vertexNumber;
	dense = isDense;

	bh.changeCapacity(vertexCount);

#ifdef SUPERVERBOSEPRIM
	chrono::high_resolution_clock::time_point endInit, startInit = chrono::high_resolution_clock::now();
#endif

	generateEdges();

#ifdef SUPERVERBOSEPRIM
	endInit = chrono::high_resolution_clock::now();
	cout << "init took " << chrono::duration_cast<std::chrono::microseconds>(endInit - startInit).count() << endl;
#endif // SUPERVERBOSEPRIM

#ifdef VERBOSEPRIM
	cout << "Executing Prim on a" << (isDense ? " dense " : " sparce ") << "graph with " << vertexCount << " vertices and " << edgeCount << " edges out of " << maxEdges(vertexCount) << endl;
#endif // VERBOSEPRIM

	chrono::high_resolution_clock::time_point end, start = chrono::high_resolution_clock::now();

	int* parentVertex = new int[vertexCount];

	for (int i = 0; i < vertexCount; i++)
	{
		parentVertex[i] = -1; //equivalent to parent[v] = NIL
	}

	bh.createVertices(); //V

	bh.decreaseKey(root, 0);

	while (!bh.isEmpty()) {//V
		int u = bh.extractMin();//LOGV
		AdjacencyResult v = adj.giveAdjacency(u);//1
		while (v.destination != -1)//O(V*LOGV) //DENSE -> LOOP RUNS AROUND V TIMES //SPARSE -> LOOP RUNS AROUND V/SCALAR
		{
			if (v.weight < bh.findPriority(v.destination))//O(1) //in case v does not belong in Q, it's priority PRIORITY_ERROR which is INT_MIN, therefore, never entering the loop
			{
				parentVertex[v.destination] = u;
				bh.decreaseKey(v.destination, v.weight);//O(LOGV)
			}
			v = adj.giveAdjacency(u);//1
		}
	}

	end = chrono::high_resolution_clock::now();
	unsigned long long nano = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
#ifdef VERBOSEPRIM
	cout << "finished in " << nano << " microseconds" << endl;
#endif // VERBOSEPRIM

#ifdef SUPERVERBOSEPRIM
	cout << "List of parents after Prim algorithm:" << endl;
	for (int i = 0; i < vertexCount; i++)
	{
		cout << i << '[' << parentVertex[i] << "] costing " << adj.findWeight(parentVertex[i], i) << endl;
	}
	cout << "finished" << endl;
#endif // SUPERVERBOSEPRIM


	delete[](parentVertex);
	return nano;
}


