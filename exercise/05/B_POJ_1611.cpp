/* http://poj.org/problem?id=1611 */
/* AC 16MS 464K */
#include <stdio.h>

const int MAX_N = 30000 + 10;
const int MAX_M = 500 + 10;

int find_root(int set[], int i)
{
	if(set[i] != i)
	{
		set[i] = find_root(set, set[i]);
	}
	return set[i];
}

int main()
{
	int n, m;
	int i, j, k, num, ar, br, ans;
	int set[MAX_N];

	while(scanf("%d %d", &n, &m) != EOF && (n != 0 || m != 0))
	{
		for(i = 0; i < n; i++)
		{
			set[i] = i;
		}
		for(i = 0; i < m; i++)
		{
			scanf("%d", &k);
			if(k != 0)
			{
				scanf("%d", &num);
				ar = find_root(set, num);
			}
			for(j = 1; j < k; j++)
			{
				scanf("%d", &num);
				br = find_root(set, num);
				if(br == 0)
				{
					set[ar] = br;
					ar = 0;
				}
				else
				{
					set[br] = ar;
				}
			}
		}
		ans = 0;
		for(i = 0; i < n; i++)
		{
			ar = find_root(set, i);
			if(ar == 0)
			{
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*

100 4
2 1 2
5 10 13 11 12 14
2 0 1
2 99 2
200 2
1 5
5 1 2 3 4 5
1 0
0 0

*/