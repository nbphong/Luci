// IOI 2010 - Save It!
// Lúcio Cardoso

// Solution: https://ioinformatics.org/page/ioi-2010/36

#include <bits/stdc++.h>
#include "grader.h"
#include "encoder.h"

using namespace std;

const int maxn = 1e3+10;

static int dist[maxn][maxn], pai[maxn];

static svector<int> grafo[maxn];

void bfs(int s)
{
	queue<int> fila;

	fila.push(s), dist[s][s] = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[s][v] == -1)
			{
				dist[s][v] = dist[s][u]+1;
				fila.push(v);

				pai[v] = u;
			}
		}
	}
}

void encode(int n, int h, int e, int *v1, int *v2)
{
	for (int i = 0; i < e; i++)
	{
		grafo[v1[i]].push_back(v2[i]);
		grafo[v2[i]].push_back(v1[i]);
	}

	memset(dist, -1, sizeof dist);
	
	for (int i = n-1; i >= 0; i--)
		bfs(i);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (pai[i]&(1<<j)) encode_bit(1);
			else encode_bit(0);
		}
	}

	for (int j = 0; j < h; j++)
	{
		for (int i = 1; i < n; i += 5)
		{
			int tri = 0;

			for (int k = 0; k < 5; k++)
			{
				int u = i+k;

				int delta = (u >= n ? 0 : dist[j][u]-dist[j][pai[u]] + 1);

				tri += pow(3, k)*delta;
			}

			for (int k = 0; k < 8; k++)
			{
				if (tri&(1<<k)) encode_bit(1);
				else encode_bit(0);
			}
		}
	}
}
