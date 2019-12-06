#pragma once
//José Pedro Baltazar Mendes
//xmende04	
#include "priorityQ.h"

Vertex::Vertex()
{
	indexInQueue = -1;//inoperable, used only for array creation
	priority = INT_MAX;
}

Vertex::Vertex(int index)
{
	indexInQueue = index;
	priority = INT_MAX; //equivalent to infinite
}

void BinaryHeap::swap(int index1, int index2) {
	int tmp = verticeHelper[vertices[index1]].indexInQueue;
	verticeHelper[vertices[index1]].indexInQueue = verticeHelper[vertices[index2]].indexInQueue;
	verticeHelper[vertices[index2]].indexInQueue = tmp;

	
	tmp = vertices[index1];
	vertices[index1] = vertices[index2];
	vertices[index2] = tmp;
}

void BinaryHeap::createVertices()
{
	for (int i = 0; i < capacity; i++)
	{
		heap_size++;
		vertices[i] = i;
		verticeHelper[i].indexInQueue = i;
		verticeHelper[i].priority = INT_MAX;
	}
}

int BinaryHeap::extractMin()
{
	if (heap_size <= 0)
		return -1;
	int vertexToExtract = vertices[0];
	if (heap_size == 1) { //prevents the swap, saving performance
		heap_size = 0;
		verticeHelper[0].indexInQueue = -1;//sets the index to -1 and the priority for the minimum available value
		verticeHelper[0].priority = PRIORITY_ERROR;
		vertices[0] = -1;
		
		return vertexToExtract;
	}

	swap(0, heap_size - 1);
	
	verticeHelper[vertices[heap_size - 1]].indexInQueue = -1;
	verticeHelper[vertices[heap_size - 1]].priority = PRIORITY_ERROR;
	vertices[heap_size - 1] = -1;
	heap_size--;
	heapify(0);

	return vertexToExtract;
}



void BinaryHeap::decreaseKey(int vertexNumber, int new_priority)
{
	int index = verticeHelper[vertexNumber].indexInQueue;
	verticeHelper[vertexNumber].priority = new_priority;

	while (index != 0 && verticeHelper[vertices[index]].priority < verticeHelper[vertices[parent(index)]].priority)
	{
		swap(index, parent(index));
		index = parent(index);
	}

}

bool BinaryHeap::isEmpty()
{
	return (vertices[0] == -1);
}

int BinaryHeap::findPriority(int vertexNumber)
{
	return verticeHelper[vertexNumber].priority;
}

void BinaryHeap::changeCapacity(int numberOfVertices)
{
	heap_size = 0;
	capacity = numberOfVertices;
	if (verticeHelper != nullptr)
		delete[]verticeHelper;
	if (vertices != nullptr)
		delete[]vertices;

	verticeHelper = new Vertex[numberOfVertices];
	vertices= new int[numberOfVertices];
}

void BinaryHeap::heapify(int root)
{
	int l = left(root);
	int r = right(root);
	int newRoot = root;

	if (l < heap_size && verticeHelper[vertices[l]].priority < verticeHelper[vertices[root]].priority)
		newRoot = l;
	if (r < heap_size && verticeHelper[vertices[r]].priority < verticeHelper[vertices[root]].priority)
		newRoot = r;

	if (newRoot != root) {
		swap(root, newRoot);
		heapify(newRoot);
	}
}
