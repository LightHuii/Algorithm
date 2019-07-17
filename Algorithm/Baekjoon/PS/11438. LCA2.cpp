#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 100001
int N, M;

vector<vector<int>>adj;		//연결 정보
int dp[21][MAX] = { 0, };	//dp[i][j]: j번 노드의 2^i번째 부모의 번호
int depth[MAX] = { 0, };
int parent[MAX] = { 0, };
bool visited[MAX];

void dfs(int curr, int par) {
	depth[curr] = depth[par] + 1;
	parent[curr] = par;
	dp[0][curr] = parent[curr];

	visited[curr] = true;
	for (int i = 0; i < (int)adj[curr].size(); i++) {
		int next = adj[curr][i];
		if (!visited[next]) {
			visited[next] = true;
			dfs(next, curr);
		}
	}
}

int main()
{
	scanf("%d", &N);

	adj.resize(N + 1);

	//노드 생성
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);	//연결만
	}

	depth[0] = -1;
	dfs(1, 0);	//bfs 한 번으로 depth, 부모노드 설정

	//dp구하기 - 순서 중요
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= N; i++)
			dp[j][i] = dp[j - 1][dp[j - 1][i]];
	}
	
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (depth[a] < depth[b]) {
			int tmp = a;
			a = b;
			b = tmp;
		}	//a에 더 깊은 depth를 넣음

		for (int i = 20; i >= 0; i--) {
			if (depth[a] - depth[b] >= (1 << i))	//2의 제곱을 간단하게 표현
				a = dp[i][a];	//한번에 2^i번째 부모로 이동
		}
		int rst = 0;

		//깊이 차이를 좁히는 과정에서 서로 같으면 정답
		if (a == b)
			rst = a;
		//아니라면, 다시 맞춰야 한다.
		else {
			for (int i = 20; i >= 0; i--) {
				if (dp[i][a] != dp[i][b]) {
					a = dp[i][a];
					b = dp[i][b];
				}
			}
			rst = dp[0][a];
		}
		printf("%d\n", rst);
	}

	return 0;
}