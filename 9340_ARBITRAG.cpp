/*
TASK: Arbitrage
ALGO: warshall
Input:
3
USDollar
BritishPound
FrenchFranc
3
USDollar 0.5 BritishPound
BritishPound 10.0 FrenchFranc
FrenchFranc 0.21 USDollar

3
USDollar
BritishPound
FrenchFranc
6
USDollar 0.5 BritishPound
USDollar 4.9 FrenchFranc
BritishPound 10.0 FrenchFranc
BritishPound 1.99 USDollar
FrenchFranc 0.09 BritishPound
FrenchFranc 0.19 USDollar

0

Output:
Case 1: Yes
Case 2: No
*/

#include <cstdio>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

#define MAX 30
#define EPS 1e-9

char res[2][4] = {"Yes","No"};
double value[MAX][MAX];
map< string, int > M;
map< string, int > :: iterator it;

inline int hash(char *s, int &n) 
{
	int ret; it = M.find(s);
	if(it == M.end()) 
		M.insert(pair< string, int >(s, ret=n++));
	else 
		ret = it->second;
	return ret;
}

int warshall(int n) 
{
	int i, j, k;
	for(k=0;k<n;k++) 
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				value[i][j] = max(value[i][j], value[i][k]*value[k][j]);
			}
		}
		if(value[k][k] > 1.0 + EPS) 
		{
			return 0;
		}
	}
	return 1;
}

int main() 
{
	int cs = 1, i, j, n;
	char name1[MAX], name2[MAX];
	double val;
	while(scanf("%d", &n)==1 && n) 
	{
		// init and get currency name
		M.clear();
		for(i = j = 0; i < n; i++) 
		{
			scanf("%s", name1);
			hash(name1, j);
		}
		// init exchange ratio matrix
		for(i = 0; i < n; i++) 
		{
			for(j = 0; j < n; j++) 
				value[i][j] = 0.0;
			value[i][i] = 1.0;
		}
		// get exchange ratio matrix
		scanf("%d", &j);
		while(j--) 
		{
			scanf("%s %lf %s", name1, &val, name2);
			value[M[name1]][M[name2]] = val;
		}
		printf("Case %d: %s\n", cs++, res[warshall(n)]); 
	}
	return 0;
}
