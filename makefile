all: target

target:
	@echo "Compiling PrimNKruskalProject xmende04"
	gpp -o primNkruskal main.cpp kruskal.cpp adjacencyList.cpp densityCurveEquations.cpp disjointSet.cpp prim.cpp priorityQ.cpp