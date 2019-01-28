#include "Graph.h"
#include <iostream>
#include "fstream"
#include "conio.h"
#define ERROR(e) {cout << "ERROR: " << e << endl; exit(1);}
const int N = 100;
bool used[N];
int timer, tin[N], fup[N];

int min(int a, int b)
{
	if (a<b) return a; else return b;
}

Graph::Graph(int n)
{
	this->n = n;
	a = new int *[n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
		for (int j = 0; j < n; j++)
			a[i][j] = 0;
	}
}


Graph * Graph::loadFromMarixFile(const string filePath)
{
	int graphSize;
	ifstream stream(filePath);
	stream >> graphSize;

	Graph * newGraph = new Graph(graphSize);

	return newGraph;
}

Graph * Graph::loadFromDimaxFormat(const string filePath)
{
	int graphSize = 0;
	ifstream stream(filePath);


	stream >> graphSize;

	Graph * newGraph = new Graph(graphSize);

	return newGraph;
}


Graph * Graph::loadFromEdgeListFile(const string filePath) {
	int    graphSize;
	ifstream stream(filePath);

	if (!stream.is_open()) {
		ERROR("Can not open input file: " + filePath);
	}

	stream >> graphSize;

	Graph * newGraph = new Graph(graphSize);

	int i, j;
	while (!stream.eof()) {
		stream >> i >> j ;
		newGraph->a[i - 1][j - 1] = 1;
		newGraph->a[j - 1][i - 1] = 1;
	}

	return newGraph;
}

Graph::~Graph(void)
{
	for (int i = 0; i < n; i++) {
		delete a[i];
	}

	delete a;
}


void Graph::printMatrix() {
	cout << "Size: " << n << "\n";


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "\t";
		cout << "\n";
	}


}

void Graph::FindBrigde()
{
	timer = 0;
	for (int i = 0; i<n; ++i)
		used[i] = false;
	for (int i = 0; i<n; ++i)
		if (!used[i])
			DepthFirstSearch(i,-1);
}

void Graph::PrintBrigde(int startI,int to)
{
	cout << endl << "Brigde is " << startI + 1 << "-" << to + 1;
}



void Graph::DepthFirstSearch(int startI, int startJ)
{
	used[startI] = true;
	tin[startI] = fup[startI] = timer++;
	for (int j = 0; j < n; ++j)
	{
		if (a[startI][j] == 1)
		{
			int to = j;
			if (to == startJ)  continue;
			if (used[to])
				fup[startI] = min(fup[startI], tin[to]);
			else {
				DepthFirstSearch(to, startI);
				fup[startI] = min(fup[startI], fup[to]);
				if (fup[to] > tin[startI])
					PrintBrigde(startI, to);
			}
		}
	}
}


int main() {
	//char inputFileName [] = "simpleGraph.txt";
	//char inputFileName [] = "/Users/aponom/Dropbox/Prepod/Algoirthms and Data Structures/CppGraph/simpleGraph.txt";
	char inputFileName[] = "graph.txt";
	cout << "Input file: " << inputFileName << "\n";

	Graph *newGraph = Graph::loadFromEdgeListFile(inputFileName);;
	newGraph->printMatrix();
	newGraph->FindBrigde();
	getch();
	
}


