#include <string>
using namespace std;
class Graph
{

private:
	int **a; //pointer to the matrix
	int n; //number of vertex

public:
	Graph(int n);

	int getSize() { return n; }
	static Graph * loadFromMarixFile(const string filePath);
	static Graph * loadFromEdgeListFile(const string filePath);
	static Graph * loadFromDimaxFormat(const string filePath);

	void printMatrix();

	void DepthFirstSearch(int startI, int startJ);

	void FindBrigde();

	void PrintBrigde(int startI, int to);

	~Graph(void);
};
