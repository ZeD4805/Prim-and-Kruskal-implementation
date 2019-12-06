#pragma once
//José Pedro Baltazar Mendes
//xmende04	

#include "kruskal.h"

#define VERBOSEKRUSKAL

using namespace std;

bool edgeSorter(Edge e1, Edge e2) {
	return (e1.weight < e2.weight);
}

DisjointElement::DisjointElement() //in the beggining of the execution of the algorithm, each set is represented by itself, this means that each element is it's own set's head.
{
	head = this;
	rank = 0;
}

DisjointElement::~DisjointElement()
{
}

/*int DisjointElement::getSetSize() {
	return head->children.size();
}*/

DisjointElement* DisjointElement::getSetHead() //path compression
{
	while (head != head->head)
		head = head->head;

	return head;
}

int DisjointElement::getSetRank()
{
	return getSetHead()->rank;
}

void DisjointElement::mergeSet(DisjointElement* otherSet) {

	DisjointElement* finalHead = this->getSetHead();
	DisjointElement* headToRemove = otherSet->getSetHead();

	int htrSize = headToRemove->rank;
	int fhSize = finalHead->rank;

	if (headToRemove->rank > finalHead->rank) {
		finalHead = otherSet->head;
		headToRemove = this->head;
	}

	if(finalHead->rank < headToRemove->rank +1)
		finalHead->rank = headToRemove->rank + 1;

	headToRemove->head = finalHead;
	headToRemove->rank = 0;

	/*for (vector<DisjointElement*>::iterator itr = headToRemove->children.begin(); itr != headToRemove->head->children.end(); itr++) { //iterates through all the children of the set to be merged and adds them to the final set
		(*itr)->head = finalHead;
		finalHead->children.push_back(*itr);
	}

	finalHead->children.push_back(headToRemove);
	headToRemove->children.clear();
	headToRemove->head = finalHead; //we also have to add the other set's head into the set*/
}

KruskalGraph::KruskalGraph()
{
	vertexCount = 0;
}

KruskalGraph::~KruskalGraph()
{
}


void KruskalGraph::fillEdgeBank(int vertexNumber, bool isDense)
{
	vertexCount = vertexNumber;
	edges.clear(); //resets the edges and parameters

	int targetEdgeNumber = numberOfEdges(vertexNumber, isDense);

	int maxVertexes = maxEdges(vertexNumber);

	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = i+1; j < vertexCount; j++)
		{
			if (rand() % maxVertexes <= targetEdgeNumber)
				edges.push_back(Edge({ i, j, rand() }));
		}
	}
}

unsigned long long KruskalGraph::executeKruskal(int vertexNumber, bool isDense)
{
	fillEdgeBank(vertexNumber, isDense);

#ifdef VERBOSEKRUSKAL
	cout << "Executing Kruskal on a" << (isDense ? " dense " : " sparce ") << "graph with " << vertexCount << " vertices and " << edges.size() << " edges out of " << vertexCount*(vertexCount-1)/2<< endl;
#endif // VERBOSEKRUSKAL

	chrono::high_resolution_clock::time_point end, start = chrono::high_resolution_clock::now();

	vector<Edge> selectedEdges; //"A" set

	DisjointElement* disjointSets = new DisjointElement[vertexCount]; //n time complexity

	vector<Edge>::iterator itr;
#ifdef SUPERVERBOSEKRUSKAL
	chrono::high_resolution_clock::time_point endsort, startsort = chrono::high_resolution_clock::now(); //start counting edge sorting time
#endif

	sort(edges.begin(), edges.end(), edgeSorter); //nlogn time complexity

#ifdef SUPERVERBOSEKRUSKAL
	endsort = chrono::high_resolution_clock::now();
	cout << "Edge sort time: " << chrono::duration_cast<chrono::microseconds>(endsort - startsort).count() << endl;
#endif // SUPERVERBOSEKRUSKAL


	for (itr = edges.begin(); itr != edges.end() && selectedEdges.size() < vertexCount - 1; itr++)//O(E*(V+logV)) time complexity //we stop the collection of edges as we have enough to connect all vertices
	{
		if (disjointSets[itr->origin].getSetHead() != disjointSets[itr->destiny].getSetHead())//logV
		{
			selectedEdges.push_back(*itr);//1
			disjointSets[itr->origin].mergeSet(&disjointSets[itr->destiny]);//O(V) time complexity
		}		
	}

	end = chrono::high_resolution_clock::now();
	unsigned long long nano = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
#ifdef VERBOSEKRUSKAL
	cout << "finished in " << nano << " microseconds" << endl;
#endif // VERBOSEKRUSKAL
	delete[](disjointSets);
	//TOTAL COMPLEXITY IS O(E*LOG(E) + E*V + E*LOGV )

	//FOR DENSE IS AROUND	E~=V^2	->O(V^2 * 2LOG(V) + V^3 + V^2*LOGV) = O(V^3 + V^2*LOG(V)
	//FOR SPARCE IS AROUND	E~=V	->O(V*LOGV + V^2 + V*LOGV) = O(V^2 + V*LOG(V))
	return nano;
}
