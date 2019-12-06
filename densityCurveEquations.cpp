#pragma once
//José Pedro Baltazar Mendes
//xmende04	
#include "densityCurveEquations.h"

int maxEdges(int vertexCount) {
	return (vertexCount * (vertexCount - 1) / 2);
}; //N*(N-1)/2 (No Self-Loops)

int numberOfEdges(int vertexCount, bool dense) {
	if (dense)
		return (int)(pow(vertexCount, 2) / (1 * log10(vertexCount)) - 280); //N^2/(1.5*logN)
	else
		return (int)(3 * vertexCount * log10(vertexCount)); //3*N*logN
}