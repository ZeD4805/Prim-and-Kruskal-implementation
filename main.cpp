//José Pedro Baltazar Mendes
//xmende04	

#include "prim.h"
#include "kruskal.h"
#include <numeric>
#include <fstream>
#define KRUSKAL
#define PRIM

int main(void) {

	srand(time(NULL));

	vector<unsigned long long> kruskalDenseTimes, primDenseTimes, kruskalSparceTimes, primSparceTimes;
	int testsPerPoint = 15;
	int batches = 20;
	unsigned long long average = 0;
	vector<unsigned long long> averages;
#ifdef KRUSKAL


	//KRUSKAL
	KruskalGraph kg;
	
	for (int i = 0; i < batches; i++)
	{
		average = 0;
		vector<unsigned long long> averages;

		for (int j = 0; j < testsPerPoint; j++)
		{
			averages.push_back(kg.executeKruskal(30 + 50 * i, true)); //the accumulator will overflow if it's not divided by 1000
		}
		averages.erase(min_element(averages.begin(), averages.end()));
		averages.erase(max_element(averages.begin(), averages.end()));
		
		kruskalDenseTimes.push_back(accumulate(averages.begin(), averages.end(), 0) / averages.size());
		averages.clear();

		for (int j = 0; j < testsPerPoint; j++)
		{
			averages.push_back(kg.executeKruskal(30 + 50 * i, false));
		}
		averages.erase(min_element(averages.begin(), averages.end()));
		averages.erase(max_element(averages.begin(), averages.end()));

		kruskalSparceTimes.push_back(accumulate(averages.begin(), averages.end(), 0) / averages.size());
		averages.clear();
	}

#endif // KRUSKAL

#ifdef PRIM
	//PRIM
	PrimGraph pg;

	for (int i = 0; i < 20; i++)
	{
		average = 0;
		for (int j = 0; j < testsPerPoint; j++)
		{
			averages.push_back(pg.executePrim(30 + 50 * i, 0, true));
		}
		averages.erase(min_element(averages.begin(), averages.end()));
		averages.erase(max_element(averages.begin(), averages.end()));

		primDenseTimes.push_back(accumulate(averages.begin(), averages.end(), 0) / averages.size());
		averages.clear();

		for (int j = 0; j < testsPerPoint; j++)
		{
			averages.push_back(pg.executePrim(30 + 50 * i, 0, false));
		}
		averages.erase(min_element(averages.begin(), averages.end()));
		averages.erase(max_element(averages.begin(), averages.end()));

		primSparceTimes.push_back(accumulate(averages.begin(), averages.end(), 0) / averages.size());
		averages.clear();
	}
#endif

	std::ofstream csvfile;
	csvfile.open("timesInMicro.csv");
	csvfile << "V,dense kruskal,sparce kruskal,dense prim,sparce prim\n";
	for (int i = 0; i < batches; i++)
	{
		csvfile << 30+50*i << "," <<kruskalDenseTimes[i] << "," << kruskalSparceTimes[i] << "," << primDenseTimes[i] << "," << primSparceTimes[i] << "\n";
		
	}
	csvfile.close();

	return 0;
}