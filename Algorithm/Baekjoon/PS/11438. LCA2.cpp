#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 100001
int N, M;

vector<vector<int>>adj;		//���� ����
int dp[21][MAX] = { 0, };	//dp[i][j]: j�� ����� 2^i��° �θ��� ��ȣ
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

	//��� ����
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);	//���Ḹ
	}

	depth[0] = -1;
	dfs(1, 0);	//bfs �� ������ depth, �θ��� ����

	//dp���ϱ� - ���� �߿�
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
		}	//a�� �� ���� depth�� ����

		for (int i = 20; i >= 0; i--) {
			if (depth[a] - depth[b] >= (1 << i))	//2�� ������ �����ϰ� ǥ��
				a = dp[i][a];	//�ѹ��� 2^i��° �θ�� �̵�
		}
		int rst = 0;

		//���� ���̸� ������ �������� ���� ������ ����
		if (a == b)
			rst = a;
		//�ƴ϶��, �ٽ� ����� �Ѵ�.
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