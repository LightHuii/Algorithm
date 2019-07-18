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
int cnt = 1, r_cnt = 0;		//cnt: order, r_cnt: ���� ����

int dfs(int curr, bool root) {
	order[curr] = cnt++;	//order ����
	visited[curr] = true;	//visit

	int ret = order[curr];	//ret: ���� ����� low�� ����
	int child = 0;			//root�� ��� �ڽ� ����

	//������ ��忡 ����
	for (int i = 0; i < (int)adj[curr].size(); i++) {
		int next = adj[curr][i];
		if (!visited[next]) {	//���� �鸮�� �ʾҴٸ�
			child++;

			int df = dfs(next, false);	//������ ����� low

			//root�� �ƴϰ�, ���� ����� low�� ���� order���� ũ�ų� ���ٸ� ���� ��尡 ������
			if (!root && df >= order[curr] && !selected[curr]) {
				rst.push_back(curr);
				r_cnt++;
				selected[curr] = true;
			}
			//���� ����� low�� ���� ���� ������ ���š�
			//�̷��� �ؾ� ��Ʈ ����� low�� 1�� ����
			ret = min(ret, df);
		}
		//���� ��尡 �̹� �鸰 ���̶��, low�� ���� ����� order�� ���� ���� ��
		else
			ret = min(ret, order[next]);
	}

	//��Ʈ�� ���
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