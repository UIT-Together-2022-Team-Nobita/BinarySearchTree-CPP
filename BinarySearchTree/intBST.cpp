#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct node
{
	int info;
	struct node* pLeft;
	struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

void Init(TREE&);
NODE* GetNode(int);
int InsertNode(TREE&, string);
int Input(TREE&, string);
void Output(TREE);
int Output(TREE, string);
int Output(TREE, ofstream&);
int NodeCount(TREE);

int main()
{
	clock_t start, end = 0;
	double time_use;
	start = clock();
	TREE t;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intbst";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(t, filenameinp) == true)
		{
			cout << "\nThe number of nodes:	" << NodeCount(t);
			string filenameout = filename;
			filenameout += ".out";
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else
			cout << "\nCan't open the file" << filename << endl;
	}
	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nRuntime:	" << time_use;
	cout << endl;
	return 1;
}


void Init(TREE& t)
{
	t = NULL;
}

NODE* GetNode(int x)
{
	NODE* p = new NODE;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}

int InsertNode(TREE& t, int x)
{
	if (t != NULL)
	{
		int rValue = rand();
		if (rValue % 2 == 0)
			return InsertNode(t->pRight, x);
		return InsertNode(t->pLeft, x);
	}
	t = GetNode(x);
	if (t == NULL)
		return -1;
	return 1;
}

int Input(TREE& t, string filename)
{
	ifstream fi(filename);
	if (fi.fail())
		return 0;
	int n, x;
	fi >> n;
	Init(t);
	for (int i = 1; i <= n; i++)
	{
		fi >> x;
		InsertNode(t, x);
	}
	return 1;
}

void Output(TREE t)
{
	if (t == NULL)
		return;
	Output(t->pLeft);
	cout << t->info;
	Output(t->pRight);
}

int Output(TREE t, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return 0;
	fo << setw(6) << NodeCount(t) << endl;
	return Output(t, fo);
}

int Output(TREE t, ofstream& fo)
{
	if (t == NULL)
		return 0;
	Output(t->pLeft, fo);
	fo << setw(6) << t->info;
	Output(t->pRight, fo);
}

int NodeCount(TREE t)
{
	if (t == NULL)
		return 0;
	int a = NodeCount(t->pLeft);
	int b = NodeCount(t->pRight);
	return a + b + 1;
}