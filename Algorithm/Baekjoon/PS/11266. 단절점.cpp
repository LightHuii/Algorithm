#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>
using namespace std;

#define MAX 10001
int V, E;
vector<vector<int>>adj;
int order[MAX] = { 0, };
bool visited[MAX];
bool selected[MAX];
vector<int>rst;
int cnt = 1, r_cnt = 0;		//cnt: order, r_cnt: 정답 개수

int dfs(int curr, bool root) {
	order[curr] = cnt++;	//order 지정
	visited[curr] = true;	//visit

	int ret = order[curr];	//ret: 현재 노드의 low를 리턴
	int child = 0;			//root일 경우 자식 개수

	//인접한 노드에 대해
	for (int i = 0; i < (int)adj[curr].size(); i++) {
		int next = adj[curr][i];
		if (!visited[next]) {	//아직 들리지 않았다면
			child++;

			int df = dfs(next, false);	//인접한 노드의 low

			//root가 아니고, 다음 노드의 low가 현재 order보다 크거나 같다면 현재 노드가 단절점
			if (!root && df >= order[curr] && !selected[curr]) {
				rst.push_back(curr);
				r_cnt++;
				selected[curr] = true;
			}
			//인접 노드의 low중 가장 낮은 값으로 갱신★
			//이렇게 해야 루트 노드의 low가 1로 설정
			ret = min(ret, df);
		}
		//인접 노드가 이미 들린 곳이라면, low는 다음 노드의 order중 가장 낮은 값
		else
			ret = min(ret, order[next]);
	}

	//루트일 경우
	if (root && child > 1) {
		rst.push_back(curr);
		r_cnt++;
	}
	return ret;
}

int main()
{
	cin >> V >> E;
	adj.resize(V + 1);
	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= V; i++)
		sort(adj[i].begin(), adj[i].end());

	for (int i = 1; i <= V; i++) {
		if (!visited[i])
			dfs(i, true);
	}

	sort(rst.begin(), rst.end());
	cout << r_cnt << endl;
	for (int i = 0; i < (int)rst.size(); i++)
		cout << rst[i] << ' ';

	return 0;
}