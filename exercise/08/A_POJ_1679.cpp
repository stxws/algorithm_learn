/* http://poj.org/problem?id=1679 */
/* AC 0MS 412K */
#include <stdio.h>
#include <string.h>

const int MAX_N = 100 + 5;
const int INF = 0x1f1f1f1f;

int n, m;
int mp[MAX_N][MAX_N];
int mst[MAX_N];
int maxd[MAX_N][MAX_N];

int prim()
{
	int i, j, k, min, ans;
	int dist[MAX_N];

	for(i = 1; i <= n; i++)
	{
		dist[i] = mp[1][i];
		mst[i] = 1;
	}
	dist[1] = -1;
	
	ans = 0;
	for(i = 2; i <= n; i++)
	{
		min = INF;
		for(j = 2; j <= n; j++)
		{
			if(dist[j] != -1 && min > dist[j])
			{
				min = dist[j];
				k = j;
			}
		}
		if(min == INF)
		{
			return -1;
		}
		ans += dist[k];
		dist[k] = -1;
		for(j = 1; j <= n; j++)
		{
			if(dist[j] != -1 && dist[j] > mp[k][j])
			{
				dist[j] = mp[k][j];
				mst[j] = k;
			}
			if(dist[j] == -1)
			{
				int pre = mst[k];
				maxd[j][k] = (maxd[j][pre] > mp[pre][k]) ? maxd[j][pre] : mp[pre][k];
				maxd[k][j] = maxd[j][k];
			}
		}
	}
	return ans;
}

int sec_mst(int mst_l)
{
	int i, j, ans;

	ans = INF;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			if(i == j || mp[i][j] == INF || mst[i] == j || mst[j] == i)
			{
				continue;
			}
			if(ans > mst_l + mp[i][j] - maxd[i][j])
			{
				ans = mst_l + mp[i][j] - maxd[i][j];
			}
		}
	}
	if(ans == INF)
	{
		return -1;
	}
	else
	{
		return ans;
	}
}

int main()
{
	int t, i, x, y, w, mst_l;

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &m);
		memset(mp, 0x1f, sizeof(mp));
		memset(maxd, 0, sizeof(maxd));
		for(i = 0; i <= n; i++)
		{
			mp[i][i] = 0;
		}
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &x, &y, &w);
			if(mp[x][y] > w)
			{
				mp[x][y] = w;
				mp[y][x] = w;
			}
		}

		mst_l = prim();
		if(mst_l < 0 || mst_l == sec_mst(mst_l))
		{
			printf("Not Unique!\n");
		}
		else
		{
			printf("%d\n", mst_l);
		}
	}
	return 0;
}

/*
7

3 3
1 2 1
2 3 2
3 1 3

2 3
1 2 37
2 1 17
1 2 68

4 4
1 2 2
2 3 2
3 4 2
4 1 2

1 0

2 3
1 2 17
2 1 17
1 2 68

5 7
1 2 5
2 3 7
2 4 8
4 5 11
3 5 10
1 5 6
4 2 12



3
68
Not Unique!
0
68
29

*/