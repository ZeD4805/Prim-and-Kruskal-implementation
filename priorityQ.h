#pragma once
//José Pedro Baltazar Mendes
//xmende04	

#include <iostream>
#include <vector>

#define INT_MAX 2147483647
#define HEAP_MAX 512
#define INT_MIN -INT_MAX -1
#define PRIORITY_ERROR INT_MIN;
//vertex definition

using namespace std;

class Vertex
{
public:
	Vertex();
	Vertex(int vertexNumber);
	~Vertex() {};

	int indexInQueue;
	int priority;
private:

};

//binary heap implementation

//implemented on a Vertex array
class BinaryHeap
{
public:
	BinaryHeap() { heap_size = 0; capacity = 0; vertices = nullptr; verticeHelper = nullptr; };
	~BinaryHeap() { delete[]verticeHelper; delete[]vertices; };

	
	void createVertices();
	int extractMin();
	void decreaseKey(int vertexNumber, int new_priority);
	bool isEmpty();
	int findPriority(int vertexNumber);

	void changeCapacity(int numberOfVertices);

private:
	int left(int index) { return (2 * index + 1); };
	int right(int index) { return (2 * index + 2); };
	int parent(int index) { return (index - 1) / 2; };

	void swap(int index1, int index2);
	void heapify(int root);

	Vertex* verticeHelper; //contains the index of the vertex in the heap array and it's priority
	int* vertices;

	int heap_size;
	int capacity;
};
